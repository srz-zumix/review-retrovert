# -*- coding: utf-8 -*-

##
## ReVIEW::PDFMakerのソースコードがいろいろひどいので、書き直す。
## 具体的には、もとのコードではPDFMakerクラスの責務が大きすぎるので、分割する。
## ・CLIクラス … コマンドラインオプションの解析
## ・Makerクラス … PDFに限定されない機能（設定ファイルの読み込み等）
## ・PDFMakerクラス … 原稿ファイルを読み込んでPDFファイルを生成する機能
## ・LATEXRendererクラス … layout.tex.erbのレンダリング
##

require 'date'
require 'pathname'
require 'digest/md5'
require 'rbconfig'
require 'review/pdfmaker'

require_relative './review-cli'
require_relative './review-maker'


module ReVIEW


  remove_const :PDFMaker if defined?(PDFMaker)


  class PDFMaker < Maker

    SCRIPT_NAME = "review-pdfmaker"

    def generate()
      remove_old_file()
      @build_dir = make_build_dir()
      begin
        book = load_book()  # also loads 'review-ext.rb'
        #
        converter = ReVIEW::Converter.new(book, new_builder())
        errors = create_input_files(converter, book)
        if errors && !errors.empty?
          FileUtils.rm_f pdf_filepath()   ###
          handle_compile_errors(errors)
        end
        #
        prepare_files()
        tmp_file = build_pdf(book)
        copy_outfile(tmp_file, pdf_filepath())
      ensure
        remove_entry_secure(@build_dir) unless @config['debug']
      end
    end

    protected

    def new_builder()
      return ReVIEW::LATEXBuilder.new
    end

    def pdf_filepath
      return File.join(@basedir, "#{@config['bookname']}.pdf")
    end

    def remove_old_file
      #FileUtils.rm_f(pdf_filepath())    # don't delete pdf file
    end

    def make_build_dir()
      dir = "#{@config['bookname']}-pdf"
      if !File.directory?(dir)
        Dir.mkdir(dir)
      else
        ## 目次と相互参照に関するファイルだけを残し、あとは削除
        Pathname.new(dir).children.each do |x|
          next if x.basename.to_s =~ /\.(aux|toc|out|mtc\d*|maf)\z/
          x.rmtree()
        end
      end
      return dir
    end

    def create_input_files(converter, book)
      errors = []
      book.each_input_file do |part, chap|
        if part
          err = output_chaps(converter, part.name) if part.file?
        elsif chap
          filename = File.basename(chap.path, '.*')
          err = output_chaps(converter, filename)
        end
        errors << err if err
      end
      return errors
    end

    def output_chaps(converter, filename)
      contdir = @config['contentdir']
      infile  = "#{filename}.re"
      infile  = File.join(contdir, infile) if contdir.present?
      outfile = "#{filename}.tex"
      $stderr.puts "compiling #{outfile}"
      begin
        converter.convert(infile, File.join(@build_dir, outfile))
        nil
      ## 文法エラーだけキャッチし、それ以外のエラーはキャッチしないよう変更
      ## （LATEXBuilderで起こったエラーのスタックトレースを表示する）
      rescue ApplicationError => ex
        warn "compile error in #{outfile} (#{ex.class})"
        warn ex.message
        ex.message
      end
    end

    def handle_compile_errors(errors)
      return if errors.nil? || errors.empty?
      if @config['ignore-errors']
        $stderr.puts 'compile error, but try to generate PDF file'
      else
        error 'compile error, No PDF file output.'
      end
    end

    def build_pdf(book)
      base = "book"
      #
      texfile = File.join(@build_dir, "#{base}.tex")
      new_renderer(book).generate_file(texfile)
      #
      Dir.chdir(@build_dir) do
        if ENV['REVIEW_SAFE_MODE'].to_i & 4 > 0
          warn 'command configuration is prohibited in safe mode. ignored.'
          config = ReVIEW::Configure
        else
          config = @config
        end
        compile_latex_files(base, config)
      end
      #
      return File.join(@build_dir, "#{base}.pdf")
    end

    def absolute_path(filename)
      return nil unless filename.present?
      filepath = File.absolute_path(filename, @basedir)
      return File.exist?(fielpath) ? filepath : nil
    end

    def compile_latex_files(base, config)
      latex_cmd  = config['texcommand']
      latex_opt  = config['texoptions']
      dvipdf_cmd = config['dvicommand']
      dvipdf_opt = config['dvioptions']
      mkidx_p    = config['pdfmaker']['makeindex']
      mkidx_cmd  = config['pdfmaker']['makeindex_command']
      mkidx_opt  = config['pdfmaker']['makeindex_options']
      mkidx_sty  = absolute_path(config['pdfmaker']['makeindex_sty'])
      mkidx_dic  = absolute_path(config['pdfmaker']['makeindex_dic'])
      #
      latex  = "#{latex_cmd} #{latex_opt}"
      dvipdf = "#{dvipdf_cmd} #{dvipdf_opt}"
      mkidx  = "#{mkidx_cmd} #{mkidx_opt}"
      mkidx  << " -s #{mkidx_sty}" if mkidx_sty
      mkidx  << " -d #{mkidx_dic}" if mkidx_dic
      #
      call_hook('hook_beforetexcompile')
      changed = run_latex!(latex, "#{base}.tex")
      changed = run_latex!(latex, "#{base}.tex") if changed
      changed = run_latex!(latex, "#{base}.tex") if changed
      if mkidx_p  # 索引を作る場合
        call_hook('hook_beforemakeindex')
        run_cmd!("#{mkidx} #{base}") if File.exist?("#{base}.idx")
        call_hook('hook_aftermakeindex')
        run_latex!(latex, "#{base}.tex")
      end
      call_hook('hook_aftertexcompile')
      return unless File.exist?("#{base}.dvi")
      run_cmd!("#{dvipdf} #{base}.dvi")
      call_hook('hook_afterdvipdf')
    end

    ## コンパイルメッセージを減らすために、uplatexコマンドをバッチモードで起動する。
    ## エラーがあったら、バッチモードにせずに再コンパイルしてエラーメッセージを出す。
    def run_latex!(latex, file)
      ## *.auxファイルと*.tocファイルのハッシュ値を計算する。
      ## （「//list[?]」が生成するラベルはランダムなのでそれを削除してハッシュ値を計算する。）
      delete_rexp = /^\\newlabel\{_\d+\}/
      auxfile = file.sub(/\.tex\z/, '.aux')
      tocfile = file.sub(/\.tex\z/, '.toc')
      auxhash_old = _filehash(auxfile, delete_rexp)
      tochash_old = _filehash(tocfile)
      ## invoke latex command with batchmode option in order to suppress
      ## compilation message (in other words, to be quiet mode).
      ok = run_cmd("#{latex} -interaction=batchmode #{file}")
      if ! ok
        ## latex command with batchmode option doesn't show any error,
        ## therefore we must invoke latex command again without batchmode option
        ## in order to show error.
        $stderr.puts "*"
        $stderr.puts "* latex command failed; retry without batchmode option to show error."
        $stderr.puts "*"
        run_cmd!("#{latex} #{file}")
      end
      ## *.tocファイルのハッシュ値を計算し、コンパイル前と変わっていたらtrueを返す。
      ## （つまりもう一度コンパイルが必要ならtrueを返す。）
      auxhash_new = _filehash(auxfile, delete_rexp)
      tochash_new = _filehash(tocfile)
      return auxhash_old.nil? || tochash_old.nil? \
          || auxhash_old != auxhash_new || tochash_old != tochash_new
      ## LaTeXのログファイルに「ラベルが変更された」と出ていたらtrueを返す。
      ## （つまりもう一度コンパイルが必要ならtrueを返す。）
      ## → この方法は、ページ番号が変わったことは検出できても、
      ##    章や節のタイトルが変わったことを検出できない。
      #logfile = file.sub(/\.tex\z/, '.log')
      #begin
      #  lines = File.open(logfile, 'r') {|f|
      #    f.grep(/^LaTeX Warning: Label\(s\) may have changed./)
      #  }
      #  return !lines.empty?
      #rescue IOError
      #  return true
      #end
    end

    def _filehash(filepath, delete_rexp=nil)
      return nil unless File.exist?(filepath)
      binary = File.open(filepath, 'rb') {|f| f.read() }
      binary = binary.gsub(delete_rexp, '') if delete_rexp
      return Digest::MD5.hexdigest(binary)
    end
    private :_filehash

    ## 開発用。LaTeXコンパイル回数を環境変数で指定する。
    if ENV['STARTER_COMPILETIMES']
      alias __run_latex! run_latex!
      def run_latex!(latex, file)
        n = ENV['STARTER_COMPILETIMES']
        @_done ||= {}
        k = "#{latex} #{file}"
        return if (@_done[k] ||= 0) >= n.to_i
        @_done[k] += 1
        __run_latex!(latex, file)
      end
    end

    def prepare_files()
      ## copy image files
      copy_images(@config['imagedir'], File.join(@build_dir, @config['imagedir']))
      ## copy style files
      stydir = File.join(Dir.pwd, 'sty')
      copy_sty(stydir, @build_dir)
      copy_sty(stydir, @build_dir, 'fd')
      copy_sty(stydir, @build_dir, 'cls')
      copy_sty(Dir.pwd, @build_dir, 'tex')
    end

    def copy_outfile(tmp_pdffile, out_pdffile)
      if File.exist?(tmp_pdffile)
        FileUtils.cp(tmp_pdffile, out_pdffile)
      elsif File.exist?(out_pdffile)
        FileUtils.rm(out_pdffile)
      end
    end

    def copy_images(from, to)
      return unless File.exist?(from)
      FileUtils.mkdir_p(to)
      ReVIEW::MakerHelper.copy_images_to_dir(from, to)
      ## extractbb コマンドは、最近のLaTeX処理系では必要ないだけでなく、
      ## XeTeX において図がずれる原因になるので、使わない。
      #|Dir.chdir(to) do
      #|  images = Dir.glob('**/*.{jpg,jpeg,png,pdf,ai,eps,tif,tiff}')
      #|  images = images.find_all {|f| File.file?(f) }
      #|  break if images.empty?
      #|  d = @config[@maker_name]
      #|  if d['bbox']
      #|    system('extractbb', '-B', d['bbox'], *images)
      #|    system_or_raise('ebb', '-B', d['bbox'], *images) unless system('extractbb', '-B', d['bbox'], '-m', *images)
      #|  else
      #|    system('extractbb', *images)
      #|    system_or_raise('ebb', *images) unless system('extractbb', '-m', *images)
      #|  end
      #|end
    end

    def copy_sty(dirname, copybase, extname = 'sty')
      unless File.directory?(dirname)
        warn "No such directory - #{dirname}"
        return
      end
      Dir.open(dirname) do |dir|
        dir.each do |fname|
          if File.extname(fname).downcase == '.' + extname
            FileUtils.mkdir_p(copybase)
            FileUtils.cp File.join(dirname, fname), copybase
          end
        end
      end
    end

    def new_renderer(book)
      return LATEXRenderer.new(@config, book, @basedir, @starter_config)
    end


    ## layout.tex.erb をレンダリングする
    class LATEXRenderer < BaseRenderer
      include ReVIEW::LaTeXUtils

      def layout_template_name
        return './latex/layout.tex.erb'
      end

      def initialize(*args)
        super
        setup()
      end

      def setup()
        @input_files = make_input_files(@book)
        #
        dclass = @config['texdocumentclass'] || []
        @documentclass = dclass[0] || 'jsbook'
        @documentclassoption = dclass[1] || 'uplatex,oneside'

        @okuduke = make_colophon()
        @authors = make_authors()

        @custom_titlepage = make_custom_page(@config['cover']) || make_custom_page(@config['coverfile'])
        @custom_originaltitlepage = make_custom_page(@config['originaltitlefile'])
        @custom_creditpage = make_custom_page(@config['creditfile'])

        @custom_profilepage = make_custom_page(@config['profile'])
        @custom_advfilepage = make_custom_page(@config['advfile'])
        @custom_colophonpage = make_custom_page(@config['colophon']) if @config['colophon'] && @config['colophon'].is_a?(String)
        @custom_backcoverpage = make_custom_page(@config['backcover'])

        if @config['pubhistory']
          warn 'pubhistory is oboleted. use history.'
        else
          @config['pubhistory'] = make_history_list.join("\n")
        end

        @coverimageoption =
          if @documentclass == 'ubook' || @documentclass == 'utbook'
            'width=\\textheight,height=\\textwidth,keepaspectratio,angle=90'
          else
            'width=\\textwidth,height=\\textheight,keepaspectratio'
          end

        part_tuple     = I18n.get('part'    ).split(/\%[A-Za-z]{1,3}/, 2)
        chapter_tuple  = I18n.get('chapter' ).split(/\%[A-Za-z]{1,3}/, 2)
        appendix_tuple = I18n.get('appendix').split(/\%[A-Za-z]{1,3}/, 2)
        @locale_latex = {
          'prepartname'      => part_tuple[0],
          'postpartname'     => part_tuple[1],
          'prechaptername'   => chapter_tuple[0],
          'postchaptername'  => chapter_tuple[1],
          'preappendixname'  => appendix_tuple[0],
          'postappendixname' => appendix_tuple[1],
        }

        @texcompiler = File.basename(@config['texcommand'], '.*')
        #
        return self
      end

      private

      def chapter_key(chap)
        return 'PREDEF'   if chap.on_predef?
        return 'CHAPS'    if chap.on_chaps?
        return 'APPENDIX' if chap.on_appendix?
        return 'POSTDEF'  if chap.on_postdef?
        return nil
      end

      def make_input_files(book)
        input_files = {'PREDEF'=>"", 'CHAPS'=>"", 'APPENDIX'=>"", 'POSTDEF'=>""}
        book.each_input_file do |part, chap|
          if part
            key = 'CHAPS'
            latex_code = (part.file? ? "\\input{#{part.name}.tex}\n"
                                     : "\\part{#{part.name}}\n")
          elsif chap
            key = chapter_key(chap)  # 'PREDEF', 'CHAPS', 'APPENDEX', or 'POSTDEF'
            latex_code = "\\input{#{File.basename(chap.path, '.*')}.tex}\n"
          end
          input_files[key] << latex_code if key
        end
        return input_files
      end

      def make_custom_page(file)
        file_sty = file.to_s.sub(/\.[^.]+\Z/, '.tex')
        return File.read(file_sty) if File.exist?(file_sty)
        nil
      end

      def join_with_separator(value, sep)
        return [value].flatten.join(sep)
      end

      def make_colophon_role(role)
        return "" unless @config[role].present?
        initialize_metachars(@config['texcommand'])
        names = @config.names_of(role)
        sep   = i18n('names_splitter')
        str   = [names].flatten.join(sep)
        #return "#{i18n(role)} & #{escape_latex(str)} \\\\\n"
        return "\\startercolophonrow{#{i18n(role)}}{#{escape_latex(str)}}\n"
      end

      def make_colophon()
        return @config['colophon_order'].map {|role| make_colophon_role(role) }.join
      end

      def make_authors
        sep = i18n('names_splitter')
        pr = proc do |key, labelkey, linebreak|
          @config[key].present? ? \
            linebreak + i18n(labelkey, names_of(key, sep)) : ""
        end
        authors = ''
        authors << pr.call('aut', 'author_with_label', '')
        authors << pr.call('csl', 'supervisor_with_label', " \\\\\n")
        authors << pr.call('trl', 'translator_with_label', " \\\\\n")
        return authors
      end

      def names_of(key, sep)
        return @config.names_of(key).map {|s| escape_latex(s) }.join(sep)
      end

      def make_history_list
        buf = []
        if @config['history']
          @config['history'].each_with_index do |items, edit|
            items.each_with_index do |item, rev|
              editstr = edit == 0 ? i18n('first_edition') : i18n('nth_edition', (edit + 1).to_s)
              revstr = i18n('nth_impression', (rev + 1).to_s)
              if item =~ /\A\d+\-\d+\-\d+\Z/
                buf << i18n('published_by1', [date_to_s(item), editstr + revstr])
              elsif item =~ /\A(\d+\-\d+\-\d+)[\s　](.+)/
                # custom date with string
                item.match(/\A(\d+\-\d+\-\d+)[\s　](.+)/) { |m| buf << i18n('published_by3', [date_to_s(m[1]), m[2]]) }
              else
                # free format
                buf << item
              end
            end
          end
        elsif @config['date']
          buf << i18n('published_by2', date_to_s(@config['date']))
        end
        buf
      end

      def date_to_s(date)
        d = Date.parse(date)
        d.strftime(i18n('date_format'))
      end

    end


  end


end
