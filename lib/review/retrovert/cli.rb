require "thor"

module Review
  module Retrovert
    class CLI < Thor
      desc "convert {review_starter_project} {outdir}", "convert Re:VIEW Starter project to Re:VIEW project"
      def convert(starter, outdir)
        puts str.split("_").map{|w| w[0] = w[0].upcase; w}.join
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