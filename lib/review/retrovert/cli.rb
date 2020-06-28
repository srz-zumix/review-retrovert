require "thor"
require "review/retrovert/converter"

module ReVIEW
  module Retrovert
    class CLI < Thor
      desc "convert {review_starter_configfile} {outdir}", "convert Re:VIEW Starter project to Re:VIEW project"
      method_option "force", aliases: "f", desc: 'Force output', type: :boolean
      method_option "strict", desc: 'Only process files registered in the catalog', type: :boolean
      def convert(review_starter_configfile, outdir)
        Converter.execute(review_starter_configfile, outdir, options)
      end
    end
  end
end
