require "review"
require 'fileutils'
require "review/retrovert/yamlconfig"

module ReVIEW
  module Retrovert
    class Converter
      attr_accessor :config, :basedir

      def initialize
        @basedir = nil
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

      def copy_config(outdir)
        @configs.copy(outdir)
      end

      def copy_catalog(outdir)
        yamlfile =@config['catalogfile']
        FileUtils.copy(File.join(@basedir, yamlfile), File.join(outdir, File.basename(yamlfile)))
      end

      def copy_contents(outdir)
        contentdir = @config['contentdir']
        path = File.join(@basedir, contentdir)
        outpath = File.join(outdir, contentdir)
        FileUtils.mkdir_p(outpath)
        FileUtils.cp_r(Dir.glob(File.join(path, '*.re')), outpath)
      end

      def copy_images(outdir)
        imagedir = @config['imagedir']
        path = File.join(@basedir, imagedir)
        outpath = File.join(outdir, imagedir)
        FileUtils.mkdir_p(outpath)
        image_ext = @config['image_ext']
        image_ext.each { |ext|
          FileUtils.cp_r(Dir.glob(File.join(path, "*.#{ext}")), outpath)
        }
      end

      def update_config(outdir)
        # @configs.rewrite_yml('imagedir', 'images')
      end

      def clean_initial_project(outdir)
        FileUtils.rm(File.join(outdir, 'config.yml'))
        FileUtils.rm(File.join(outdir, 'catalog.yml'))
        FileUtils.rm_rf(File.join(outdir, 'images'))
        FileUtils.rm(Dir.glob(File.join(outdir, '*.re')))
      end

      def load_config(yamlfile)
        @config = ReVIEW::Configure.values
        error "#{yamlfile} not found." unless File.exist?(yamlfile)

        begin
          loader = ReVIEW::YAMLLoader.new
          @config.deep_merge!(loader.load_file(yamlfile))
        rescue => e
          error "yaml error #{e.message}"
        end

        @basedir = File.absolute_path(File.dirname(yamlfile))
        @configs.open(yamlfile)

        begin
          @config.check_version(ReVIEW::VERSION)
        rescue ReVIEW::ConfigError => e
          warn e.message
        end

        # version 2 compatibility
        unless @config['texdocumentclass']
          if @config.check_version(2, exception: false)
            @config['texdocumentclass'] = ['jsbook', 'uplatex,oneside']
          else
            @config['texdocumentclass'] = @config['_texdocumentclass']
          end
        end
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
        copy_contents(outdir)
        copy_images(outdir)
        update_config(outdir)

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

