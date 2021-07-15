require "review"
require 'fileutils'
require 'tmpdir'
require "review/retrovert/yamlconfig"
require "review/retrovert/reviewdef"
require "review/retrovert/utils"

module ReVIEW
  module Retrovert
    class Converter
      attr_accessor :config, :basedir

      def initialize
        @basedir = nil
        @srccontentsdir = nil
        @outimagedir = nil
        @logger = ReVIEW.logger
        @configs = YamlConfig.new
        @embeded_contents = []
        @catalog_contents = []
        @talk_shortcuts = {}
        @ird = false
        @talklist_replace_cmd = "note"
        @desclist_replace_cmd = "info"

        @r_option_inner = '(.*?\\[.*?\\\\\\].*?)*.*?'
      end

      def error(msg)
        @logger.error msg
        exit 1
      end

      def warn(msg)
        @logger.warn msg
      end

      def info(msg)
        @logger.info msg
      end

      def copy_config(outdir)
        @configs.copy(outdir)
      end

      def copy_catalog(outdir)
        yamlfile = @config['catalogfile']
        FileUtils.copy(File.join(@basedir, yamlfile), File.join(outdir, File.basename(yamlfile)))
      end

      def copy_contents(outdir)
        path = File.join(@basedir, @srccontentsdir)
        # outpath = File.join(outdir, srccontentsdir)
        # FileUtils.mkdir_p(outpath)
        # FileUtils.cp_r(Dir.glob(File.join(path, '*.re')), outpath)
        FileUtils.cp_r(Dir.glob(File.join(path, '*.re')), outdir)
      end

      def get_out_imagedir(outdir)
        imagedir = @config['imagedir']
        outimagedir = File.basename(imagedir) # Re:VIEW not support sub-directory
        outpath = File.join(outdir, outimagedir)
        return outpath
      end

      def store_out_image(outdir)
        outpath = get_out_imagedir(outdir)
        if File.exist?(outpath)
          dir = Dir.mktmpdir('review-retrovert')
          FileUtils.mv(Dir.glob(File.join(outpath, "**/*")), dir)
          return dir
        end
        return nil
      end

      def restore_out_image(outpath, tmpdir)
        if File.exist?(tmpdir)
          FileUtils.mkdir_p(outpath)
          FileUtils.mv(Dir.glob(File.join(tmpdir, "**/*")), outpath)
          FileUtils.rm_rf(tmpdir)
        end
      end

      def copy_images(outdir, store_image_dir)
        imagedir = @config['imagedir']
        outimagedir = File.basename(imagedir) # Re:VIEW not support sub-directory
        outpath = get_out_imagedir(outdir)
        FileUtils.mkdir_p(outpath)
        if store_image_dir
          restore_out_image(outpath, store_image_dir)
        else
          srcpath = File.join(@basedir, imagedir)
          image_ext = @config['image_ext']
          srcroot = Pathname.new(srcpath)
          image_ext.each { |ext|
            Dir.glob(File.join(srcpath, "**/*.#{ext}")).each { |srcimg|
              outimg = File.join(outpath, Pathname.new(srcimg).relative_path_from(srcroot))
              FileUtils.makedirs(File.dirname(outimg))
              FileUtils.cp(srcimg, outimg)
            }
          }
        end
        @configs.rewrite_yml('imagedir', outimagedir)
      end

      def copy_wards(outdir, words_file)
        new_file = words_file
        FileUtils.mkdir_p(File.join(outdir, File.dirname(words_file)))
        if File.extname(words_file) == ".csv"
          FileUtils.copy(File.join(@basedir, words_file), File.join(outdir, new_file))
        else
          new_file += ".csv"
          Utils.Tsv2Csv(File.join(@basedir, words_file), File.join(outdir, new_file))
        end
        new_file
      end

      def update_config(outdir)
        @configs.rewrite_yml('contentdir', '.')
        @configs.rewrite_yml('hook_beforetexcompile', 'null')
        @configs.rewrite_yml('texstyle', '["reviewmacro"]')
        pagesize = @config['starter']['pagesize'].downcase
        jsbook_config = "media=print,paper=#{pagesize}"

        # words
        words_files = @config['words_file']
        if words_files.is_a?(Array)
          new_words_files = []
          words_files.each do |words_file|
            new_words_files.push copy_wards(outdir, words_file)
          end
          @configs.rewrite_yml('words_file', "[#{new_words_files.join(',')}]")
        else
          new_words_file = copy_wards(outdir, words_files)
          @configs.rewrite_yml('words_file', new_words_file)
        end

        if @ird
          # # リュウミン Pr6N R-KL 12.5Q 22H (9pt = 12.7Q 15.5pt = 21.8Q(H))
          # texdocumentclass: ["review-jsbook", "media=ebook,openany,paper=b5,fontsize=9pt,baselineskip=15.5pt,head_space=15mm,gutter=22mm,footskip=16mm,line_length=45zw,number_of_lines=38"]
          jsbook_config = "media=ebook,openany,paper=b5,fontsize=9pt,baselineskip=15.5pt,head_space=15mm,gutter=22mm,footskip=16mm,line_length=45zw,number_of_lines=38"
        end
        @configs.rewrite_yml_array('texdocumentclass', "[\"review-jsbook\", \"#{jsbook_config}\"]")
        @config['retrovert'].each{ |k,v|
          unless v..is_a?(Hash)
            @configs.commentout_root_yml(k)
          end
        }
        if @ird
          @configs.rewrite_yml('chapterlink', 'null')
        end
      end

      def replace_compatible_block_command_outline(content, command, new_command, option_count, begin_option_pos=0)
        content.gsub!(/^\/\/#{command}(\[[^\r\n]*?\]){0,#{begin_option_pos}}(?<option>(\[[^\r\n]*?\]){0,#{option_count}})(\[[^\r\n]*\])*{(?<inner>.*?)\/\/}/m, "//#{new_command}\\k<option>{\\k<inner>//}")
        content.gsub!(/^\/\/#{command}(\[[^\r\n]*?\]){0,#{begin_option_pos}}(?<option>(\[[^\r\n]*?\]){0,#{option_count}})(\[[^\r\n]*\])*$/, "//#{new_command}\\k<option>")
        # if begin_option_pos > 0
        #   content.gsub!(/^\/\/#{command}(\[[^\r\n]*?\]){0,#{begin_option_pos}}{(?<inner>.*?)\/\/}/m, "//#{new_command}{\\k<inner>//}")
        #   content.gsub!(/^\/\/#{command}(\[[^\r\n]*?\]){0,#{begin_option_pos}}$/, "//#{new_command}")
        # end
      end

      def exclude_exta_option(content, cmd, max_option_num)
        replace_compatible_block_command_outline(content, cmd, cmd, max_option_num)
      end

      def starter_caption_to_text(content, command, n)
        content.gsub!(/^\/\/#{command}(?<option>(\[[^\r\n]*?\]){0,#{n-1}})\[(?<caption>#{@r_option_inner})\](?<post>.*)$/, "\\k<caption>\n//#{command}\\k<option>\\k<post>")
      end

      def replace_compatible_block_command_to_outside(content, command, new_command, option_count, add_options="", new_body="")
        body = new_body
        body += '\n' unless body.empty?
        content.gsub!(/^\/\/#{command}(?<option>(\[[^\r\n]*?\]){0,#{option_count}})(\[[^\r\n]*\])*{(?<inner>.*?)\/\/}/m, "//#{new_command}\\k<option>#{add_options}{\n#{new_body}//}\\k<inner>")
      end

      def replace_block_command_outline(content, command, new_command, use_option)
        if use_option
          content.gsub!(/^\/\/#{command}(?<option>\[[^\r\n]*\])*{(?<inner>.*?)\/\/}/m, "//#{new_command}\\k<option>{\\k<inner>//}")
        else
          content.gsub!(/^\/\/#{command}(?<option>\[[^\r\n]*?\])*{(?<inner>.*?)\/\/}/m, "//#{new_command}{\\k<inner>//}")
        end
      end

      def delete_block_command_outer(content, command)
        content.gsub!(/^\/\/#{command}(\[[^\r\n]*?\])*{(?<inner>.*?)\/\/}\R/m, '\k<inner>')
      end

      def delete_block_command(content, command)
        content.gsub!(/^\/\/#{command}(\[[^\r\n]*?\])*{.*?\/\/}\R/m, '')
        content.gsub!(/^\/\/#{command}(\[.*?\])*\s*\R/, '')
      end

      def replace_block_command_nested_boxed_article_i(content, box, depth)
        found = false
        content.dup.scan(/(^\/\/#{box})(\[[^\r\n]*?\])*(?:(\$)|(?:({)|(\|)))(.*?)(^\/\/)(?(3)(\$)|(?(4)(})|(\|)).*?[\r\n]+)/m) { |m|
          matched = m[0..-1].join
          inner = m[5]
          # info depth
          im = inner.match(/^\/\/(?<command>\w+)(?<options>(\[#{@r_option_inner}\])*)(?<open>[$|{])/)
          unless im.nil?
            inner_cmd = im['command']
            inner_open = im['open']
            inner_opts = im['options']
            id_opt = ""

            # is_commentout = false
            is_commentout = true
            if ReViewDef::is_has_id_block_command(inner_cmd)
              first_opt_m = inner_opts.match(/^\[(.*?)\]/)
              if first_opt_m
                first_opt_v = first_opt_m[1]
                unless first_opt_v.empty?
                  if inner.match(/@<#{ReViewDef::id_ref_inline_commands().join('|')}>[$|{]#{first_opt_v}/)
                    is_commentout = false
                    id_opt = "\\[#{first_opt_v}\\]"
                  end
                end
              end
            end
            cmd_begin = m[0..4].join
            cmd_end = m[6..-1].join
            # check other fence inner block (block command has fence??)
            if inner_open == m[2..4].join
              # if same fence then cmd_end == inner_end
              if is_commentout
                inner.gsub!(/(^\/\/(\w+(\[#{@r_option_inner}\]|))*#{inner_open})/, '#@#\1')
                rep = "#{cmd_begin}#{inner}#@##{cmd_end}"
                content.gsub!(matched) { |mm| rep }
              else
                imb = inner.match(/(\R((^\/\/\w+(\[#{@r_option_inner}\])*)\s*)*^\/\/#{inner_cmd}#{id_opt}(\[#{@r_option_inner}\])*#{inner_open}.*)\R/m)
                to_out_block = imb[1]
                inner.gsub!(/#{Regexp.escape(to_out_block)}/m, '')
                rep = "#{cmd_begin}#{inner}#{cmd_end}#{to_out_block}"
                content.gsub!(matched) { |mm| rep }
              end
            else
              close = inner_open == '{' ? '}' : inner_open
              if is_commentout
                inner.gsub!(/(^\/\/(\w+(\[#{@r_option_inner}\]|))*#{inner_open})(.*?)(^\/\/#{close})/m, '#@#\1\2#@#\3')
                rep = "#{cmd_begin}#{inner}#{cmd_end}"
                content.gsub!(matched) { |mm| rep }
              else
                imb = inner.match(/\R((^\/\/\w+(\[#{@r_option_inner}\])*)\s*)*^\/\/(#{inner_cmd})#{id_opt}(\[[^\r\n]*?\])*(?:(\$)|(?:({)|(\|)))(.*?)(^\/\/)(?(3)(\$)|(?(4)(})|(\|)))/m)
                to_out_block = imb[0]
                inner.gsub!(/#{Regexp.escape(to_out_block)}/m, '')
                rep = "#{cmd_begin}#{inner}#{cmd_end}#{to_out_block}"
                content.gsub!(matched) { |mm| rep }
              end
            end
            found = true
          end
        }
        if found
          replace_block_command_nested_boxed_article_i(content, box, depth+1)
        end
      end

      def replace_block_command_nested_boxed_article(content, box)
        replace_block_command_nested_boxed_article_i(content, box, 0)
      end

      def replace_block_command_nested_boxed_articles(content)
        unless Gem::Version.new(ReVIEW::VERSION) >= Gem::Version.new('5.0.0')
          replace_block_command_nested_boxed_article(content, 'note')
          replace_block_command_nested_boxed_article(content, 'memo')
          replace_block_command_nested_boxed_article(content, 'tip')
          replace_block_command_nested_boxed_article(content, 'info')
          replace_block_command_nested_boxed_article(content, 'warning')
          replace_block_command_nested_boxed_article(content, 'important')
          replace_block_command_nested_boxed_article(content, 'caution')
          replace_block_command_nested_boxed_article(content, 'notice')
        end
      end

      # #@+++ ~ #@--- to #@#+++ #@#~ #@#---
      def replace_block_commentout(content)
        d = content.dup
        d.scan(/(^#@)(\++\R)(.*?)(^#@)(-+)/m) { |m|
          matched = m[0..-1].join
          inner = m[2]
          inner.gsub!(/^/, '#@#')
          rep = "#@##{m[1]}#{inner}#@##{m[4]}"
          content.gsub!(matched) { |mm| rep }
        }
      end

      def replace_block_commentout_without_sampleout(content)
        d = content.dup
        d.gsub!(/(^\/\/sampleoutputbegin\[)(.*?)(\])(.*?)(^\/\/sampleoutputend)/m, '')
        d.scan(/(^#@)(\++\R)(.*?)(^#@)(-+)/m) { |m|
          matched = m[0..-1].join
          inner = m[2]
          inner.gsub!(/^/, '#@#\1')
          rep = "#@##{m[1]}#{inner}#@##{m[4]}"
          content.gsub!(matched) { |mm| rep }
        }
      end

      def replace_sampleoutput(content)
        # replace_block_commentout_without_sampleout(content)
        content.dup.scan(/(^\/\/sampleoutputbegin\[)(.*?)(\].*?\R)(.*?)(^\/\/sampleoutputend)/m) { |m|
          matched = m[0..-1].join
          sampleoutputbegin = m[0..2].join
          sampleoutputend = m[4]
          option = m[1]
          inner = m[3]
          # inner.gsub!(/^\/\//, '//@<nop>{}')
          rep = "#{option}\n#@##{sampleoutputbegin}#{inner}#@##{sampleoutputend}"
          content.gsub!(matched) { |mm| rep }
        }
      end

      def replace_auto_ids(content, command, require_option_count)
        index = -1
        content.gsub!(/^\/\/#{command}\[(|\?)\]/) { |s| index += 1; "//#{command}[starter_auto_id_#{command}_#{index}]" }
        if require_option_count > 0
          while !content.gsub!(/(^\/\/#{command}(\[[^\[\]]*?\]){0,#{require_option_count-1}})($|{)/, '\1[]\3').nil?
          end
        end
      end

      def fix_deprecated_list(content)
        if Gem::Version.new(ReVIEW::VERSION) >= Gem::Version.new('4.0.0')
          content.gsub!(/^: (.*)/, ' : \1')
        end
      end

      def remove_starter_refid(content)
        # note - noteref
        content.dup.scan(/(@<noteref>)(?:(\$)|(?:({)|(\|)))(.*?)(?(2)(\$)|(?(3)(})|(\|)))/) { |m|
          matched = m[0..-1].join
          ref = m[4]
          n = content.match(/^\/\/note\[#{ref}\](\[.*?\])/)
          unless n.nil?
            rep = n[1]
            content.gsub!(matched) { |mm| rep }
            content.gsub!(/^\/\/note\[#{ref}\](\[.*?\])/, '//note\1')
          else
            # content.gsub!(matched, "noteref<#{ref}>")
          end
        }
      end

      def remove_option_param(content, commands, n, param)
        content.gsub!(/(?<prev>^\/\/(#{commands.join('|')})(\[.*?\]){#{n-1}}\[.*?)((,|)\s*#{param}=[^,\]]*)(?<post>.*?\])/, '\k<prev>\k<post>')
      end

      def remove_starter_options(content)
        # image width
        content.gsub!(/(^\/\/image\[.*?\]\[.*?\]\[.*?)(,|)(\s*)width=\s*([0-9.]+)%(?<after>.*?\])/) { |m|
          m.gsub!(/width=\s*([0-9.]+)%/) {
            value = $1
            "scale=#{value.to_i * 0.01}"
          }
        }
        remove_option_param(content, ["image"], 3, "width")
        # image border
        remove_option_param(content, ["image"], 3, "border")
        # image pos
        remove_option_param(content, ["image"], 3, "pos")
        # list lineno
        remove_option_param(content, ["list"], 3, "lineno")
      end

      # talklist to //#{cmd}[]{ //emlist[]{}... }
      def talklist_to_nested_contents_list(content, cmd)
        content.gsub!(/^\/\/talklist(.*?){/, "//#{cmd}\\1{")
        content.gsub!(/^\/\/talk(?<options>\[#{@r_option_inner}\]\[#{@r_option_inner}\])\[(?<body>#{@r_option_inner})\]$/, "//talk\\k<options>{\n\\k<body>\n//}")
        content.gsub!(/^\/\/t(?<options>\[#{@r_option_inner}\])\[(?<body>#{@r_option_inner})\]$/, "//talk\\k<options>{\n\\k<body>\n//}")
        content.gsub!(/^\/\/(t|talk)((\[#{@r_option_inner}\])*){/) { |s|
          m = s.scan(/(\[(#{@r_option_inner})\])/)
          # 1st option is image id
          avatar = m[0][1]
          first_option = m[0][0]
          traling_options = m[1..-1].map{ |x| x[0] }.join
          if avatar.length > 0
            kv = @talk_shortcuts[avatar]
            if kv&.key?('image')
              "//indepimage[#{kv['image']}]\n//emlist[]#{traling_options}{"
            elsif kv&.key?('name')
              "//emlist[#{kv['name']}]{"
            else
              "//indepimage#{first_option}\n//emlist[]#{traling_options}{"
            end
          else
            "//emlist#{first_option}#{traling_options}{"
          end
        }
      end

      # desclist to //#{cmd}[]{ //emlist[]{}... }
      def desclist_to_nested_contents_list(content, cmd)
        content.gsub!(/^\/\/desclist(.*?){/, "//#{cmd}\\1{")
        content.gsub!(/^\/\/desc(?<options>\[#{@r_option_inner}\])\[(?<body>#{@r_option_inner})\]$/, "//desc\\k<options>{\n\\k<body>\n//}")
        content.gsub!(/^\/\/desc((\[#{@r_option_inner}\])*){/, '//emlist\1{')
      end

      def starter_list_to_nested_contents_list(content)
        # talklist
        talklist_to_nested_contents_list(content, @talklist_replace_cmd)
        # desclist
        desclist_to_nested_contents_list(content, @desclist_replace_cmd)
        replace_block_command_nested_boxed_article(content, 'emlist')
      end

      def convert_table_option(content)
        r_table = /^(?<matched>\/\/table\[#{@r_option_inner}\]\[#{@r_option_inner}\]\[(?<options>#{@r_option_inner})\](?<open>.))$/
        content.dup.scan(r_table) { |m|
          matched = m[0]
          options = m[1]
          options.split(',').each { |option|
            if option.match(/\s*csv\s*=\s*on\s*/)
              open = m[2]
              close = ReViewDef::fence_close(open)
              if close
                tm = content.match(/#{Regexp.escape(matched)}(.*?)^\/\/#{close}/m)
                outer = tm[0]
                inner = tm[1]
                im = inner.match(/(.*?)([=\-]{12,}\R)(.*)/m)
                if im
                  header = im[1]
                  sep = im[2]
                  body = im[3]
                  new_header = ""
                  new_body = ""
                  CSV.parse(header) do |h|
                    new_header += CSV.generate_line(h, col_sep: "\t")
                  end
                  CSV.parse(body) do |c|
                    new_body += CSV.generate_line(c, col_sep: "\t")
                  end
                  content.gsub!(outer, "#{matched}#{new_header}#{sep}#{new_body}//#{close}")
                else
                  new_body = ""
                  CSV.parse(inner) do |c|
                    new_body += CSV.generate_line(c, col_sep: "\t")
                  end
                  content.gsub!(outer, "#{matched}#{new_body}//#{close}")
                end
              end
            end
          }
        }
      end

      # tsize[builder][xxx] to tsize[|builder|xxx]
      def replace_tsize(content)
        content.gsub!(/^\/\/tsize\[(.*?)\]\[(.*?)\]/) {
          builder = $1
          builder = "" if $1 == '*'
          "//tsize[|#{builder}|#{$2}]"
        }
      end

      def copy_embedded_contents(outdir, content)
        content.scan(/\#@mapfile\((.*?)\)/).each do |filepath|
          srcpath = File.join(@basedir, filepath)
          if File.exist?(srcpath)
            outpath = File.join(File.absolute_path(outdir), filepath)
            FileUtils.mkdir_p(File.dirname(outpath))
            FileUtils.cp(srcpath, outpath)
            @embeded_contents.push(filepath[0])
            update_content(outpath, outpath)
          end
        end
      end

      def make_id_label(name)
        name.gsub(/[^A-Za-z0-9]/, '_')
      end

      def add_linkurl_footnote(content, filename)
        urls = {}
        content.dup.scan(/(^.*)(@<href>{)(.*?)(,)(.*?)(})(.*)$/) { |m|
          unless m[0].match(/^#@#/)
            matched = m.join
            prev = m[0]
            url = m[2]
            text = m[4]
            post = m[6]
            id = "#{make_id_label(filename)}_link_auto_footnote#{urls.length}"
            urls[id] = url
            content.sub!(/#{Regexp.escape(matched)}$/, "#{prev}@<href>{#{url},#{text}} @<fn>{#{id}} #{post}")
          end
        }

        urls.each { |k,v|
          content.sub!(/(@<href>{#{v},.*?} @<fn>{#{k}}.*?\R\R)/m, "\\1//footnote[#{k}][#{v}]\n")
        }

        urls.each { |k,v|
          unless content.match(/\/\/footnote\[#{k}\]\[#{v}\]/)
            content << "//footnote[#{k}][#{v}]\n"
          end
        }
      end

      def replace_starter_command(content)
        replace_compatible_block_command_outline(content, 'program', 'list', 2)
        replace_compatible_block_command_outline(content, 'terminal', 'cmd', 1, 1)
        replace_compatible_block_command_outline(content, 'output', 'list', 3)
        replace_compatible_block_command_to_outside(content, 'sideimage', 'image', 1, '[]')
        replace_block_command_outline(content, 'abstract', 'lead', true)
        delete_block_command(content, 'vspace')
        delete_block_command(content, 'needvspace')
        delete_block_command(content, 'clearpage')
        delete_block_command(content, 'flushright')
        delete_block_command(content, 'paragraphend')
        delete_block_command_outer(content, 'centering')

        # convert starter option
        convert_table_option(content)

        # delete starter option
        # exclude_exta_option(content, 'cmd', 0)
        starter_caption_to_text(content, 'cmd', 1)
        exclude_exta_option(content, 'imgtable', 2)
        exclude_exta_option(content, 'table', 2)
        # exclude_exta_option(content, 'tsize', 1)
        replace_tsize(content)

        # delete IRD unsupported commands
        if @ird
          delete_block_command(content, 'noindent')
        end

        # chapterauthor
        content.gsub!(/^\/\/chapterauthor\[(.*?)\]/, "//lead{\n\\1\n//}")
        # talklist/desclist
        starter_list_to_nested_contents_list(content)
      end

      def delete_inline_command(content, command)
        # 既に入れ子は展開されている前提
        content.gsub!(/@<#{command}>(?:(\$)|(?:({)|(\|)))(.*?)(?(1)(\$)|(?(2)(})|(\|)))/, '\4')
      end

      def do_replace_inline_command(content, command, &blk)
        # 既に入れ子は展開されている前提
        content.gsub!(/@<#{command}>(?:(\$)|(?:({)|(\|)))(.*?)(?(1)(\$)|(?(2)(})|(\|)))/) { blk.call([$1, $2, $3].join, $4, [$5, $6, $7].join) }
      end

      def replace_inline_command(content, command, new_command)
        do_replace_inline_command(content, command) { |open, inner, close|
          "@<#{new_command}>#{open}#{inner}#{close}"
        }
      end

      # @<XXX>{AAA@<YYY>{BBB}} to @<XXX>{AAA}@<YYY>{BBB}
      def expand_nested_inline_command(content)
        found = false
        content.dup.scan(/(@<.*?>)(?:(\$)|(?:({)|(\|)))(.*?)(?(2)(\$)|(?(3)(})|(\|)))/) { |m|
          matched = m.join
          body = m[4]
          im = body.match(/(.*)(@<.*?>)(?:(\$)|(?:({)|(\|)))(.*?)(?(3)(\$)|(?(4)(})|(\|)))(.*)/)
          if content.match(/^#@#.*#{Regexp.escape(matched)}.*/)
            next
          end
          if im.nil?
            # for {}
            im2 = body.match(/(.*)(@<.*?>)#{Regexp.escape(m[1..3].join)}(.*)/)
            unless im2.nil?
              rep = ""
              if im2[3].length > 0
                outcmd_begin = m[0..3].join + im2[1..2].join + "$|{".gsub(m[1..3].join, '')[0]
                outcmd_end = "$|}".gsub(m[5..7].join, '')[0]
                rep = "#{outcmd_begin}#{im2[3]}#{outcmd_end}"
              else
                rep = m[0..3].join + im2[1]
              end
              content.gsub!(matched) { |mm| rep }
              found = true
            else
              # for |$
              if body.match(/.*@<.*?>$/)
                outcmd_fence = m[1..3].join
                incmd_fence = "$|".gsub(outcmd_fence, '')
                rep = "#{m[0..3].join}#{body}#{incmd_fence}"
                content.gsub!(/#{Regexp.escape(matched)}(.*?)#{Regexp.escape(outcmd_fence)}/, "#{rep}\\1#{incmd_fence}")
                found = true
              end
            end
          else
            outcmd_begin = m[0..3].join
            outcmd_end = m[5..7].join
            rep = ""
            rep += "#{outcmd_begin}#{im[1]}#{outcmd_end}" if im[1].length > 0
            rep += "#{im[2..9].join}"
            rep += "#{outcmd_begin}#{im[-1]}#{outcmd_end}" if im[-1].length > 0
            content.gsub!(matched) { |mm| rep }
            found = true
          end
        }
        if found
          expand_nested_inline_command(content)
        end
      end

      def replace_starter_inline_command(content)
        expand_nested_inline_command(content)

        replace_inline_command(content, 'secref', 'hd')
        replace_inline_command(content, 'file', 'kw')
        replace_inline_command(content, 'hlink', 'href')
        replace_inline_command(content, 'B', 'strong')
        replace_inline_command(content, 'W', 'wb')
        replace_inline_command(content, 'term', 'idx')
        replace_inline_command(content, 'termnoidx', 'hidx')
        delete_inline_command(content, 'userinput')
        delete_inline_command(content, 'weak')
        delete_inline_command(content, 'cursor')
        # font size
        delete_inline_command(content, 'small')
        delete_inline_command(content, 'xsmall')
        delete_inline_command(content, 'xxsmall')
        delete_inline_command(content, 'large')
        delete_inline_command(content, 'xlarge')
        delete_inline_command(content, 'xxlarge')

        do_replace_inline_command(content, 'par') { |open, inner, close| "@<br>#{open}#{close}" }
        do_replace_inline_command(content, 'qq' ) { |open, inner, close| "\"#{inner}\"" }
      end

      def update_content(outdir, contentfile)
        info contentfile
        filename = File.basename(contentfile, '.*')
        content = File.read(contentfile)
        content.gsub!(/@<href>{(.*?)#.*?,(.*?)}/, '@<href>{\1,\2}')
        content.gsub!(/@<href>{(.*?)#.*?}/, '@<href>{\1}')
        linkurl_footnote = @config['starter']['linkurl_footnote']
        # table 内の @ コマンドは不安定らしい
        while !content.gsub!(/(\/\/table.*)@<br>{}(.*?\/\/})/m, "\\1#{Regexp.escape(@table_br_replace)}\\2").nil? do
        end
        # 空セルが2行になることがあるらしい
        while !content.gsub!(/(\/\/table.*\s)\.(\s.*?\/\/})/m, "\\1#{Regexp.escape(@table_empty_replace)}\\2").nil? do
        end
        # noop を最後に消すためにダミーに変える
        content.gsub!('@<nop>$$', '@<must_be_replace_nop>$must_be_replace_nop$')
        content.gsub!('@<nop>||', '@<must_be_replace_nop>|must_be_replace_nop|')
        content.gsub!('@<nop>{}', '@<must_be_replace_nop>{must_be_replace_nop}')

        # Re:VIEW Starter commands
        replace_starter_command(content)

        # fixed lack of options
        content.gsub!(/^\/\/list{/, '//list[][]{')
        # empty br line to blankline
        content.gsub!(/^\s*@<br>{}\s*$/, '//blankline')

        if Gem::Version.new(ReVIEW::VERSION) >= Gem::Version.new('4.0.0')
          # empty caption is not allow
          content.gsub!(/^\/\/image\[(.*)\]\[\]{/, '//image[\1][ ]{')
        end

        # special command
        replace_sampleoutput(content)

        if linkurl_footnote
          add_linkurl_footnote(content, filename)
        end

        # nested command
        replace_block_command_nested_boxed_articles(content)

        # empty ids
        replace_auto_ids(content, 'table', 2)
        replace_auto_ids(content, 'list', 2)
        replace_auto_ids(content, 'listnum', 2)

        # remove starter extension
        remove_starter_refid(content)
        remove_starter_options(content)

        # replace block comment
        replace_block_commentout(content)

        # special charactor
        content.gsub!('@<LaTeX>{}', 'LaTeX')
        content.gsub!('@<TeX>{}', 'TeX')
        content.gsub!('@<hearts>{}', '!HEART!')

        replace_starter_inline_command(content)

        # fix deprecated
        fix_deprecated_list(content)

        if @ird
          # br to blankline
          content.gsub!(/(.*)@<br>{}$/, "\\1\n\n")
          content.gsub!(/(.*)@<br>{}(.*)$/, "\\1\n\n\\2")
        end

        # nop replace must be last step
        content.gsub!('@<must_be_replace_nop>$must_be_replace_nop$', '@<b>$$')
        content.gsub!('@<must_be_replace_nop>|must_be_replace_nop|', '@<b>||')
        content.gsub!('@<must_be_replace_nop>{must_be_replace_nop}', '@<b>{}')

        File.write(contentfile, content)
        copy_embedded_contents(outdir, content)
      end

      def update_content_files(outdir, contentdir, contentfiles)
        files = contentfiles.is_a?(String) ? contentfiles.split(/\R/) : contentfiles
        files.each do |content|
          contentpath = File.join(contentdir, content)
          srccontentpath = File.join(@srccontentsdir, content)
          if @embeded_contents.include?(srccontentpath)
            info "skip copy maped file #{contentpath}"
            next
          end
          unless File.exist?(contentpath)
            srcpath = File.join(@basedir, srccontentpath)
            # info srcpath
            if File.exist?(srcpath)
              FileUtils.cp(srcpath, contentdir)
            end
          end
          update_content(outdir, contentpath)
        end
      end

      def update_contents(outdir, options)
        yamlfile = @config['catalogfile']
        abspath = File.absolute_path(outdir)
        contentdir = abspath
        info 'replace starter block command'
        info 'replace starter inline command'
        catalog = ReVIEW::Catalog.new(File.open(File.join(abspath, yamlfile)))
        update_content_files(outdir, contentdir, @catalog_contents)
        unless options['strict']
          all_contentsfiles = Pathname.glob(File.join(File.join(@basedir, @srccontentsdir), '*.re')).map(&:basename)
          contentsfiles = all_contentsfiles.select{ |path| ! @catalog_contents.include?(path.to_s) }
          update_content_files(outdir, contentdir, contentsfiles)
        end
      end

      def preproc_content_files(outdir, pp, contentdir, contentfiles)
        files = contentfiles.is_a?(String) ? contentfiles.split(/\R/) : contentfiles
        files.each do |content|
          contentpath = File.join(contentdir, content)
          if File.exist?(contentpath)
            info "preproc #{contentpath}"
            buf = StringIO.new
            pwd = Dir.pwd
            Dir.chdir(outdir)
            File.open(contentpath) { |f| pp.process(f, buf) }
            Dir.chdir(pwd)
            content = buf.string
            content.gsub!(/^#[@]map.*$/, '')
            content.gsub!(/^#[@]end$/, '')
            File.write(contentpath, content)
          end
        end
      end

      def preproc_contents(outdir, options)
        yamlfile = @config['catalogfile']
        abspath = File.absolute_path(outdir)
        contentdir = abspath
        param = {}
        param['tabwidth'] = options['tabwidth'].to_i
        pp = ReVIEW::Preprocessor.new(ReVIEW::Repository.new(param), param)

        if options['strict']
          catalog = ReVIEW::Catalog.new(File.open(File.join(abspath, yamlfile)))
          preproc_content_files(outdir, pp, contentdir, @catalog_contents)
        else
          contentsfiles = Pathname.glob(File.join(File.join(@basedir, @srccontentsdir), '*.re')).map(&:basename)
          preproc_content_files(outdir, pp, contentdir, contentsfiles)
        end
      end

      def update_sty(outdir, options)
        # FileUtils.cp(File.join(@basedir, 'sty/review-custom.sty'), File.join(outdir, 'sty/review-custom.sty'))
        if @ird
          FileUtils.cp(File.join(__dir__, 'sty/ird.sty'), File.join(outdir, 'sty/ird.sty'))
          file = File.open(File.join(outdir, 'sty/review-custom.sty'), 'a')
          file.puts('\RequirePackage{ird}')
        end
      end

      def update_ext(outdir, options)
        if @ird
          FileUtils.cp(File.join(__dir__, 'ext/review-ext.rb'), File.join(outdir, 'review-ext.rb'))
        end
      end

      def clean_initial_project(outdir)
        FileUtils.rm(File.join(outdir, 'config.yml'))
        FileUtils.rm(File.join(outdir, 'catalog.yml'))
        FileUtils.rm_rf(File.join(outdir, 'images'))
        FileUtils.rm(Dir.glob(File.join(outdir, '*.re')))
      end

      def add_catalog_contents(contentfiles)
        files = contentfiles.is_a?(String) ? contentfiles.split(/\R/) : contentfiles
        @catalog_contents.concat(files)
      end

      def load_config(yamlfile)
        @configs.open(yamlfile)
        @config = @configs.config
        @basedir = @configs.basedir
        @srccontentsdir = @config['contentdir']

        catalog = ReVIEW::Catalog.new(File.open(@configs.catalogfile()))
        add_catalog_contents(catalog.predef())
        add_catalog_contents(catalog.chaps())
        add_catalog_contents(catalog.appendix())
        add_catalog_contents(catalog.postdef())
      end

      def create_initial_project(outdir, options)
        FileUtils.rm_rf(outdir) if options['force']
        ReVIEW::Init.execute(outdir)
        clean_initial_project(outdir)
      end

      def execute(yamlfile, outdir, options)
        @table_br_replace = options['table-br-replace']
        @table_empty_replace = options['table-empty-replace']
        @ird = options['ird']
        load_config(yamlfile)
        store_image_dir = store_out_image(outdir) if options['no-image']
        create_initial_project(outdir, options)
        @talk_shortcuts = @config['starter']['talk_shortcuts']

        copy_config(outdir)
        copy_catalog(outdir)
        copy_images(outdir, store_image_dir)
        update_config(outdir)
        update_contents(outdir, options)
        update_sty(outdir, options)
        update_ext(outdir, options)

        pwd = Dir.pwd
        Dir.chdir(outdir)
        updater = ReVIEW::Update.new
        updater.force = true
        # updater.backup = false
        begin
          updater.execute()
        rescue
        end
        Dir.chdir(pwd)

        if options['preproc']
          info 'preproc'
          preproc_contents(outdir, options)
        end
      end

      def self.execute(yamlfile, outdir, options)
        self.new.execute(yamlfile, outdir, options)
      end

    end
  end
end

