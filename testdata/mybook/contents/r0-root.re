//makechaptitlepage[toc=on]

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

//table[][]{
A	B
--------------
a	b@<br>{}b
.	X
X	.
//}

==={subsubtest} コマンド

==== Secref テスト用

secref: @<secref>{subsubtest}
secref: @<secref>{r0-root|subsubtest}
secref: @<secref>{01-install|RubyとTeXLiveのインストール}
#@# secref: @<secref>{01-install|Rubyのインストール}

==== footnote bar

//footnote[fnbar][test@<br>{}hoge]

==== others

//terminal{
Test @<foldhere>{} foldhere
//}

@<ruby>{虎空棘魚, タイガーシーラカンス}

5 + 5 = @<tcy>{10}
@<tcy>{YES}
