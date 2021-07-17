module ReVIEW
  module Retrovert
    class ReViewDef
      class << self
        attr_accessor :r_option_inner

        def is_has_id_block_command(cmd)
          no_id_block_command().none?(cmd)
        end

        def fence_close(open)
          case open
          when "$", "|" then
            return open
          when "{" then
            return "}"
          end
          nil
        end

        # id 指定しないブロックコマンド
        def no_id_block_command()
          [
            "emlist",
            "emlistnum",
            "emtable",
            "note",
            "memo",
            "info",
            "warning",
            "important",
            "caution",
            "notice",
          ]
        end

        # id 参照するインラインコマンド
        def id_ref_inline_commands()
          [
            "list",
            "img",
            "table",
            "eq",
          ]
        end

        # キャプションを取得する
        def get_caption(line)
          m = line.match(/^\/\/(\w+?)((\[#{r_option_inner}\])*)([$|{])*$/)
          if m
            cmd = m[1]
            options = m[2]
            if options
              if no_id_block_command().include?(cmd)
                n = options.match(/\[(#{r_option_inner})\].*/)
                return n[1] if n
              else
                n = options.match(/\[#{r_option_inner}\]\[(#{@r_option_inner})\].*/)
                return n[1] if n
              end
            end
          end
          nil
        end
      end

      self.r_option_inner = '(.*?\\[.*?\\\\\\].*?)*.*?'
    end
  end
end
