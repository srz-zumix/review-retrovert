require 'review'

module ReVIEW
  module Retrovert
    class Preprocessor
      @preprocessor = nil

      def initialize(param)
        if Gem::Version.new(ReVIEW::VERSION) >= Gem::Version.new('5.2.0')
          @preprocessor = ReVIEW::Preprocessor.new(param)
        else
          @preprocessor = ReVIEW::Preprocessor.new(ReVIEW::Repository.new(param), param)
        end
      end

      def process(path)
        if Gem::Version.new(ReVIEW::VERSION) >= Gem::Version.new('5.2.0')
          @preprocessor.process(path)
        else
          buf = StringIO.new
          File.open(path) { |f| @preprocessor.process(f, buf) }
          buf.string
        end
      end
    end

    class ReViewCompat
      class << self
        def has_nested_minicolumn()
          Gem::Version.new(ReVIEW::VERSION) >= Gem::Version.new('5.0.0')
        end

        def is_need_space_term_list()
          Gem::Version.new(ReVIEW::VERSION) >= Gem::Version.new('4.0.0')
        end

        def is_allow_empty_image_caption()
          v = Gem::Version.new(ReVIEW::VERSION)
          v < Gem::Version.new('4.0.0') || v >= Gem::Version.new('5.1.0')
        end

        def has_bou()
          Gem::Version.new(ReVIEW::VERSION) >= Gem::Version.new('3.2.0')
        end

        def Preprocessor(param)
          Preprocessor.new(param)
        end

        def Catalog(path)
          ReVIEW::Catalog.new(File.open(path))
        end

      end
    end
  end
end
