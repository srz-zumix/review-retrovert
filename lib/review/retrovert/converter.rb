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

      def replace_inline_command(content, command, sub)

      end

      def delete_inline_command(content, command)
        # FIXME: 入れ子のフェンス記法({}|$)
        content.gsub!(/@<#{command}>(?:(\$)|(?:({)|(\|)))((?:.*@<\w*>[\|${].*?[\|$}].*?|.*?)*)(?(1)(\$)|(?(2)(})|(\|)))/){"#{$4}"}
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
        content.gsub!(/(\/\/sideimage\[.*?\]\[.*?\])\[.*?\]/, '\1')
        content.gsub!(/\/\/sideimage/, '//image')
        content.gsub!(/@<href>{(.*?)#.*?}/, '@<href>{\1}')
        while !content.gsub!(/(\/\/table.*)@<br>(.*?\/\/})/m, '\1\2').nil? do
        end
        delete_inline_command(content , 'xsmall')
        delete_inline_command(content , 'weak')
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
        info 'replace //sideimage to //image'
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

