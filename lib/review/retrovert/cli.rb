require "thor"
require "review/retrovert/converter"

module ReVIEW
  module Retrovert
    class CLI < Thor
      desc "convert {review_starter_configfile} {outdir}", "convert Re:VIEW Starter project to Re:VIEW project"
      method_option "force", aliases: "f", desc: 'Force output', type: :boolean
      method_option "strict", desc: 'Only process files registered in the catalog', type: :boolean
      method_option "preproc", desc: 'Execute preproc after conversion', type: :boolean
      method_option "tabwidth", desc: 'Preproc tabwidth option value', type: :numeric, default: 0
      method_option "table-br-replace", desc: '@<br>{} in table replace string (Default: empty)', type: :string, default: ''
      method_option "table-empty-replace", desc: 'empty cell(.) in table replace string (Default full-width space)', type: :string, default: '　'
      method_option "ird", desc: 'For IRD', type: :boolean
      method_option "no-update", desc: 'Do not Re:VIEW update', type: :boolean
      method_option "no-image", desc: 'Do not copy image', type: :boolean
      method_option "no-delegate-yaml", desc: 'review-retrovert creates an inherited file if the config.yml/catalog.yml file does not exist. Not done if no-delegate-yaml option is specified', type: :boolean
      def convert(review_starter_configfile, outdir)
        Converter.execute(review_starter_configfile, outdir, options)
      end

      desc "version", "show version"
      def version()
        puts VERSION
      end

      desc "review-version", "show Re:VIEW version"
      map "review-version" => :review_version
      def review_version()
        puts ReVIEW::VERSION
      end

    end
  end
end
