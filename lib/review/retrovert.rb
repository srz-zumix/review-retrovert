require "review/retrovert/version"
require "review/retrovert/cli"

module Review
  module Retrovert
    class Error < StandardError; end
      def hello
        puts("hello")
      end
  end
end
