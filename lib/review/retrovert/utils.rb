require 'csv'

module ReVIEW
  module Retrovert
    class Utils
      class << self

        # tsv to csv
        def Tsv2Csv(infile, outfile)
          File.open(infile, 'r') do |file|
            CSV.open(outfile, 'w') do |csv|
              file.each_line do |line|
                csv << line.chomp.split(/\t+/)
              end
            end
          end
        end

      end
    end
  end
end
