# -*- coding: utf-8 -*-

##
## ReVIEW::LATEXBuilderクラスを拡張する
##

require 'review/latexbuilder'


module ReVIEW

  defined?(LATEXBuilder)  or raise "internal error: LATEXBuilder not found."


  module LATEXBuilderForIRD
    # def headline(level, label, caption)
    #   if level >= 4
    #     puts '\needspace{3zh}'
    #   end
    #   super(level,label,caption)
    #   puts '\nopagebreak[4]'
    # end

    def ul_begin
      blank
      puts '\begin{reviewitemize}'
    end
    def ul_end
      puts '\end{reviewitemize}'
      blank
    end
  end

  class LATEXBuilder
    prepend LATEXBuilderForIRD

  #   def headline(level, label, caption)
  #     _, anchor = headline_prefix(level)
  #     headline_name = HEADLINE[level]
  #     if @chapter.is_a?(ReVIEW::Book::Part)
  #       if @book.config.check_version('2', exception: false)
  #         headline_name = 'part'
  #       elsif level == 1
  #         headline_name = 'part'
  #         puts '\begin{reviewpart}'
  #       end
  #     end
  #     prefix = ''
  #     if level > @book.config['secnolevel'] || (@chapter.number.to_s.empty? && level > 1)
  #       prefix = '*'
  #     end
  #     blank unless @output.pos == 0
  #     @doc_status[:caption] = true
  #     puts macro(headline_name + prefix, compile_inline(caption))
  #     puts '\nopagebreak[4]'
  #     @doc_status[:caption] = nil
  #     if prefix == '*' && level <= @book.config['toclevel'].to_i
  #       puts "\\addcontentsline{toc}{#{headline_name}}{#{compile_inline(caption)}}"
  #     end
  #     if level == 1
  #       puts macro('label', chapter_label)
  #     else
  #       puts macro('label', sec_label(anchor))
  #       puts macro('label', label) if label
  #     end
  #     puts '\nopagebreak[4]'
  #   rescue
  #     error "unknown level: #{level}"
  #   end
  end
end
