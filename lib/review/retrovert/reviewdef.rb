module ReVIEW
  module Retrovert
    class ReViewDef
      class << self
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
            "emtable",
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
      end
    end
  end
end
