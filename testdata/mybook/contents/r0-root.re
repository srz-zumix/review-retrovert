= Retrovert テスト用

//blankline

test@<br>{}

== テスト

=== File

#@mapfile(contents/r0-inner.re)
#@end

//list[][][file=contents/test.txt]{
//}

//table[][][csv=on,file=contents/table.csv]{
//}

=== コマンド

===={subsubtest} Secref テスト用

secref: @<secref>{subsubtest}
secref: @<secref>{r0-root|subsubtest}
secref: @<secref>{01-install|RubyとTeXLiveのインストール}
#@# secref: @<secref>{01-install|Rubyのインストール}

==== footnote bar

//footnote[fnbar][test@<br>{}hoge]

==== others

Test @<foldhere>{} foldhere

