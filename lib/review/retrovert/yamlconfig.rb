require 'yaml'

module ReVIEW
  module Retrovert
    class YamlConfig
      attr_accessor :config, :config_files, :retrovert_configs, :basedir, :basename

      def initialize
        @config_files = []
        @retrovert_configs = []
        @config = ReVIEW::Configure.values
      end

      def error(msg)
        ReVIEW.logger.error msg
        exit 1
      end

      def open(yamlfile)
        error "#{yamlfile} not found." unless File.exist?(yamlfile)

        begin
          loader = ReVIEW::YAMLLoader.new
          @config.deep_merge!(loader.load_file(yamlfile))
        rescue => e
          error "yaml error #{e.message}"
        end

        @basedir = File.absolute_path(File.dirname(yamlfile))
        @basename = File.basename(yamlfile)

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

        file_queue = [ @basename ]
        loaded_files = {}
        while file_queue.present?
          current_file = file_queue.shift
          yaml = load_yaml(File.expand_path(current_file, @basedir))
          @config_files << current_file

          if yaml.key?('inherit')
            inherit_files = parse_inherit(yaml, yamlfile, loaded_files)
            file_queue = inherit_files + file_queue
          end
          if yaml.key?('retrovert')
            @retrovert_configs << current_file
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
        @basedir = outdir
        rewrite_retrovert_yml()
      end

      def commentout(yamlfile, key)
        content = File.read(yamlfile)
        content.gsub!(/^(\s*)#{key}:(.*)$/, "#\\1#{key}:\\2")
        File.write(yamlfile, content)
      end

      def commentout_root_yml(key)
        commentout(File.join(@basedir, @basename), key)
      end

      def rewrite_yml_(yamlfile, key, val)
        content = File.read(yamlfile)
        content.gsub!(/^(\s*)#{key}:.*$/, "\\1#{key}: #{val}")
        File.write(yamlfile, content)
      end

      def rewrite_yml(key, val)
        config_files.each { |current_file|
          rewrite_yml_(File.join(@basedir, current_file), key, val)
        }
      end

      def rewrite_yml_array_(yamlfile, key, val)
        content = File.read(yamlfile)
        content.gsub!(/^(\s*)#{key}:\s*\[.*?\]/m, '\1' + "#{key}: #{val}")
        File.write(yamlfile, content)
      end

      def rewrite_yml_array(key, val)
        config_files.each { |current_file|
          rewrite_yml_array_(File.join(@basedir, current_file), key, val)
        }
      end

      def rewrite_retrovert_yml()
        @retrovert_configs.each { |current_file|
          yamlfile = File.expand_path(current_file, @basedir)
          yaml = load_yaml(yamlfile)
          retrovert = yaml['retrovert']
          yaml.deep_merge!(retrovert)
          yaml.delete('retrovert')
          # Convert Date/Time objects to strings to avoid YAML loading issues
          # with Ruby 3.1+ and review 5.3 or earlier
          yaml = convert_dates_to_strings(yaml)
          # YAML.dump(yaml, File.open(yamlfile, "w"))
          content = Psych.dump(yaml)
          content.gsub!('---','')
          File.write(yamlfile, content)
        }
      end

      # Recursively convert Date and Time objects to ISO 8601 strings
      def convert_dates_to_strings(obj)
        case obj
        when Hash
          obj.transform_values { |v| convert_dates_to_strings(v) }
        when Array
          obj.map { |v| convert_dates_to_strings(v) }
        when Date, Time
          obj.strftime('%Y-%m-%d')
        else
          obj
        end
      end

      def load_yaml(filepath)
        begin
          yaml = YAML.load_file(filepath, permitted_classes: [Date, Time])
        rescue => e
          error "load error #{e.message}"
        end
        if yaml.class == FalseClass
          raise "#{current_file} is malformed."
        end
        return yaml
      end

      def path()
        File.join(@basedir, @basename)
      end

      def catalogfile()
        File.join(@basedir, @config['catalogfile'])
      end

    end
  end
end
