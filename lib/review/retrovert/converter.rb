require "review"
require 'fileutils'
require "review/retrovert/yamlconfig"

module ReVIEW
  module Retrovert
    class Converter
      attr_accessor :config, :basedir

      def initialize
        @basedir = nil
        @srccontentsdir = nil
        @outimagedir = nil
        @logger = ReVIEW.logger
        @configs = YamlConfig.new
      end

      def error(msg)
        @logger.error msg
        exit 1
      end

      def warn(msg)
        @logger.warn msg
      end

      def info(msg)
        @logger.info msg
      end

      def copy_config(outdir)
        @configs.copy(outdir)
      end

      def copy_catalog(outdir)
        yamlfile = @config['catalogfile']
        FileUtils.copy(File.join(@basedir, yamlfile), File.join(outdir, File.basename(yamlfile)))
      end

      def copy_contents(outdir)
        path = File.join(@basedir, @srccontentsdir)
        # outpath = File.join(outdir, srccontentsdir)
        # FileUtils.mkdir_p(outpath)
        # FileUtils.cp_r(Dir.glob(File.join(path, '*.re')), outpath)
        FileUtils.cp_r(Dir.glob(File.join(path, '*.re')), outdir)
      end

      def copy_images(outdir)
        imagedir = @config['imagedir']
        srcpath = File.join(@basedir, imagedir)
        outimagedir = File.basename(imagedir) # Re:VIEW not support sub-directory
        outpath = File.join(outdir, outimagedir)
        FileUtils.mkdir_p(outpath)
        image_ext = @config['image_ext']
        srcroot = Pathname.new(srcpath)
        image_ext.each { |ext|
          Dir.glob(File.join(srcpath, "**/*.#{ext}")).each { |srcimg|
            outimg = File.join(outpath, Pathname.new(srcimg).relative_path_from(srcroot))
            FileUtils.makedirs(File.dirname(outimg))
            FileUtils.cp(srcimg, outimg)
          }
        }
        @configs.rewrite_yml('imagedir', outimagedir)
      end

      def update_config(outdir)
        @configs.rewrite_yml('contentdir', '.')
        @configs.rewrite_yml('hook_beforetexcompile', 'null')
        @configs.rewrite_yml('texstyle', '["reviewmacro"]')
        @configs.rewrite_yml('chapterlink', 'null')
        pagesize = @config['starter']['pagesize'].downcase
        @configs.rewrite_yml_array('texdocumentclass', "[\"review-jsbook\", \"media=print,paper=#{pagesize}\"]")
      end

      def replace_compatible_block_command_outline(content, command, new_command, option_count)
        if option_count > 0
          content.gsub!(/^\/\/#{command}(?<option>(\[[^\r\n]*?\]){0,#{option_count}})(\[[^\r\n]*\])*{(?<inner>.*?)\/\/}/m, "//#{new_command}\\k<option>{\\k<inner>//}")
        else
          content.gsub!(/^\/\/#{command}(\[[^\r\n]*\])*{(?<inner>.*?)\/\/}/m, "//#{new_command}{\\k<inner>//}")
        end
      end

      def replace_compatible_block_command_to_outside(content, command, new_command, option_count, add_options="", new_body="")
        body = new_body
        body += '\n' unless body.empty?
        content.gsub!(/^\/\/#{command}(?<option>(\[[^\r\n]*?\]){0,#{option_count}})(\[[^\r\n]*\])*{(?<inner>.*?)\/\/}/m, "//#{new_command}\\k<option>#{add_options}{\n#{new_body}//}\\k<inner>")
      end

      def replace_block_command_outline(content, command, new_command, use_option)
        if use_option
          content.gsub!(/^\/\/#{command}(?<option>\[[^\r\n]*\])*{(?<inner>.*?)\/\/}/m, "//#{new_command}\\k<option>{\\k<inner>//}")
        else
          content.gsub!(/^\/\/#{command}(?<option>\[[^\r\n]*?\])*{(?<inner>.*?)\/\/}/m, "//#{new_command}{\\k<inner>//}")
        end
      end

      def delete_block_command_outer(content, command)
        content.gsub!(/^\/\/#{command}(\[[^\r\n]*?\])*{(?<inner>.*?)\/\/}\R/m, '\k<inner>')
      end

      def delete_block_command(content, command)
        content.gsub!(/^\/\/#{command}(\[[^\r\n]*?\])*{.*?\/\/}\R/m, '')
        content.gsub!(/^\/\/#{command}(\[.*?\])*\s*\R/, '')
      end

      def delete_inline_command(content, command)
        # FIXME: 入れ子のフェンス記法({}|$)
        content.gsub!(/@<#{command}>(?:(\$)|(?:({)|(\|)))((?:.*@<\w*>[\|${].*?[\|$}].*?|.*?)*)(?(1)(\$)|(?(2)(})|(\|)))/){"#{$4}"}
      end

      def replace_inline_command(content, command, new_command)
        content.gsub!(/@<#{command}>/, "@<#{new_command}>")
      end

      def replace_block_command_nested_boxed_article_i(content, box, depth)
        found = false
        content.dup.scan(/(^\/\/#{box})(\[[^\r\n]*?\])*(?:(\$)|(?:({)|(\|)))(.*?)(^\/\/)(?(3)(\$)|(?(4)(})|(\|)).*?[\r\n]+)/m) { |m|
          matched = m[0..-1].join
          inner = m[5]
          # info depth
          im = inner.match(/^\/\/(\w+)((\[.*?\])*)([$|{])/)
          unless im.nil?
            inner_cmd = im[1]
            inner_open = im[4]
            inner_opts = im[2]
            first_opt_m = inner_opts.match(/^\[(.*?)\]/)
            first_opt = ""

            # is_commentout = false
            is_commentout = true
            if first_opt_m
              first_opt_v = first_opt_m[1]
              unless first_opt_v.empty?
                if inner.match(/@<.*?>[$|{]#{first_opt}/)
                  is_commentout = false
                  first_opt = "\\[#{first_opt_v}\\]"
                end
              end
            end
            cmd_begin = m[0..4].join
            cmd_end = m[6..-1].join
            # check other fence inner block (block command has fence??)
            if inner_open == m[2..4].join
              # if same fence then cmd_end == inner_end
              if is_commentout
                inner.gsub!(/(^\/\/(\w+(\[.*?\]|))*#{inner_open})/, '#@#\1')
                content.gsub!(/#{Regexp.escape(matched)}/m, "#{cmd_begin}#{inner}#@##{cmd_end}")
              else
                imb = inner.match(/(\R((^\/\/\w+(\[.*?\])*)\s*)*^\/\/#{inner_cmd}#{first_opt}(\[.*?\])*#{inner_open}.*)\R/m)
                to_out_block = imb[1]
                inner.gsub!(/#{Regexp.escape(to_out_block)}/m, '')
                content.gsub!(/#{Regexp.escape(matched)}/m, "#{cmd_begin}#{inner}#{cmd_end}#{to_out_block}")
              end
            else
              close = inner_open == '{' ? '}' : inner_open
              if is_commentout
                inner.gsub!(/(^\/\/(\w+(\[.*?\]|))*#{inner_open})(.*?)(^\/\/#{close})/m, '#@#\1\2#@#\3')
                content.gsub!(/#{Regexp.escape(matched)}/m, "#{cmd_begin}#{inner}#{cmd_end}")
              else
                imb = inner.match(/\R((^\/\/\w+(\[.*?\])*)\s*)*^\/\/(#{inner_cmd})#{first_opt}(\[[^\r\n]*?\])*(?:(\$)|(?:({)|(\|)))(.*?)(^\/\/)(?(3)(\$)|(?(4)(})|(\|)))/m)
                to_out_block = imb[0]
                inner.gsub!(/#{Regexp.escape(to_out_block)}/m, '')
                content.gsub!(/#{Regexp.escape(matched)}/m, "#{cmd_begin}#{inner}#{cmd_end}#{to_out_block}")
              end
            end
            found = true
          end
        }
        if found
          replace_block_command_nested_boxed_article_i(content, box, depth+1)
        end
      end

      def replace_block_command_nested_boxed_article(content, box)
        replace_block_command_nested_boxed_article_i(content, box, 0)
      end

      def replace_block_command_nested_boxed_articles(content)
        unless Gem::Version.new(ReVIEW::VERSION) >= Gem::Version.new('5.0.0')
          replace_block_command_nested_boxed_article(content, 'note')
          replace_block_command_nested_boxed_article(content, 'memo')
          replace_block_command_nested_boxed_article(content, 'tip')
          replace_block_command_nested_boxed_article(content, 'info')
          replace_block_command_nested_boxed_article(content, 'warning')
          replace_block_command_nested_boxed_article(content, 'important')
          replace_block_command_nested_boxed_article(content, 'caution')
          replace_block_command_nested_boxed_article(content, 'notice')
        end
      end

      def replace_block_commentout(content)
        d = content.dup
        d.scan(/(^#@)(\++)(.*?)(^#@)(-+)/m) { |m|
          matched = m[0..-1].join
          inner = m[2]
          inner.gsub!(/(^.)/, '#@#\1')
          content.gsub!(/#{Regexp.escape(matched)}/m, "#@##{m[1]}#{inner}#@##{m[4]}")
        }
      end

      def replace_block_commentout_without_sampleout(content)
        d = content.dup
        d.gsub!(/(^\/\/sampleoutputbegin\[)(.*?)(\])(.*?)(^\/\/sampleoutputend)/m, '')
        d.scan(/(^#@)(\++)(.*?)(^#@)(-+)/m) { |m|
          matched = m[0..-1].join
          inner = m[2]
          inner.gsub!(/(^.)/, '#@#\1')
          content.gsub!(/#{Regexp.escape(matched)}/m, "#@##{m[1]}#{inner}#@##{m[4]}")
        }
      end

      def replace_sampleoutput(content)
        # replace_block_commentout_without_sampleout(content)
        content.dup.scan(/(^\/\/sampleoutputbegin\[)(.*?)(\].*?\R)(.*?)(^\/\/sampleoutputend)/m) { |m|
          matched = m[0..-1].join
          sampleoutputbegin = m[0..2].join
          sampleoutputend = m[4]
          option = m[1]
          inner = m[3]
          # inner.gsub!(/^\/\//, '//@<nop>{}')
          content.gsub!(/#{Regexp.escape(matched)}/m, "#{option}\n#@##{sampleoutputbegin}#{inner}#@##{sampleoutputend}")
        }
      end

      def replace_auto_ids(content, command, require_option_count)
        index = -1
        content.gsub!(/^\/\/#{command}\[(|\?)\]/) { |s| index += 1; "//#{command}[starter_auto_id_#{command}_#{index}]" }
        if require_option_count > 0
          while !content.gsub!(/(^\/\/#{command}(\[[^\[\]]*?\]){0,#{require_option_count-1}})($|{)/, '\1[]\3').nil?
          end
        end
      end

      def fix_deprecated_list(content)
        if Gem::Version.new(ReVIEW::VERSION) >= Gem::Version.new('4.0.0')
          content.gsub!(/^: (.*)/, ' : \1')
        end
      end

      def remove_starter_refid(content)
        # note - noteref
        content.dup.scan(/(@<noteref>)(?:(\$)|(?:({)|(\|)))(.*?)(?(2)(\$)|(?(3)(})|(\|)))/) { |m|
          matched = m[0..-1].join
          ref = m[4]
          n = content.match(/^\/\/note\[#{ref}\](\[.*?\])/)
          unless n.nil?
            content.gsub!(/#{Regexp.escape(matched)}/, n[1])
            content.gsub!(/^\/\/note\[#{ref}\](\[.*?\])/, '//note\1')
          else
            # content.gsub!(/#{Regexp.escape(matched)}/, "noteref<#{ref}>")
          end
        }
      end

      def remove_starter_options(content)
        # image border
        content.gsub!(/(^\/\/image\[.*?\]\[.*?\]\[.*?)((,|)border=[^,\]]*)(.*?\])/, '\1\4')
        # list lineno
        content.gsub!(/(^\/\/list\[.*?\]\[.*?\]\[.*?)((,|)lineno=[^,\]]*)(.*?\])/, '\1\4')
      end

      def expand_nested_inline_command(content)
        found = false
        content.dup.scan(/(@<.*?>)(?:(\$)|(?:({)|(\|)))(.*?)(?(2)(\$)|(?(3)(})|(\|)))/) { |m|
          matched = m.join
          body = m[4]
          im = body.match(/(.*)(@<.*?>)(?:(\$)|(?:({)|(\|)))(.*?)(?(3)(\$)|(?(4)(})|(\|)))(.*)/)
          if im.nil?
            im = body.match(/(.*)(@<.*?>)#{m[1..3].join}/)
            unless im.nil?
              outcmd_begin = m[0] + "$|{".gsub(m[1..3].join, '')
              outcmd_end = "$|}".gsub(m[5..7].join, '')
              rep = "#{outcmd_begin}#{body}#{outcmd_end}"
              content.gsub!(matched, rep)
              found = true
            end
          else
            outcmd_begin = m[0..3].join
            outcmd_end = m[5..7].join
            rep = "#{outcmd_begin}#{im[1]}#{outcmd_end}#{im[2..9].join}#{outcmd_begin}#{im[-1]}#{outcmd_end}"
            content.gsub!(matched, rep)
            found = true
          end
        }
        if found
          expand_nested_inline_command(content)
        end
      end

      def copy_embedded_contents(outdir, content)
        content.scan(/\#@mapfile\((.*?)\)/).each do |filepath|
          srcpath = File.join(@basedir, filepath)
          if File.exist?(srcpath)
            outpath = File.join(File.absolute_path(outdir), filepath)
            FileUtils.mkdir_p(File.dirname(outpath))
            FileUtils.cp(srcpath, outpath)
            update_content(outpath, outpath)
          end
        end
      end

      def add_linkurl_footnote(content)
        urls = {}
        content.dup.scan(/(^.*)(@<href>{)(.*?)(,)(.*?)(})(.*)$/) { |m|
          unless m[0].match(/^#@#/)
            matched = m.join
            prev = m[0]
            url = m[2]
            text = m[4]
            post = m[6]
            id = "link_auto_footnote#{urls.length}"
            urls[id] = url
            content.sub!(/#{Regexp.escape(matched)}$/, "#{prev}@<href>{#{url},#{text}} @<fn>{#{id}} #{post}")
          end
        }

        urls.each { |k,v|
          content.sub!(/(@<href>{#{v},.*?} @<fn>{#{k}}.*?\R\R)/m, "\\1//footnote[#{k}][#{v}]\n")
        }

        urls.each { |k,v|
          unless content.match(/\/\/footnote\[#{k}\]\[#{v}\]/)
            content << "//footnote[#{k}][#{v}]\n"
          end
        }
      end

      def update_content(outdir, contentfile)
        info contentfile
        content = File.read(contentfile)
        content.gsub!(/@<href>{(.*?)#.*?,(.*?)}/, '@<href>{\1,\2}')
        content.gsub!(/@<href>{(.*?)#.*?}/, '@<href>{\1}')
        linkurl_footnote = @config['starter']['linkurl_footnote']
        # table 内の @ コマンドは不安定らしい
        while !content.gsub!(/(\/\/table.*)@<br>{}(.*?\/\/})/m, "\\1#{@table_br_replace}\\2").nil? do
        end
        # 空セルが2行になることがあるらしい
        while !content.gsub!(/(\/\/table.*\s)\.(\s.*?\/\/})/m, "\\1#{@table_empty_replace}\\2").nil? do
        end
        # Re:VIEW Starter commands
        replace_compatible_block_command_outline(content, 'terminal', 'cmd', 1)
        replace_compatible_block_command_outline(content, 'cmd', 'cmd', 0)
        replace_compatible_block_command_to_outside(content, 'sideimage', 'image', 1, '[]')
        replace_block_command_outline(content, 'abstract', 'lead', true)
        delete_block_command(content, 'needvspace')
        delete_block_command(content, 'clearpage')
        delete_block_command(content, 'flushright')
        delete_block_command(content, 'centering')
        delete_block_command(content, 'noindent')
        delete_block_command(content, 'paragraphend')

        replace_inline_command(content, 'secref', 'hd')
        replace_inline_command(content, 'file', 'kw')
        replace_inline_command(content, 'hlink', 'href')
        replace_inline_command(content, 'B', 'strong')
        delete_inline_command(content, 'userinput')
        delete_inline_command(content, 'weak')
        delete_inline_command(content, 'cursor')
        # font size
        delete_inline_command(content, 'small')
        delete_inline_command(content, 'xsmall')
        delete_inline_command(content, 'xxsmall')
        delete_inline_command(content, 'large')
        delete_inline_command(content, 'xlarge')
        delete_inline_command(content, 'xxlarge')

        # fixed lack of options
        content.gsub!(/^\/\/list{/, '//list[][]{')

        if Gem::Version.new(ReVIEW::VERSION) >= Gem::Version.new('4.0.0')
          # empty caption is not allow
          content.gsub!(/^\/\/image\[(.*)\]\[\]{/, '//image[\1][ ]{')
        end

        # special command
        replace_sampleoutput(content)

        if linkurl_footnote
          add_linkurl_footnote(content)
        end

        # # br to blankline
        # content.gsub!(/(.*)@<br>{}(.*)/, '\1\n//blankline\n\2')

        # nested command
        replace_block_command_nested_boxed_articles(content)

        # empty ids
        replace_auto_ids(content, 'list', 2)
        replace_auto_ids(content, 'listnum', 2)

        # remove starter extension
        remove_starter_refid(content)
        remove_starter_options(content)

        # replace block comment
        replace_block_commentout(content)

        # special charactor
        content.gsub!('@<LaTeX>{}', 'LaTeX')
        content.gsub!('@<TeX>{}', 'TeX')
        content.gsub!('@<hearts>{}', '!HEART!')

        # nop replace must be last step
        content.gsub!('@<nop>$$', '@<b>$$')
        content.gsub!('@<nop>||', '@<b>||')
        content.gsub!('@<nop>{}', '@<b>{}')

        # expand nested inline command
        expand_nested_inline_command(content)

        # fix deprecated
        fix_deprecated_list(content)

        File.write(contentfile, content)
        copy_embedded_contents(outdir, content)
      end

      def update_content_files(outdir, contentdir, contentfiles)
        files = contentfiles.is_a?(String) ? contentfiles.split(/\R/) : contentfiles
        files.each do |content|
          contentpath = File.join(contentdir, content)
          unless File.exist?(contentpath)
            srcpath = File.join(File.join(@basedir, @srccontentsdir), content)
            # info srcpath
            if File.exist?(srcpath)
              FileUtils.cp(srcpath, contentdir)
            end
          end
          update_content(outdir, contentpath)
        end
      end

      def update_contents(outdir, options)
        yamlfile = @config['catalogfile']
        abspath = File.absolute_path(outdir)
        contentdir = abspath
        info 'replace starter block command'
        info 'replace starter inline command'
        if options['strict']
          catalog = ReVIEW::Catalog.new(File.open(File.join(abspath, yamlfile)))
          update_content_files(outdir, contentdir, catalog.predef())
          update_content_files(outdir, contentdir, catalog.chaps())
          update_content_files(outdir, contentdir, catalog.appendix())
          update_content_files(outdir, contentdir, catalog.postdef())
        else
          # copy_contents(outdir)
          contentsfiles = Pathname.glob(File.join(File.join(@basedir, @srccontentsdir), '*.re')).map(&:basename)
          update_content_files(outdir, contentdir, contentsfiles)
        end
      end

      def preproc_content_files(outdir, pp, contentdir, contentfiles)
        files = contentfiles.is_a?(String) ? contentfiles.split(/\R/) : contentfiles
        files.each do |content|
          contentpath = File.join(contentdir, content)
          if File.exist?(contentpath)
            info "preproc #{contentpath}"
            buf = StringIO.new
            pwd = Dir.pwd
            Dir.chdir(outdir)
            File.open(contentpath) { |f| pp.process(f, buf) }
            Dir.chdir(pwd)
            content = buf.string
            content.gsub!(/^#[@]map.*$/, '')
            content.gsub!(/^#[@]end$/, '')
            File.write(contentpath, content)
          end
        end
      end

      def preproc_contents(outdir, options)
        yamlfile = @config['catalogfile']
        abspath = File.absolute_path(outdir)
        contentdir = abspath
        param = {}
        param['tabwidth'] = options['tabwidth'].to_i
        pp = ReVIEW::Preprocessor.new(ReVIEW::Repository.new(param), param)

        if options['strict']
          catalog = ReVIEW::Catalog.new(File.open(File.join(abspath, yamlfile)))
          preproc_content_files(outdir, pp, contentdir, catalog.predef())
          preproc_content_files(outdir, pp, contentdir, catalog.chaps())
          preproc_content_files(outdir, pp, contentdir, catalog.appendix())
          preproc_content_files(outdir, pp, contentdir, catalog.postdef())
        else
          # copy_contents(outdir)
          contentsfiles = Pathname.glob(File.join(File.join(@basedir, @srccontentsdir), '*.re')).map(&:basename)
          preproc_content_files(outdir, pp, contentdir, contentsfiles)
        end
      end

      def clean_initial_project(outdir)
        FileUtils.rm(File.join(outdir, 'config.yml'))
        FileUtils.rm(File.join(outdir, 'catalog.yml'))
        FileUtils.rm_rf(File.join(outdir, 'images'))
        FileUtils.rm(Dir.glob(File.join(outdir, '*.re')))
      end

      def load_config(yamlfile)
        @configs.open(yamlfile)
        @config = @configs.config
        @basedir = @configs.basedir
        @srccontentsdir = @config['contentdir']
      end

      def create_initial_project(outdir, options)
        FileUtils.rm_rf(outdir) if options['force']
        ReVIEW::Init.execute(outdir)
        clean_initial_project(outdir)
      end

      def execute(yamlfile, outdir, options)
        @table_br_replace = options['table-br-replace']
        @table_empty_replace = options['table-empty-replace']
        load_config(yamlfile)
        create_initial_project(outdir, options)

        copy_config(outdir)
        copy_catalog(outdir)
        copy_images(outdir)
        update_config(outdir)
        update_contents(outdir, options)

        pwd = Dir.pwd
        Dir.chdir(outdir)
        updater = ReVIEW::Update.new
        updater.force = true
        # updater.backup = false
        begin
          updater.execute()
        rescue
        end
        Dir.chdir(pwd)

        if options['preproc']
          info 'preproc'
          preproc_contents(outdir, options)
        end
      end

      def self.execute(yamlfile, outdir, options)
        self.new.execute(yamlfile, outdir, options)
      end

    end
  end
end

