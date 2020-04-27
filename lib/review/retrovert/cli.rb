require "thor"
require "review/retrovert/converter"

module ReVIEW
  module Retrovert
    class CLI < Thor
      desc "convert {review_starter_configfile} {outdir}", "convert Re:VIEW Starter project to Re:VIEW project"
      method_option "force", aliases: "f", desc: 'force output', type: :boolean
      def convert(review_starter_configfile, outdir)
        Converter.execute(review_starter_configfile, outdir, options)
      end

      desc "snake {CamelCaseString}", "convert {CamelCaseString} to {snake_case_string}"
      def snake(str)
        puts str
          .gsub(/([A-Z]+)([A-Z][a-z])/, '\1_\2')
          .gsub(/([a-z\d])([A-Z])/, '\1_\2')
          .tr("-", "_")
          .downcase
      end
    end
  end
end