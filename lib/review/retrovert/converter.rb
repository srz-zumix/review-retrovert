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
      end

      def replace_compatible_block_command_outline(content, command, new_command, option_count)
        content.gsub!(/^\/\/#{command}(?<option>(\[[^\r\n]*?\]){0,#{option_count}})(\[[^\r\n]*\])*{(?<inner>.*?)\/\/}/m, "//#{new_command}\\k<option>{\\k<inner>//}")
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

      def replace_block_command_nested_boxed_article(content, box)
        m = content.match(/^\/\/#{box}(.*?)^\/\/}/m)
        unless m.nil?
          inner = m[1]
          n = inner.match(/^\/\/(\w+\[.*?\])*{/)
          unless n.nil?
            inner.gsub!(/(^\/\/(\w+\[.*?\])*{)/, '#@#\1')
            content.gsub!(/^\/\/#{box}(.*?)^\/\/}/m, "//#{box}#{inner}#@#//}")
            replace_block_command_nested_boxed_article(content, box)
          end
        end
      end

      def replace_block_command_nested_boxed_articles(content)
        replace_block_command_nested_boxed_article(content, 'note')
        replace_block_command_nested_boxed_article(content, 'memo')
        replace_block_command_nested_boxed_article(content, 'tip')
        replace_block_command_nested_boxed_article(content, 'info')
        replace_block_command_nested_boxed_article(content, 'warning')
        replace_block_command_nested_boxed_article(content, 'important')
        replace_block_command_nested_boxed_article(content, 'caution')
        replace_block_command_nested_boxed_article(content, 'notice')
      end

      def replace_sampleoutput(content)
        m = content.match(/^\/\/sampleoutputbegin(.*?)^\/\/sampleoutputend/m)
        unless m.nil?
          sample = m[1]
          sample.gsub!(/^\/\//, '//@<nop>{}')
          content.gsub!(/(^\/\/sampleoutputbegin)(.*?)(^\/\/sampleoutputend)/m, "\\1#{sample}\\3")
          # while content.gsub!(/(^\/\/sampleoutputbegin.*?)(^\/\/.*?^\/\/sampleoutputend)/m, '\1@<nop>{}\2').nil? do
          # end
          content.gsub!(/^\/\/sampleoutputbegin(?<option>\[.*?\])*/, "\\k<option>\n//embed{")
          content.gsub!(/^\/\/sampleoutputend/, '//}')
        end
      end

      def replace_empty_ids(content, command)
        index = -1
        content.gsub!(/^\/\/#{command}\[\]/) { |s| index += 1; "//#{command}[starter_auto_id_#{command}_#{index}]" }
      end

      def expand_nested_inline_command(content)
        found = false
        content.dup().scan(/(@<.*?>)(?:(\$)|(?:({)|(\|)))(.*?)(?(2)(\$)|(?(3)(})|(\|)))/) { |m|
          matched = m.join()
          body = m[4]
          im = body.match(/(.*)(@<.*?>)(?:(\$)|(?:({)|(\|)))(.*?)(?(3)(\$)|(?(4)(})|(\|)))(.*)/)
          unless im.nil?
            outcmd_begin = m[0..3].join()
            outcmd_end = m[5..7].join()
            rep = "#{outcmd_begin}#{im[1]}#{outcmd_end}#{im[2..9].join()}#{outcmd_begin}#{im[-1]}#{outcmd_end}"
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

      def update_content(outdir, contentfile)
        info contentfile
        content = File.read(contentfile)
        content.gsub!(/@<href>{(.*?)#.*?,(.*?)}/, '@<href>{\1,\2}')
        content.gsub!(/@<href>{(.*?)#.*?}/, '@<href>{\1}')
        # table 内の @ コマンドは不安定らしい
        while !content.gsub!(/(\/\/table.*)@<br>{}(.*?\/\/})/m, "\\1#{@table_br_replace}\\2").nil? do
        end
        # 空セルが2行になることがあるらしい
        while !content.gsub!(/(\/\/table.*\s)\.(\s.*?\/\/})/m, "\\1#{@table_empty_replace}\\2").nil? do
        end
        # Re:VIEW Starter commands
        replace_compatible_block_command_outline(content, 'terminal', 'cmd', 1)
        replace_compatible_block_command_to_outside(content, 'sideimage', 'image', 1, '[]')
        replace_block_command_outline(content, 'abstract', 'lead', true)
        delete_block_command(content, 'needvspace')
        delete_block_command(content, 'clearpage')
        delete_block_command(content, 'flushright')
        delete_block_command(content, 'centering')
        delete_block_command(content, 'noindent')

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

        # special command
        replace_sampleoutput(content)

        # nested command
        replace_block_command_nested_boxed_articles(content)

        # empty ids
        replace_empty_ids(content, 'list')
        replace_empty_ids(content, 'listnum')

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
        updater.execute()
        Dir.chdir(pwd)
      end

      def self.execute(yamlfile, outdir, options)
        self.new.execute(yamlfile, outdir, options)
      end

    end
  end
end

