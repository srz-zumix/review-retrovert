require 'yaml'

module ReVIEW
  module Retrovert
    class YamlConfig
      attr_accessor :config_files, :basedir, :basename

      def initialize
        @config_files = []
      end

      def error(msg)
        ReVIEW.logger.error msg
        exit 1
      end

      def open(yamlfile)
        @basedir = File.absolute_path(File.dirname(yamlfile))
        @basename = File.basename(yamlfile)

        file_queue = [ @basename ]
        loaded_files = {}
        while file_queue.present?
          current_file = file_queue.shift
          begin
            yaml = YAML.load_file(File.expand_path(current_file, @basedir))
          rescue => e
            error "load error #{e.message}"
          end
          if yaml.class == FalseClass
            raise "#{current_file} is malformed."
          end
          @config_files << current_file

          if yaml.key?('inherit')
            inherit_files = parse_inherit(yaml, yamlfile, loaded_files)
            file_queue = inherit_files + file_queue
          end
        end
      end

      def parse_inherit(yaml, yamlfile, loaded_files)
        files = []

        yaml['inherit'].reverse_each do |item|
          inherit_file = File.expand_path(item, File.dirname(yamlfile))

          # Check loop
          if loaded_files[inherit_file]
            error "Found circular YAML inheritance '#{inherit_file}' in #{yamlfile}."
          end

          loaded_files[inherit_file] = true
          files << item
        end

        files
      end

      def copy(outdir)
        @config_files.each { |current_file|
          FileUtils.copy(File.expand_path(current_file, @basedir), File.join(outdir, current_file))
        }
        @basename = outdir
      end

      def rewrite_yml_(yamlfile, key, val)
        content = File.read(yamlfile)
        content.gsub!(/^(\s*)#{key}:.*$/, '\1' + "#{key}: #{val}")
        File.write(yamlfile, content)
      end

      def rewrite_yml(key, val)
        config_files.each { |current_file|
          rewrite_yml_(File.join(@basename, current_file), key, val)
        }
      end

    end
  end
end