# -*- coding: utf-8 -*-

##
## change ReVIEW source code
##

require_relative './review-book'          ## Book::Baseクラスを修正
require_relative './review-compiler'      ## Compilerクラスを修正
require_relative './review-builder'       ## Builderクラスを修正
require_relative './review-latexbuilder'  ## LaTeX用の機能を修正
require_relative './review-htmlbuilder'   ## HTML用の機能を修正
require_relative './review-textbuilder'   ## テキスト用の機能を修正
#require_relative './review-pdfmaker'     ## PDF用の機能を修正 (for Rake task)
require_relative './review-epubbuilder'   ## テキスト用の機能を修正
require_relative './review-webmaker'      ## Webページ用の機能を修正
require_relative './review-tocparser'     ## Web用目次作成機能を修正


module ReVIEW


  Book::Base.class_eval do

    ## 環境変数 $STARTER_CHAPTER で指定された章だけをコンパイルするよう改造
    def each_input_file()
      env_starter = ENV['STARTER_CHAPTER']
      env_starter = nil unless env_starter.present?
      found = false
      self.parts.each do |part|
        yield part, nil if part.name.present? && !env_starter
        part.chapters.each do |chap|
          next if env_starter && env_starter != chap.name
          found = true
          yield nil, chap
        end
      end
      if env_starter && !found
        raise "ERROR: chapter file '#{env_starter}.re' not found. ($STARTER_CHAPTER='#{env_starter}')"
      end
      nil
    end

  end


  class PDFMaker

    ### original: 2.4, 2.5
    #def call_hook(hookname)
    #  return if !@config['pdfmaker'].is_a?(Hash) || @config['pdfmaker'][hookname].nil?
    #  hook = File.absolute_path(@config['pdfmaker'][hookname], @basehookdir)
    #  if ENV['REVIEW_SAFE_MODE'].to_i & 1 > 0
    #    warn 'hook configuration is prohibited in safe mode. ignored.'
    #  else
    #    system_or_raise("#{hook} #{Dir.pwd} #{@basehookdir}")
    #  end
    #end
    ### /original

    def call_hook(hookname)    # review-pdfmaker がエラーにならないために
      d = @config['pdfmaker']
      return unless d.is_a?(Hash)
      return unless d[hookname]
      if ENV['REVIEW_SAFE_MODE'].to_i & 1 > 0
        warn 'hook configuration is prohibited in safe mode. ignored.'
        return
      end
      ## hookname が文字列の配列なら、それらを全部実行する
      basehookdir = @basehookdir
      [d[hookname]].flatten.each do |hook|
        script = File.absolute_path(hook, basehookdir)
        ## 拡張子が .rb なら、rubyコマンドで実行する（ファイルに実行属性がなくてもよい）
        if script.end_with?('.rb')
          ruby = ruby_fullpath()
          ruby = "ruby" unless File.exist?(ruby)
          system_or_raise(ruby, script, Dir.pwd, basehookdir)
        else
          system_or_raise(script, Dir.pwd, basehookdir)
        end
      end
    end

    private
    def ruby_fullpath
      require 'rbconfig'
      c = RbConfig::CONFIG
      return File.join(c['bindir'], c['ruby_install_name']) + c['EXEEXT'].to_s
    end

  end unless defined?(Maker)


end
