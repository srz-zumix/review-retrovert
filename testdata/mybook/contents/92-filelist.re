#@# -*- coding: utf-8 -*-
= ファイルとフォルダ

//abstract{
プロジェクトのzipファイル（例：@<file>{mybook.zip}）を解凍してできるファイルとフォルダの解説です。
//}


#@#=={appendix-files} ファイルとフォルダの解説

#@# : @<file>{Gemfile}
#@#	@<code>{gem}コマンドが使用します。通常は気にしなくていいです。
 : @<file>{README.md}
	プロジェクトの説明が書かれたファイルです。
	ユーザが好きなように上書きすることを想定しています。
 : @<file>{Rakefile}
	@<code>{rake}コマンドが使用します。
	コマンドを追加する場合は、このファイルは変更せず、かわりに「@<file>{lib/tasks/*.rake}」を変更してください。
 : @<file>{catalog.yml}
	原稿ファイルが順番に並べられたファイルです。
	原稿ファイルを追加した・削除した場合は、このファイルも編集します。
#@# : @<file>{catalog.yml.orig}
#@#	Re:VIEWでのオリジナルファイルです。
 : @<file>{config-starter.yml}
	Starter独自の設定ファイルです。
	Starterでは設定ファイルとして「@<file>{cofnig.yml}」と「@<file>{cofnig-starter.yml}」の両方を使います。
 : @<file>{config.yml}
	Re:VIEWの設定ファイルです。
	Starterによりいくつか変更と拡張がされています。
#@# : @<file>{config.yml.orig}
#@#	Re:VIEWでのオリジナルファイルです。
 : @<file>{contents/}
	原稿ファイルを置くフォルダです@<fn>{fn-lacsx}。
 : @<file>{contents/*.re}
	原稿ファイルです。
	章(Chapter)ごとにファイルが分かれます。
 : @<file>{css/}
	HTMLファイルで使うCSSファイルを置くフォルダです。
	ePubで使うのはこれではなくて@<file>{style.css}なので注意してください。
 : @<file>{images/}
	画像ファイルを置くフォルダです。
	この下に章(Chapter)ごとのサブフォルダを作ることもできます。
 : @<file>{layouts/layout.epub.erb}
	原稿ファイルからePubファイルを生成するためのテンプレートです。
 : @<file>{layouts/layout.html5.erb}
	原稿ファイルからHTMLファイルを生成するためのテンプレートです。
 : @<file>{layouts/layout.tex.erb}
	原稿ファイルからLaTeXファイルを生成するためのテンプレートです。
 : @<file>{lib/hooks/beforetexcompile.rb}
	LaTeXファイルをコンパイルする前に編集するスクリプトです。
 : @<file>{lib/ruby/*.rb}
	StarterによるRe:VIEWの拡張を行うRubyスクリプトです。
 : @<file>{lib/ruby/mytasks.rake}
	ユーザ独自のRakeコマンドを追加するためのファイルです。
 : @<file>{lib/ruby/review.rake}
	Re:VIEWで用意されているRakeタスクのファイルです。
	Starterによって変更や拡張がされています。
 : @<file>{lib/ruby/review.rake.orig}
	Starterによって変更や拡張がされる前の、オリジナルのタスクファイルです。
 : @<file>{lib/ruby/starter.rake}
	Starterが追加したRakeタスクが定義されたファイルです。
 : @<file>{locale.yml}
	国際化用のファイルです。
	たとえば「リスト1.1」を「プログラム1.1」に変更したい場合は、このファイルを変更します。
 : @<file>{mybook-epub/}
	ePubファイルを生成するときの中間生成ファイルが置かれるフォルダです。
	通常は気にする必要はありません。
 : @<file>{mybook-pdf/}
	PDFファイルを生成するときの中間生成ファイルが置かれるフォルダです。
	@<LaTeX>{}ファイルをデバッグするときに必要となりますが、通常は気にする必要はありません。
 : @<file>{mybook.epub}
	生成されたePubファイルです。
	ファイル名はプロジェクトによって異なります。
 : @<file>{mybook.pdf}
	生成されたPDFファイルです。
	ファイル名はプロジェクトによって異なります。
 : @<file>{review-ext.rb}
	Re:VIEWを拡張するためのファイルです。
	このファイルから「@<file>{lib/ruby/*.rb}」が読み込まれています。
 : @<file>{sty/}
	@<LaTeX>{}で使うスタイルファイルが置かれるフォルダです。
 : @<file>{sty/jumoline.sty}
	@<LaTeX>{}で使うスタイルファイルのひとつです。
 : @<file>{sty/mycolophon.sty}
	奥付@<fn>{fn-7ypmf}の内容が書かれたスタイルファイルです。
	奥付を変更したい場合はこのファイルを編集します。
 : @<file>{sty/mystyle.sty}
	ユーザが独自に@<LaTeX>{}マクロを定義・上書きするためのファイルです。
	中身は空であり、ユーザが自由に追加して構いません。
 : @<file>{sty/mytextsize.sty}
	PDFにおける本文の高さと幅を定義したファイルです。
	@<LaTeX>{}では最初に本文の高さと幅を決める必要があるので、他のスタイルファイルから分離されてコンパイルの最初に読み込めるようになっています。
 : @<file>{sty/mytitlepage.sty}
	大扉@<fn>{fn-cq9ws}の内容が書かれたスタイルファイルです。
	大扉のデザインを変更したい場合はこのファイルを編集します。
 : @<file>{sty/starter.sty}
	Starter独自のスタイルファイルです。
	ここに書かれた@<LaTeX>{}マクロを変更したい場合は、このファイルを変更するよりも「@<file>{sty/mystyle.sty}」に書いたほうがバージョンアップがしやすくなります。
 : @<file>{sty/starter-codeblock.sty}
	プログラムコードやターミナルの@<LaTeX>{}マクロが定義されています。
 : @<file>{sty/starter-color.sty}
	色のカスタマイズ用です。
 : @<file>{sty/starter-font.sty}
	フォントのカスタマイズ用です。
 : @<file>{sty/starter-headline.sty}
	章(Chapter)や節(Section)や項(Subsection)の@<LaTeX>{}マクロが定義されたファイルです。
 : @<file>{sty/starter-note.sty}
	ノートブロックの@<LaTeX>{}マクロが定義されています。
 : @<file>{sty/starter-section.sty}
	以前の、章や節の@<LaTeX>{}マクロ定義です。
	もはや使ってませんが、starter.styを書き換えれば使えます。
 : @<file>{sty/starter-talklist.sty}
	会話形式の@<LaTeX>{}マクロが定義されています。
 : @<file>{sty/starter-toc.sty}
	目次のカスタマイズ用です。
 : @<file>{sty/starter-misc.sty}
	その他、各種のマクロ定義です。
 : @<file>{sty/starter-util.sty}
	Starterのスタイルファイルで使われるマクロが定義されています。
 : @<file>{style.css}
	ePubで使われるCSSスタイルファイルです。

//footnote[fn-lacsx][原稿ファイルを置くフォルダ名は「@<file>{config.yml}」の「@<code>|contentdir: contents|」で変更できます。]
//footnote[fn-7ypmf][@<em>{奥付}とは、本のタイトルや著者や出版社や版や刷などの情報が書かれたページのことです。通常は本のいちばん最後のページに置かれます。]
//footnote[fn-cq9ws][@<em>{大扉}とは、タイトルページのことです。表紙のことではありません。]
