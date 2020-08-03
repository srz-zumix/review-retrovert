require "thor"
require "review/retrovert/converter"

module ReVIEW
  module Retrovert
    class CLI < Thor
      desc "convert {review_starter_configfile} {outdir}", "convert Re:VIEW Starter project to Re:VIEW project"
      method_option "force", aliases: "f", desc: 'Force output', type: :boolean
      method_option "strict", desc: 'Only process files registered in the catalog', type: :boolean
      method_option "table-br-replace", desc: '@<br>{} in table replace string', type: :string, default: ''
      method_option "table-empty-replace", desc: 'empty cell(.) in table replace string', type: :string, default: '　'
      def convert(review_starter_configfile, outdir)
        Converter.execute(review_starter_configfile, outdir, options)
      end

      desc "version", "show version"
      def version()
        puts VERSION
      end

    end
  end
end
