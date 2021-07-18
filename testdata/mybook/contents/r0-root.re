= Retrovert テスト用

#@mapfile(contents/r0-inner.re)
#@end

//blankline

test@<br>{}

== テスト

=== コマンド

===={subsubtest} Secref テスト用

secref: @<secref>{subsubtest}
secref: @<secref>{hoge}
secref: @<secref>{r0-root|subsubtest}
secref: @<secref>{01-install|RubyとTeXLiveのインストール}
#@# secref: @<secref>{01-install|Rubyのインストール}

==== footnote bar

//footnote[fnbar][test@<br>{}hoge]
