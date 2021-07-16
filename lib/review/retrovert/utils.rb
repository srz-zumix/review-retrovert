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

        def NormalizeCSVArray(ar)
          ar&.each do |c|
            c.gsub!(/\A"|"\z/, '')
            c.gsub!(/^\s*/, '')
            c.gsub!(/[\r\n]/, '')
          end
          ar
        end

        def GenerateTsv(c)
          CSV.generate_line(Utils::NormalizeCSVArray(c), col_sep: "\t")
        end

      end
    end
  end
end
