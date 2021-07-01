= 記法

//abstract{
この章では、原稿ファイルの記法について詳しく説明します。
初めての人は、先に@<secref>{02-tutorial|sec-basicsyntax}を見たほうがいいでしょう。
//}

#@#//makechaptitlepage[toc=on]



=={sec-comment} コメント


=== 行コメント

「@<code>|#@#|」で始まる行は行コメントであり、コンパイル時に読み飛ばされます。
一般的な行コメントとは違って、行の先頭から始まる必要があるので注意してください。

//list[][サンプル][]{
本文1。
@<b>|#@#|本文2。
本文3。
//}

//sampleoutputbegin[表示結果]

本文1。
#@#本文2。
本文3。

//sampleoutputend



//note[行コメントを空行扱いにしない]{
Re:VIEWでは行コメントを空行として扱います。
たとえば上の例の場合、「本文1」と「本文3」が別の段落になってしまいます。
ひどい仕様ですね。
こんな仕様だと、段落の途中をコメントアウトするときにとても不便です。

Starterでは「本文1」と「本文3」が別の段落にならないよう仕様を変更しています。
//}


=== 範囲コメント

「@<code>|#@+++|」から「@<code>|#@---|」までの行は範囲コメントであり、コンパイル時に読み飛ばされます。

//needvspace[latex][6zw]
//list[][サンプル][]{
本文1。

@<b>|#@+++|
本文2。

本文3。
@<b>|#@---|

本文4。
//}

//sampleoutputbegin[表示結果]

本文1。

#@+++
本文2。

本文3。
#@---

本文4。

//sampleoutputend



範囲コメントは入れ子にできません。
また「@<code>{+}」「@<code>{-}」の数は3つと決め打ちされてます。

なお範囲コメントはStarterによる拡張機能です。



=={sec-paragraph} 段落と改行と空行


=== 段落

空行を入れると、段落の区切りになります。
空行は何行入れても、1行の空行と同じ扱いになります。

//list[][サンプル][]{
言葉を慎みたまえ。君はラピュタ王の前にいるのだ。

これから王国の復活を祝って、諸君にラピュタの力を見せてやろうと思ってね。見せてあげよう、ラピュタの雷を！

旧約聖書にあるソドムとゴモラを滅ぼした天の火だよ。ラーマヤーナではインドラの矢とも伝えているがね。
//}

//sampleoutputbegin[表示結果]

言葉を慎みたまえ。君はラピュタ王の前にいるのだ。

これから王国の復活を祝って、諸君にラピュタの力を見せてやろうと思ってね。見せてあげよう、ラピュタの雷を！

旧約聖書にあるソドムとゴモラを滅ぼした天の火だよ。ラーマヤーナではインドラの矢とも伝えているがね。

//sampleoutputend



段落は、PDFなら先頭の行を字下げ（インデント）し、ePubなら1行空けて表示されます。
また段落の前に「@<code>|//noindent|」をつけると、段落の先頭の字下げ（インデント）をしなくなります。

//list[][サンプル][]{
@<b>|//noindent|
言葉を慎みたまえ！君はラピュタ王の前にいるのだ！

@<b>|//noindent|
これから王国の復活を祝って、諸君にラピュタの力を見せてやろうと思ってね。見せてあげよう、ラピュタの雷を！

@<b>|//noindent|
旧約聖書にあるソドムとゴモラを滅ぼした天の火だよ。ラーマヤーナではインドラの矢とも伝えているがね。
//}

//sampleoutputbegin[表示結果]

//noindent
言葉を慎みたまえ！君はラピュタ王の前にいるのだ！

//noindent
これから王国の復活を祝って、諸君にラピュタの力を見せてやろうと思ってね。見せてあげよう、ラピュタの雷を！

//noindent
旧約聖書にあるソドムとゴモラを滅ぼした天の火だよ。ラーマヤーナではインドラの矢とも伝えているがね。

//sampleoutputend




=== 改行

改行は、無視されるか、半角空白と同じ扱いになります。
正確には、次のような仕様です@<fn>{fn-tjpa6}。

 * 改行直前の文字と直後の文字のどちらかが日本語なら、改行は無視される。
 * どちらも日本語でないなら、半角空白と同じ扱いになる。

//footnote[fn-tjpa6][なおこれは日本語@<LaTeX>{}の仕様です。]

次の例を見てください。

 * 最初の段落では改行の前後（つまり行の終わりと行の始まり）がどちらも日本語なので、改行は無視されます。
 * 2番目の段落では改行の前後が日本語またはアルファベットなので、やはり改行は無視されます。
 * 3番目の段落では改行の前後がどちらもアルファベットなので、改行は半角空白扱いになります。

//list[][サンプル][]{
あいうえ@<b>|お|
@<b>|か|きくけ@<b>|こ|
@<b>|さ|しすせそ。

たちつてとAB@<b>|C|
@<b>|な|にぬね@<b>|の|
@<b>|D|EFはひふへほ。

まみむめもGH@<b>|I|
@<b>|J|KLらりるれろMN@<b>|O|
@<b>|P|QRやゆよ。
//}

//sampleoutputbegin[表示結果]

あいうえお
かきくけこ
さしすせそ。

たちつてとABC
なにぬねの
DEFはひふへほ。

まみむめもGHI
JKLらりるれろMNO
PQRやゆよ。

//sampleoutputend




=== 強制改行

強制的に改行したい場合は、「@<code>|@@<nop>{}<br>{}|」を使います。

//list[][サンプル][]{
土に根をおろし、風と共に生きよう。@<b>|@@<nop>$$<br>{}|
種と共に冬を越え、鳥と共に春をうたおう。
//}

//sampleoutputbegin[表示結果]

土に根をおろし、風と共に生きよう。@<br>{}
種と共に冬を越え、鳥と共に春をうたおう。

//sampleoutputend



なおこの例だと、「@<code>|//noindent|」をつけて段落の字下げをしないほうがいいでしょう。

//list[][サンプル][]{
@<b>|//noindent|
土に根をおろし、風と共に生きよう。@@<nop>$$<br>{}
種と共に冬を越え、鳥と共に春をうたおう。
//}

//sampleoutputbegin[表示結果]

//noindent
土に根をおろし、風と共に生きよう。@<br>{}
種と共に冬を越え、鳥と共に春をうたおう。

//sampleoutputend




=== 強制空行

強制的に空行を入れるには、「@<code>|@@<nop>{}<br>{}|」を連続してもいいですが、専用の命令「@<code>{//blankline}」を使うほうがいいでしょう。

//needvspace[latex][6zw]
//list[][サンプル][]{
/@<nop>$$/noindent
土に根をおろし、風と共に生きよう。

@<b>|//blankline|
/@<nop>$$/noindent
種と共に冬を越え、鳥と共に春をうたおう。
//}

//sampleoutputbegin[表示結果]

//noindent
土に根をおろし、風と共に生きよう。

//blankline
//noindent
種と共に冬を越え、鳥と共に春をうたおう。

//sampleoutputend




=== 改段落

インライン命令「@<code>|@@<nop>{}<par>{}|」を使うと、好きな箇所で改段落できます。

改段落は、通常は空行で行います。
しかしたとえば箇条書きの中で改段落したい場合、安易に空行を入れるとそこで箇条書きが終了してしまいます。
つまり「空行なら改段落する」という仕様は、箇条書きの文法とは相性が悪いのです。

このような場合は、「@<code>|@@<nop>{}<par>{}|」を使えば箇条書きの中でも改段落できます。

//needvspace[latex][6zw]
//list[][サンプル][]{
 * 『貴官は自己の才能を示すのに、弁舌ではなく実績をもってすべきだろう。
   他人に命令するようなことが自分にもできるかどうか、やってみたらどうだ。』
   @<b>|@@<nop>$$<par>{}|
   富田耕生さん、今までありがとうございました。
//}

//sampleoutputbegin[表示結果]

 * 『貴官は自己の才能を示すのに、弁舌ではなく実績をもってすべきだろう。
   他人に命令するようなことが自分にもできるかどうか、やってみたらどうだ。』
   @<par>{}
   富田耕生さん、今までありがとうございました。

//sampleoutputend



なお箇条書きの中で改段落しても、インデントはされません@<fn>{hysqy}。
インデントしたい場合は、「@<code>|@@<nop>{}<par>{@<b>{i}}|」としてください。

//footnote[hysqy][これは@<LaTeX>{}の仕様です。]

//needvspace[latex][6zw]
//list[][サンプル][]{
 * 『貴官は自己の才能を示すのに、弁舌ではなく実績をもってすべきだろう。
   他人に命令するようなことが自分にもできるかどうか、やってみたらどうだ。』
   @@<nop>$$<par>{@<b>|i|}
   富田耕生さん、今までありがとうございました。
//}

//sampleoutputbegin[表示結果]

 * 『貴官は自己の才能を示すのに、弁舌ではなく実績をもってすべきだろう。
   他人に命令するようなことが自分にもできるかどうか、やってみたらどうだ。』
   @<par>{i}
   富田耕生さん、今までありがとうございました。

//sampleoutputend




=== 改ページ

「@<code>|//clearpage|」で強制的に改ページできます。

なおRe:VIEWでは「@<code>|//pagebreak|」で強制的に改ページできますが、これは@<LaTeX>{}の「@<code>|\pagebreak|」命令を使うため、図や表のことが考慮されません。
Starterでは「@<code>|//clearpage|」を使ってください。


=={sec-heading} 見出し


=== 見出しレベル

章(Chapter)や節(Section)といった見出しは、「@<code>{= }」や「@<code>{== }」で始めます。

//list[][サンプル][]{
@<b>|=| 章(Chapter)見出し

@<b>|==| 節(Section)見出し

@<b>|===| 項(Subsection)見出し

@<b>|====| 目(Subsubsection)見出し

@<b>|=====| 段(Paragraph)見出し

@<b>|======| 小段(Subparagraph)見出し
//}



このうち、章・節・項・目はこの順番で（入れ子にして）使うことが想定されています。
たとえば、章(Chapter)の次に節ではなく項(Subsection)が登場するのはよくありません。

ただし段と小段にはこのような制約はなく、たとえば目(Subsubsection)を飛ばして節や項の中で使って構いません。

//list[][サンプル][]{
@<nop>$$= 章(Chapter)

@<nop>$$== 節(Section)

@<b>|===== 段(Paragraph)|   @<balloon>|節の中に段が登場しても構わない|
//}



Starterでは、章は1ファイルにつき1つだけにしてください。
1つのファイルに複数の章を入れないでください。

//list[][サンプル][]{
@<nop>$$= 章1

@<nop>$$== 節

@<b>|= 章2|         @<balloon>|（エラーにならないけど）これはダメ|
//}




=== 見出し用オプション

見出しには次のようなオプションが指定できます。

//needvspace[latex][7zw]
//list[][サンプル][]{
==@<b>|[nonum]| 章番号や節番号をつけない（目次には表示する）
==@<b>|[nodisp]| 見出しを表示しない（目次には表示する）
==@<b>|[notoc]| 章番号や節番号をつけず、目次にも表示しない
//}



一般的には、「まえがき」や「あとがき」には章番号をつけません。
そのため、これらのオプションは「まえがき」や「あとがき」で使うとよさそうに見えます。

しかしこのようなオプションをつけなくても、「まえがき」や「あとがき」の章や節には番号がつきません。
そのため、これらのオプションを使う機会は、実はほとんどありません。


=== 章の概要と著者名

章タイトルの直後に、章の概要を書くことをお勧めします。

//list[][サンプル][]{
@<nop>$$= チュートリアル

@<b>|//abstract{|
この章では、インストールから簡単な使い方までを説明します。
詳しい機能の説明は次の章で行います。
@<b>|//}|
//}



章の概要は、たとえば次のように表示されます。
本文と比べて小さめのゴシック体で、左右に余白が追加され、下に2行分空きます。

//sampleoutputbegin[表示結果]

//abstract{
この章では、インストールから簡単な使い方までを説明します。
詳しい機能の説明は次の章で行います。
//}

//sampleoutputend



また、章の著者名を表記できます。
複数の著者が集まって合同誌を書く場合に使うといいでしょう。
著者名は章タイトルの直後、章の概要より前に書いてください。

//list[][サンプル][]{
@<b>|//chapterauthor[|ムスカ大佐@<b>|]|
//}

//sampleoutputbegin[表示結果]

//chapterauthor[ムスカ大佐]

//sampleoutputend




#@+++
=== 章タイトルページ

章ごとのタイトルページを作れます。

 * 章の概要を書く（必須）。
 * そのあとに「@<code>|//makechaptitlepage[toc=section]|」と書く。
 * これを全部の章で行う（ただし「まえがき」と「あとがき」を除く）。

//list[][サンプル][]{
@<nop>$$= チュートリアル

/@<nop>$$/abstract{
この章では、インストールから簡単な使い方までを説明します。
詳しい機能の説明は次の章で行います。
/@<nop>$$/}

@<b>|//makechaptitlepage[toc=section]|
//}



章ごとのタイトルページには、その章ごとの目次がつきます。
これは読者にとって便利なので、100ページや200ページを超える本格的な本の場合は、章ごとのタイトルページをつけてみてください。
#@---


==={subsec-chapterid} 章ID

章(Chapter)のファイル名から拡張子の「@<file>{.re}」を取り除いた文字列を、「章ID」と呼んでいます。
たとえば、ファイル名が「@<file>{02-tutorial.re}」なら章IDは「@<file>{02-tutorial}」、ファイル名が「@<file>{preface.re}」なら章IDは「@<file>{preface}」です。

章IDは、章そのものを参照する場合だけでなく、ある章から別の章の節(Section)や図やテーブルを参照するときに使います。
詳しくは後述します。

//note[章にラベルはつけられない]{
このあとで説明しますが、たとえば「@<code>{=={ラベル} タイトル}」のように書くと節(Section)や項(Subsection)にラベルがつけられます。

しかし「@<code>{={ラベル} タイトル}」のように書いても章にはラベルがつけられません。
かわりに章IDを使ってください。
//}


=== 章を参照する

章(Chapter)を参照するには、3つの方法があります。

 * 「@<code>|@@<nop>{}<chapref>{章ID}|」で章番号と章タイトルを参照できます（例：「第2章 チュートリアル」）。
 * 「@<code>|@@<nop>{}<chap>{章ID}|」で章番号を参照できます（例：「第2章」）。
 * 「@<code>|@@<nop>{}<title>{章ID}|」で章タイトルを参照できます（例：「チュートリアル」）。

//list[][サンプル][]{
@<b>|@@<nop>$$<chapref>{|02-tutorial@<b>|}|   ← 章番号と章タイトル

@<b>|@@<nop>$$<chap>{|02-tutorial@<b>|}|      ← 章番号だけ

@<b>|@@<nop>$$<title>{|02-tutorial@<b>|}|     ← 章タイトルだけ
//}

//sampleoutputbegin[表示結果]

@<chapref>{02-tutorial}   ← 章番号と章タイトル

@<chap>{02-tutorial}      ← 章番号だけ

@<title>{02-tutorial}     ← 章タイトルだけ

//sampleoutputend




==={subsec-headingref} 節や項を参照する

節(Section)や項(Subsection)を参照するには、まず節や項にラベルをつけます。

//list[][サンプル][]{
==@<b>|{sec-heading}| 見出し
===@<b>|{subsec-headingref}| 節や項を参照する
//}



そして「@<code>|@@<nop>{}<hd>{ラベル}|」を使ってそれらを参照します。

//list[][サンプル][]{
@<b>|@@<nop>$$<hd>{|sec-heading@<b>|}|

@<b>|@@<nop>$$<hd>{|subsec-headingref@<b>|}|
//}

//sampleoutputbegin[表示結果]

@<hd>{sec-heading}

@<hd>{subsec-headingref}

//sampleoutputend



またStarter拡張である「@<code>|@@<nop>{}<secref>{ラベル}|」を使うと、ページ番号も表示されます。
コマンド名は「@<code>|@@<nop>{}<secref>|」ですが、節(Section)だけでなく項(Subsection)や目(Subsubsection)にも使えます。

//list[][サンプル][]{
@<b>|@@<nop>$$<secref>{|sec-heading@<b>|}|

@<b>|@@<nop>$$<secref>{|subsec-headingref@<b>|}|
//}

//sampleoutputbegin[表示結果]

@<secref>{sec-heading}

@<secref>{subsec-headingref}

//sampleoutputend



他の章の節や項（つまり他の原稿ファイルの節や項）を参照するには、ラベルの前に章IDをつけます。

//list[][サンプル][]{
@@<nop>$$<secref>{@<b>{03-syntax|}sec-heading}

@@<nop>$$<secref>{@<b>{03-syntax|}subsec-headingref}
//}

//sampleoutputbegin[表示結果]

@<secref>{03-syntax|sec-heading}

@<secref>{03-syntax|subsec-headingref}

//sampleoutputend



なおラベルのかわりに節タイトルや項タイトルが使えますが、タイトルを変更したときにそれらを参照している箇所も書き換えなければならなくなるので、お勧めしません。
一見面倒でも、参照先の節や項にラベルをつけることを強くお勧めします。


//note[項を参照するなら項番号をつけよう]{
デフォルトでは、章(Chapter)と節(Section)には番号がつきますが、項(Subsection)には番号がつきません。
そのため、「@@<nop>{}<hd>{}」で項を参照するとたとえば『「見出し用オプション」』となってしまい、項番号がないのでとても探しにくくなります。
「@@<nop>{}<secref>{}」を使うと『3.1「見出し」の「見出し用オプション」』となるので多少ましですが、探しやすいとは言えません。

そのため、項(Subsection)を参照したいなら項にも番号をつけましょう。
@<file>{config.yml}の設定項目「@<code>{secnolevel:}」を「@<code>{3}」にすると、項にも番号がつくようになります。
//}


=== まえがき、あとがき、付録

「まえがき」や「あとがき」や「付録」の章は、@<file>{catalog.yml}で指定します@<fn>{fn-n8bjp}。

//footnote[fn-n8bjp][「@<file>{catalog.yml}」の中身は「YAML」という形式で書かれています。「YAML」を知らない人はGoogle検索して調べてみてください。]

//list[][catalog.yml]{
@<b>{PREDEF:}
  @<b>{- 00-preface.re}     @<balloon>{まえがき}

CHAPS:
  - 01-install.re
  - 02-tutorial.re
  - 03-syntax.re

@<b>{APPENDIX:}
  @<b>{- 92-filelist.re}    @<balloon>{付録}

@<b>{POSTDEF:}
  @<b>{- 99-postface.re}    @<balloon>{あとがき}
//}

「@<code>{-}」のあとに半角空白が必要なことに注意してください。
またインデントにタブ文字は使わないでください。


=== 部

「第I部」「第II部」のような部(Part)を指定するには、@<file>{catalog.yml}で次のように指定します。

//list[][catalog.yml]{
PREDEF:

CHAPS:
  - @<b>{初級編:}
    - chap1.re
    - chap2.re
  - @<b>{中級編:}
    - chap3.re
    - chap4.re
  - @<b>{上級編:}
    - chap5.re
    - chap6.re

APPENDIX:

POSTDEF:
//}

この例では「第I部 初級編」「第II部 中級編」「第III部 上級編」の3つに分かれています。

部タイトルのあとには「@<code>{:}」をつけて「@<code>{初級編:}」のようにしてください。
これを忘れると意味不明なエラーが出ます。


=== 段見出しと小段見出し

Starterでは、段(Paragraph)見出しは次のように表示されます。

//list[][サンプル][]{
テキストテキストテキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキストテキストテキスト。

@<b>|===== 段見出し1|
テキストテキストテキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキストテキストテキスト。

テキストテキストテキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキストテキストテキスト。

@<b>|===== 段見出し2|
テキストテキストテキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキストテキストテキスト。

テキストテキストテキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキストテキストテキスト。
//}

//sampleoutputbegin[表示結果]

テキストテキストテキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキストテキストテキスト。

===== 段見出し1
テキストテキストテキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキストテキストテキスト。

テキストテキストテキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキストテキストテキスト。

===== 段見出し2
テキストテキストテキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキストテキストテキスト。

テキストテキストテキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキストテキストテキスト。

//sampleoutputend



これを見ると分かるように、段見出しの前に少しスペースが入ります。
しかし終わりにはそのようなスペースが入りません。
終わりにもスペースを入れるには、次のように「@<code>|//paragraphend|」を使ってください。

//list[][サンプル][]{
テキストテキストテキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキストテキストテキスト。

@<nop>$$===== 段見出し
テキストテキストテキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキストテキストテキスト。
@<b>|//paragraphend|

テキストテキストテキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキストテキストテキスト。
//}

//sampleoutputbegin[表示結果]

テキストテキストテキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキストテキストテキスト。

===== 段見出し
テキストテキストテキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキストテキストテキスト。
//paragraphend

テキストテキストテキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキストテキストテキスト。

//sampleoutputend



また、小段(Subparagraph)見出しは次のように表示されます。

//list[][サンプル][]{
テキストテキストテキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキストテキストテキスト。

@<b>|====== 小段見出し1|
テキストテキストテキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキストテキストテキスト。

テキストテキストテキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキストテキストテキスト。

@<b>|====== 小段見出し2|
テキストテキストテキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキストテキストテキスト。

テキストテキストテキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキストテキストテキスト。
//}

//sampleoutputbegin[表示結果]

テキストテキストテキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキストテキストテキスト。

====== 小段見出し1
テキストテキストテキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキストテキストテキスト。

テキストテキストテキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキストテキストテキスト。

====== 小段見出し2
テキストテキストテキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキストテキストテキスト。

テキストテキストテキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキストテキストテキスト。

//sampleoutputend



これを見ると分かるように、小段見出しではスペースは入りません。
「@<code>|//subparagraph|」は用意されていますが、スペースは入りません。


=={sec-list} 箇条書きと定義リスト

=== 番号なし箇条書き

番号なし箇条書きは「@<code>{ * }」で始めます。
先頭に半角空白が入っていることに注意してください。

//list[][サンプル][]{
 @<b>|*| 箇条書き1
 @<b>|*| 箇条書き2
 @<b>|*| 箇条書き3
//}

//sampleoutputbegin[表示結果]

 * 箇条書き1
 * 箇条書き2
 * 箇条書き3

//sampleoutputend



「@<code>{*}」を連続させると、箇条書きを入れ子にできます。

//list[][サンプル][]{
 @<b>|*| 箇条書き
 @<b>|**| 入れ子の箇条書き
 @<b>|***| 入れ子の入れ子
//}

//sampleoutputbegin[表示結果]

 * 箇条書き
 ** 入れ子の箇条書き
 *** 入れ子の入れ子

//sampleoutputend




=== 番号つき箇条書き

番号つき箇条書きは2つの書き方があります。

1つ目は「@<code>{ 1. }」のように始める書き方です。
この方法は数字しか指定できず、また入れ子にできません。

//list[][サンプル][]{
 @<b>|1.| 番号つき箇条書き（数字しか指定できない）
 @<b>|2.| 番号つき箇条書き（入れ子にできない）
//}

//sampleoutputbegin[表示結果]

 1. 番号つき箇条書き（数字しか指定できない）
 2. 番号つき箇条書き（入れ子にできない）

//sampleoutputend



2つ目はStarterによる拡張で、「@<code>{ - 1. }」のように始める書き方です。
この書き方は「@<code>{ - A. }」や「@<code>{ - (1) }」など任意の文字列が使え、また「@<code>{-}」を連続することで入れ子にもできます。

//list[][サンプル][]{
 @<b>|- (A)| 番号つき箇条書き（英数字が使える）
 @<b>|- (B)| 番号つき箇条書き（任意の文字列が使える）
 @<b>|-- (B-1)| 番号つき箇条書き（入れ子にできる）
 @<b>|***| 番号なし箇条書きを含めることもできる
//}

//sampleoutputbegin[表示結果]

 - (A) 番号つき箇条書き（英数字が使える）
 - (B) 番号つき箇条書き（任意の文字列が使える）
 -- (B-1) 番号つき箇条書き（入れ子にできる）
 *** 番号なし箇条書きを含めることもできる

//sampleoutputend



どちらの記法も、先頭に半角空白が必要なことに注意してください。

//note[数字を使うべきか、文字を使うべきか]{
番号つき箇条書きでは、順番に強い意味がある場合は「1.」のように数字を使い、順番にさほど意味はなく単にラベルとして使いたい場合は「A.」のように文字を使います。
詳しくは@<secref>{06-bestpractice|sec-goodenumerate}を参照してください。
//}


==={sec-termlist} 定義リスト

HTMLでいうところの「@<code>{<dl><dt><dd>}」は、「定義リスト」と「説明リスト」の2つがあります。
前者はRe:VIEWでも使え、後者はStarterによる拡張です。
この節では前者の「定義リスト」を説明し、次の節で後者の「説明リスト」を説明します。
なお会話形式の文章を作成するには、この節ではなく@<secref>{sec-talk}を参照してください。

定義リストは、「@<code>{ : }」で始めて、次の行からインデントします。

 * 説明文のインデントは、半角空白でもタブ文字でもいいです。
  しかし混在させるとトラブルの元なので、どちらかに統一しましょう。
 * 先頭の半角空白は入れるようにしましょう。
   過去との互換性のため、先頭の半角空白がなくても動作しますが、箇条書きとの整合性のために半角空白を入れましょう。

//list[][サンプル][]{
 @<b>|:| 用語1
    説明文。
    説明文。
 @<b>|:| 用語2
    説明文。
    説明文。
//}

//sampleoutputbegin[表示結果]

 : 用語1
    説明文。
    説明文。
 : 用語2
    説明文。
    説明文。

//sampleoutputend



説明文の中には、箇条書きが入れられます（Starter拡張）。
ただし、注意点が2つあります。

 * 説明文の1行目を箇条書きで始めることはできません@<fn>{59sv1}。
   1行目は必ず通常の文章にしてください。
 * 箇条書きを使うときは、インデントにはタブ文字を使わず半角空白を使ってください。
   半角空白4文字でインデントするといいでしょう。

//footnote[59sv1][この制約は、Re:VIEWの文法に起因します。]

//list[][サンプル][]{
 @<b>|:| 用語
    説明文。
     * 項目1
     * 項目1
//}

//sampleoutputbegin[表示結果]

 : 用語
    説明文。
     * 項目1
     * 項目1

//sampleoutputend



説明文には、プログラムコードなどは入れられません。
入れたい場合は、次で紹介する「説明リスト」を使います。


==={sec-desclist} 説明リスト

「説明リスト」(Description List)とは、先ほど説明した「定義リスト」(Definition List)の機能を拡張したものです。
定義リストと比べて、説明リストには次のような特徴があります。

 * キーや用語を太字にする/しないが選べる。
 * キーや用語の直後で改行する/しないが選べる。
 * 説明文の中に、箇条書きだけでなくプログラムコードなどを入れられる。
 * 説明文の1行目から箇条書きを書ける。
 * 専用の構文を使わないので、「@<code>| : |」だけで書ける定義リストと比べて記述が煩雑。
 * 文章における役割は定義リストと同じ。

説明リストは次のように書きます。
途中にある「@<code>|@@<nop>{}<br>{}|」は改行を表します。

//list[][サンプル][]{
@<b>|//desclist{|
@<b>|//desc[開催日時]{|
20XX年XX月XX日 10:00〜12:00
/@<nop>$$/}
@<b>|//desc[開催場所]{|
XXXXXXXXビルXXXXXXXX会議室@@<nop>$$<br>{}
（XXXXXX市XXXXXX町XX-XX-XX）
/@<nop>$$/}
@<b>|//}|
//}

//sampleoutputbegin[表示結果]

//desclist{
//desc[開催日時]{
20XX年XX月XX日 10:00〜12:00
//}
//desc[開催場所]{
XXXXXXXXビルXXXXXXXX会議室@<br>{}
（XXXXXX市XXXXXX町XX-XX-XX）
//}
//}

//sampleoutputend



「@<code>| : |」だけで済む定義リストと比べて説明リストの書き方は煩雑ですが、@<table>{7mfnj}のようなオプションを指定できるという利点があります。
これらのオプションのデフォルト値は、「@<file>{config-starter.yml}」で設定されています。

//table[7mfnj][「@<code>|//desclist|」のオプション][hline=off]{
オプション			説明			デフォルト値
====================
@<code>|bold=on|		キーや用語を太字にする		@<code>|off|
@<code>|compact=on|		キーや用語の直後で改行しない	@<code>|off|
@<code>|indent=@<i>{幅}|	説明文のインデント幅		@<code>|3zw|
@<code>|listmargin=@<i>{高さ}|	説明リスト上下の空きの高さ	@<code>|0.5zw|
@<code>|itemmargin=@<i>{高さ}|	説明項目間の空きの高さ		@<code>|0mm|
@<code>|classname=@<i>{名前}|	HTMLタグに追加するクラス名	.
//}

オプションは、「@<code>|//desclist|」の第1引数に指定します。
先ほどの例をオプションつきで表示してみましょう。
ここで「@<code>|7zw|」は全角7文字分という意味です。

//list[][サンプル][]{
/@<nop>$$/desclist@<b>|[bold=on,compact=on,indent=7zw]|{
/@<nop>$$/desc[開催日時]{
20XX年XX月XX日 10:00〜12:00
/@<nop>$$/}
/@<nop>$$/desc[開催場所]{
XXXXXXXXビルXXXXXXXX会議室@@<nop>$$<br>{}
（XXXXXX市XXXXXX町XX-XX-XX）
/@<nop>$$/}
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//desclist[bold=on,compact=on,indent=7zw]{
//desc[開催日時]{
20XX年XX月XX日 10:00〜12:00
//}
//desc[開催場所]{
XXXXXXXXビルXXXXXXXX会議室@<br>{}
（XXXXXX市XXXXXX町XX-XX-XX）
//}
//}

//sampleoutputend



説明リストでは、説明文の1行目から箇条書きが書けます。
ただし次のサンプルを見れば分かるように、1行目が箇条書きだとスペースが空きすぎます。

//list[][サンプル][]{
/@<nop>$$/desclist{
/@<nop>$$/desc[参加申込者]{
@<b>| * アリス|
@<b>| * ボブ|
@<b>| * チャーリー|
/@<nop>$$/}
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//desclist{
//desc[参加申込者]{
 * アリス
 * ボブ
 * チャーリー
//}
//}

//sampleoutputend



この問題については将来対応する予定です。
当面は、「@<code>|//vspace|」を使ってスペースを削除してください。

//list[][サンプル][]{
/@<nop>$$/desclist{
/@<nop>$$/desc[参加申込者]{
@<b>|//vspace[latex][-5mm]|
 * アリス
 * ボブ
 * チャーリー
/@<nop>$$/}
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//desclist{
//desc[参加申込者]{
//vspace[latex][-5mm]
 * アリス
 * ボブ
 * チャーリー
//}
//}

//sampleoutputend



また説明文の中に、プログラムコードなども入れられます。

//list[][サンプル][]{
/@<nop>$$/desclist{
/@<nop>$$/desc[print文]{
「@@<nop>$$<code>|print()|」を使うと、文字列を表示できます。
/@<nop>$$/list{
def hello(name):
    print(f"Hello, {name}!")
/@<nop>$$/}
/@<nop>$$/}
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//desclist{
//desc[print文]{
「@<code>|print()|」を使うと、文字列を表示できます。
//list{
def hello(name):
    print(f"Hello, {name}!")
//}
//}
//}

//sampleoutputend




=={sec-command} インライン命令とブロック命令

ここで少し話を変えて、命令の形式について説明します。

Re:VIEWおよびStarterでのコマンドは、大きく3つの形式に分けられます。

 * インライン命令（例：「@<code>|@@<nop>{}<B>{...}|」）
 * ブロック命令（例：「@<code>|//list{...//}|」）
 * 特殊な形式の命令（例：箇条書きの「@<code>|*|」や見出しの「@<code>|=|」など）

ここではインライン命令とブロック命令について、それぞれ説明します。


==={subsec-inlinecmd} インライン命令

「インライン命令」とは、「@<code>|@@<nop>{}<B>{...}|」のような形式の命令のことです。
主に、文の途中に埋め込んで使います。

Re:VIEWのインライン命令は入れ子にできませんが、Starterでは入れ子にできるよう拡張しています。

//list[][サンプル][]{
@<b>|@@<nop>$$<code>{|func(@<b>|@@<nop>$$<b>{|@<b>|@@<nop>$$<i>{|arg@<b>|}}|)@<b>|}|
//}

//sampleoutputbegin[表示結果]

@<code>{func(@<b>{@<i>{arg}})}

//sampleoutputend



インライン命令は、複数行を対象にできません。
たとえば次のような書き方はできません。

//list[][サンプル][]{
@<b>|@@<nop>$$<B>{|テキスト
テキスト@<b>|}|。
//}



インライン命令の中に「@<code>|}|」を書きたい場合は、次のうちどちらかを使います。

 * 「@<code>|@@<nop>{}<B>{var x = {a: 1\};}|」のように「@<code>|\}|」とエスケープする。
 * 「@<code>|@@<nop>{}<B>{...}|」のかわりに「@<code>{@@<nop>{}<B>|...|}」または「@<code>{@@<nop>{}<B>$...$}」を使う。

2番目の書き方は、Re:VIEWでは「フェンス記法」と呼ばれています。
この記法では、バックスラッシュによるエスケープができないので注意してください。
たとえば「@<code>{@@<nop>{}<B>|\||}」や「@<code>{@@<nop>{}<B>$\$$}」のようなエスケープをしても効果はありません。

//note[インライン命令の入れ子対応と複数の引数]{
インライン命令には、「@<code>|@@<nop>{}<href>{@<i>{url}, @<i>{text}}|」や「@<code>|@@<nop>{}<yomi>{@<i>{text}, @<i>{yomi}}|」のように複数の引数を受け取るものがあります。

しかしこの書き方は、実は入れ子のインライン命令と相性がよくありません。
望ましいのは「@<code>|@@<nop>{}<href url="@<i>{url}">{@<i>{text}}|」や「@<code>|@@<nop>{}<ruby yomi="@<i>{yomi}">{@<i>{text}}|」のような形式であり、採用を現在検討中です。
//}


==={subsec-blockcmd} ブロック命令

「ブロック命令」とは、「@<code>|//list{...//}|」のような形式の命令のことです。

ブロック命令は、必ず行の先頭から始まる必要があります。
たとえば「@<code>|//list{|」や「@<code>|//}|」の前に空白があると、ブロック命令として認識されません。

ブロック命令は入れ子にできます（Starterによる拡張）。
たとえば次の例では、「@<code>|//note{...//}|」の中に「@<code>|//list{...//}|」が入っています。

//list[][サンプル][]{
@<b>|//note|[ノートサンプル]@<b>|{|
@<b>|//list|[][フィボナッチ]@<b>|{|
def fib(n):
    return n if n <= 1 else fib(n-1)+fib(n-2)
@<b>|//}|
@<b>|//}|
//}



ただし次のブロック命令はその性質上、中に他のブロック命令を入れられません（インライン命令は入れられます）。

 * プログラムコードを表す「@<code>|//list|」
 * ターミナルを表す「@<code>|//terminal|」と「@<code>|//cmd|」
 * @<LaTeX>{}やHTMLの生テキストを埋め込む「@<code>|//embed|」

ブロック命令の引数は、たとえば「@<code>|//list[ラベル][説明文]{...//}|」のように書きます。
この場合だと、第1引数が「@<code>{ラベル}」で第2引数が「@<code>{説明文}」です。
引数の中に「@<code>|]|」を入れたい場合は、「@<code>|\]|」のようにエスケープしてください。



=={sec-decoration} 強調と装飾


=== 強調

文章の一部を強調するには「@<code>|@@<nop>{}<B>{...}|」または「@<code>|@@<nop>{}<strong>{...}|」で囲みます。
囲んだ部分は太字のゴシック体になります。

//list[][サンプル][]{
テキスト@<b>|@@<nop>$$<B>{|テキスト@<b>|}|テキスト。
//}

//sampleoutputbegin[表示結果]

テキスト@<B>{テキスト}テキスト。

//sampleoutputend



日本語の文章では、強調箇所は太字にするだけでなくゴシック体にするのが一般的です。
そのため、強調したい場合は「@<code>|@@<nop>{}<B>{...}|」または「@<code>|@@<nop>{}<strong>{...}|」を使ってください。


//note[インライン命令]{
「@<code>|@@<nop>{}<B>{...}|」のような記法は@<em>{インライン命令}と呼ばれています。
インライン命令は必ず1行に記述します。
複数行を含めることはできません。

//list[][このような書き方はできない]{
@<B>|@@<nop>{}<B>{|テキスト
テキスト
テキスト。@<B>|}|
//}

//}


=== 太字

太字にするだけなら「@<code>|@@<nop>{}<b>{...}|」で囲みます。
強調と違い、ゴシック体になりません。

//list[][サンプル][]{
テキスト@<b>|@@<nop>$$<b>{|テキスト@<b>|}|テキスト。
//}

//sampleoutputbegin[表示結果]

テキスト@<b>{テキスト}テキスト。

//sampleoutputend



前述したように、日本語の文章では強調するときは太字のゴシック体にするのが一般的です。
そのため強調したいときは、ゴシック体にならない「@<code>|@@<nop>{}<b>{...}|」は使わないほうがいいでしょう。

ただし、プログラムコードの中では「@<code>|@@<nop>{}<B>{...}|」ではなく「@<code>|@@<nop>{}<b>{...}|」を使ってください。
理由は、プログラムコードは等幅フォントで表示しているのに、「@<code>|@@<nop>{}<B>{...}|」だとゴシック体のフォントに変更してしまうからです。
「@<code>|@@<nop>{}<b>{...}|」はフォントを変更しないので、等幅フォントのままで太字になります。


=== 装飾

テキストを装飾するには、@<table>{tbl-ndpcm}のようなインライン命令を使います。

//table[tbl-ndpcm][装飾用のインライン命令]{
意味	入力	出力
--------------------
太字		@<code>|@@<nop>{}<b>{テキスト}|		@<b>{テキスト}
強調		@<code>|@@<nop>{}<strong>{テキスト}|	@<strong>{テキスト}
強調		@<code>|@@<nop>{}<B>{テキスト}|		@<B>{テキスト}
傍点		@<code>|@@<nop>{}<bou>{テキスト}|	@<bou>{テキスト}
#@#圏点		@<code>|@@<nop>{}<kenten>{テキスト}|	@<kenten>{テキスト}
網掛け		@<code>|@@<nop>{}<ami>{テキスト}|	@<ami>{テキスト}
下線		@<code>|@@<nop>{}<u>{テキスト}|		@<u>{テキスト}
取り消し線	@<code>|@@<nop>{}<del>{テキスト}|	@<del>{テキスト}
目立たせない	@<code>|@@<nop>{}<weak>{テキスト}|	@<weak>{テキスト}
ゴシック体	@<code>|@@<nop>{}<em>{テキスト}|	@<em>{テキスト}
イタリック体	@<code>|@@<nop>{}<i>{Text}|		@<i>{Text}
等幅		@<code>|@@<nop>{}<tt>{Text}|		@<tt>{Text}
コード		@<code>|@@<nop>{}<code>{Text}|		@<code>{Text}
#@#縦中横	@<code>|@@<nop>{}<tcy>{Text}|		-
//}

=== 文字サイズ

文字の大きさを変更するインライン命令もあります（@<table>{tbl-2cv8w}）。

//table[tbl-2cv8w][文字の大きさを変更するインライン命令]{
意味	入力	出力
--------------------
小さく		@<code>|@@<nop>{}<small>{テキスト}|		@<small>{テキスト}
もっと小さく		@<code>|@@<nop>{}<xsmall>{テキスト}|		@<xsmall>{テキスト}
もっともっと小さく		@<code>|@@<nop>{}<xxsmall>{テキスト}|		@<xxsmall>{テキスト}
大きく			@<code>|@@<nop>{}<large>{テキスト}|		@<large>{テキスト}
もっと大きく		@<code>|@@<nop>{}<xlarge>{テキスト}|		@<xlarge>{テキスト}
もっともっと大きく	@<code>|@@<nop>{}<xxlarge>{テキスト}|		@<xxlarge>{テキスト}
//}

=== マーキング用

装飾ではなく、論理的な意味を与えるマーキング用のインライン命令もあります（@<table>{tbl-t533z}）。

//table[tbl-t533z][マーキング用のインライン命令]{
意味	入力	出力
--------------------
プログラムコード	@<code>|@@<nop>{}<code>{xxx}|	@<code>{xxx}
ファイル名		@<code>|@@<nop>{}<file>{xxx}|	@<file>{xxx}
ユーザ入力文字列	@<code>|@@<nop>{}<userinput>{xxx}|	@<userinput>{xxx}
//}

#@#//note[「@<code>|@@<nop>{}<tt>{}|」ではなく「@<code>|@@<nop>{}<code>{}|」や「@<code>|@@<nop>{}<file>{}|」を使う]{
//note[「@@<nop>{}<tt>{}」ではなく「@@<nop>{}<code>{}」や「@@<nop>{}<file>{}」を使う]{
プロブラムコードやコマンド文字列を等幅フォントで表すには、「@<code>|@@<nop>{}<tt>{}|」ではなく「@<code>|@@<nop>{}<code>{}|」を使ってください。
理由は、プログラムコードであることを表すにはフォントを変更するコマンドではなく、「プログラムコードである」ことを表すコマンドを使うべきだからです。

同じ理由で、ファイル名を表すには「@<code>|@@<nop>{}<file>{}|」を使ってください。
「@<code>|@@<nop>{}<tt>{}|」や「@<code>|@@<nop>{}<code>{}|」を使うべきではありません。
//}


=== その他のインライン命令


==== ダブルクォーテーション

「@<code>|@@<nop>{}<qq>{...}|」を使うと、引数の文字列を適切なダブルクォーテーションで囲みます。

 * PDFでは「@<code>|``...''|」のように囲みます。
   これは@<LaTeX>{}での標準的な方法であり、表示がきれいです。
 * HTMLでは「@<code>|“...”|」のように全角記号で囲みます。

表示を比べてみましょう。

 * 「@<code>|@@<nop>{}<qq>{Apple}|」は、「@<qq>{Apple}」と表示されます。
 * 「@<code>|"Apple"|」（半角記号）は、「"Apple"」と表示されます。
 * 「@<code>|“Apple”|」（全角記号）は、「“Apple”」と表示されます。



=={sec-program} プログラムリスト

=== 基本的な書き方

プログラムリストは「@<code>|//list{ ... //}|」で囲み、第2引数に説明書きを指定します。

//list[][サンプル][]{
@<b>|//list[][フィボナッチ数列]{|
def fib(n):
    return n if n <= 1 else fib(n-1) + fib(n-2)
@<b>|//}|
//}

//sampleoutputbegin[表示結果]

//list[][フィボナッチ数列]{
def fib(n):
    return n if n <= 1 else fib(n-1) + fib(n-2)
//}

//sampleoutputend



もし説明文字列の中に「@<code>{]}」を含める場合は、「@<code>{\\]}」のようにエスケープしてください。
また説明書きをつけない場合は、引数を省略して「@<code>|//list{ ... //}|」のように書けます。

=== リスト番号

第1引数にラベル名を指定すると、リスト番号がつきます。
また「@<code>|@@<nop>{}<list>{ラベル名}|」とすると、ラベル名を使ってプログラムリストを参照できます。
そのため、ラベル名は他と重複しない文字列にしてください。

//list[][サンプル][]{
サンプルコードはこちら（@<b>|@@<nop>$$<list>{fib2}|）。

/@<nop>$$/list@<b>|[fib2]|[フィボナッチ数列]{
def fib(n):
    return n if n <= 1 else fib(n-1) + fib(n-2)
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

サンプルコードはこちら（@<list>{fib2}）。

//list[fib2][フィボナッチ数列]{
def fib(n):
    return n if n <= 1 else fib(n-1) + fib(n-2)
//}

//sampleoutputend



第1引数だけ指定して「@<code>|//list[ラベル名]{ ... //}|」のようにすると、リスト番号はつくけど説明はつきません。

=== ラベルの自動指定

リスト番号はつけたいけど、重複しないラベル名をいちいちつけるのが面倒なら、ラベル名のかわりに「@<code>|?|」を指定します。
ただし「@<code>|@@<nop>{}<list>{ラベル名}|」での参照はできなくなります。

//list[][サンプル][]{
/@<nop>$$/list@<b>|[?]|{
def fib(n):
    return n if n <= 1 else fib(n-1) + fib(n-2)
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//list[?]{
def fib(n):
    return n if n <= 1 else fib(n-1) + fib(n-2)
//}

//sampleoutputend



この機能は、すべてのプログラムリストに手っ取り早くリスト番号をつけたいときに便利です。


=== 長い行の折り返し

Starterでは、プログラムコードの長い行は自動的に折り返されます。
行が折り返されると行末と次の行の先頭に折り返し記号がつくので、どの行が折り返されか簡単に見分けがつきます。

//list[][サンプル][]{
/@<nop>$$/list{
sys.stderr.write("Something error raised. Please contact to system administrator.")
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//list{
sys.stderr.write("Something error raised. Please contact to system administrator.")
//}

//sampleoutputend



「@<code>|@@<nop>{}<b>{}|」で太字にしたり、「@<code>|@@<nop>{}<del>{}|」で取り消し線を引いても、きちんと折り返しされます。

//list[][サンプル][]{
@<b>|//list{|
@<b>|@@<nop>$$<b>{|sys.stderr.write("Something error raised. Please contact to system administrator.")@<b>|}|
@<b>|@@<nop>$$<del>{|sys.stderr.write("Something error raised. Please contact to system administrator.")@<b>|}|
@<b>|//}|
//}

//sampleoutputbegin[表示結果]

//list{
@<b>{sys.stderr.write("Something error raised. Please contact to system administrator.")}
@<del>{sys.stderr.write("Something error raised. Please contact to system administrator.")}
//}

//sampleoutputend



@<del>|ただし折り返し箇所が日本語だと、折り返しされても折り返し記号がつきません。|
折り返し箇所が日本語でも、折り返し記号がつくようになりました。
以前のバージョンを使っている場合はStarterのプロジェクトを作り直してみてください。

折り返しをしたくないときは、「@<code>|//list[][][@<b>{fold=off}]|」と指定します。

//list[][サンプル][]{
/@<nop>$$/list[][][@<b>|fold=off|]{
sys.stderr.write("Something error raised. Please contact to system administrator.")
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//list[][][fold=off]{
sys.stderr.write("Something error raised. Please contact to system administrator.")
//}

//sampleoutputend



折り返しはするけど折り返し記号をつけたくない場合は、「@<code>|//list[][][@<b>{foldmark=off}]|」と指定します。

//list[][サンプル][]{
/@<nop>$$/list[][][@<b>|foldmark=off|]{
sys.stderr.write("Something error raised. Please contact to system administrator.")
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//list[][][foldmark=off]{
sys.stderr.write("Something error raised. Please contact to system administrator.")
//}

//sampleoutputend




=== 改行文字を表示

第3引数に「@<code>|[eolmark=on]|」と指定をすると、改行文字がうっすらと表示されます。
この機能は折り返し記号をオフにしてから使うといいでしょう。

//list[][サンプル][]{
/@<nop>$$/list[][][@<b>|eolmark=on|,foldmark=off]{
function fib(n) {
    if (n <= 1) { return n; }
    return fib(n-1) + fib(n-2);
}
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//list[][][eolmark=on,foldmark=off]{
function fib(n) {
    if (n <= 1) { return n; }
    return fib(n-1) + fib(n-2);
}
//}

//sampleoutputend



//note[折り返し記号や改行文字をマウス選択の対象外にする]{
PDF中のプログラムコードをマウスでコピーしたとき、折り返し記号や改行文字がコピーした文字列に含まれると、それらをいちいち除去しないといけないので不便です。

Starterでは、これらの記号をマウス選択の対象から外すことができます。
詳しくは@<secref>{04-customize|sec-excluding}を参照してください。
//}


=== インデント

第3引数にたとえば「@<code>|[indent=4]|」@<fn>{dw1jh}のような指定をすると、4文字幅でのインデントを表す縦線がうっすらとつきます。

//footnote[dw1jh][後方互換性のために、「@<code>|[indentwidth=4\]|」という名前でも指定できます。]

//list[][サンプル][]{
/@<nop>$$/list[][]@<b>|[indent=4]|{
class Fib:

    def __call__(n):
        if n <= 1:
            return n
        else:
            return fib(n-1) + fib(n-2)
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//list[][][indent=4]{
class Fib:

    def __call__(n):
        if n <= 1:
            return n
        else:
            return fib(n-1) + fib(n-2)
//}

//sampleoutputend



Pythonのようにインデントの深さでブロックを表すプログラミング言語では、ブロックの終わりが明示されません。
そのためプログラムの途中で改ページされると、その前後のブロックの関係が読者には分からなくなります。

そのような場合は、この機能を使ってインデントを表示してあげるとよいでしょう。

//note[インデント記号をコピペ対象にしない]{
以前のStarterでは、インデントを表す記号としてパイプ記号「@<code>{|}」を使っていました。
そのせいで、プログラムコードをマウスでコピペするとパイプ記号も一緒にコピペされてしまっていました。
これは読者にとってうれしくない仕様です。

現在のStarterでは、インデントを表す記号のかわりに図形として縦線を引いています。
そのおかげで、コピペしてもパイプ記号が入りません@<fn>{fn-ibzh1}。
Starterによる気配りの一例です。

//footnote[fn-ibzh1][ただし、Starterのデフォルトでは折り返し記号や行番号がコピペ対象に含まれてしまいます。これについては@<secref>{04-customize|sec-excluding}を参照してください。]
//}


=== 外部ファイルの読み込み

プログラムコードを外部ファイルから読み込むには、2つ方法があります。

ひとつは、「@<code>|//list[][][file=...]|」のように「@<code>|//list|」の第3引数にファイル名を指定することです。
この場合、ブロックの中身は無視されます（ブロックそのものは省略できません）。

//list[][サンプル][]{
/@<nop>$$/list[][]@<b>|[file=source/fib3.rb]|{
/@<nop>$$/}
//}



もうひとつは、「@<code>|@@<nop>{}<include>{}|」というインライン命令を使うことです@<fn>{fn-yph1o}。

//footnote[fn-yph1o][参考：@<href>{https://github.com/kmuto/review/issues/887}]

//needvspace[latex][6zw]
//list[][サンプル][]{
/@<nop>$$/list[fib3][フィボナッチ数列]{
@<b>|@@<nop>$$<include>{source/fib3.rb}|
/@<nop>$$/}
//}



脚注のリンク先にあるように、この方法はRe:VIEWでは undocumented です。
Starterでは正式な機能としてサポートします。


=== タブ文字

プログラムコードの中にタブ文字があると、8文字幅のカラムに合うよう自動的に半角空白に展開されます。

しかし「@<code>|@@<nop>{}<b>{...}|」のようなインライン命令があると、カラム幅の計算が狂うため、意図したようには表示されないことがあります。

そのため、プログラムコードにはなるべくタブ文字を含めないほうがいいでしょう。


=== 全角文字の幅を半角2文字分にする

プログラムコードのデフォルトでは、全角文字の幅は半角文字2文字分より少し狭くなっています。
「@<code>|//list|」の第3引数に「@<code>|widecharfit=on|」というオプションを指定すると、全角文字の幅が半角文字2文字分に揃います。

//list[][サンプル][]{
/@<nop>$$/list[][][@<b>|widecharfit=on|]{
123456789_123456789_123456789_123456789_123456789_
あいうえおかきくけこさしすせそたちつてとなにぬねの
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//list[][][widecharfit=on]{
123456789_123456789_123456789_123456789_123456789_
あいうえおかきくけこさしすせそたちつてとなにぬねの
//}

//sampleoutputend



プログラムやターミナル画面において、全角と半角が混在しているせいで表示が崩れる場合は、このオプションを指定すると表示が崩れなくなります。

//list[][「@<code>|widecharfit=on|」がない場合：表示が崩れる]{
testdb1=> select * from members order by id;
 id  |   name   | height | gender
-----+----------+--------+--------
 101 | エレン   |    170 | M
 102 | ミカサ   |    170 | F
 103 | アルミン |    163 | M
 104 | ジャン   |    175 | M
 105 | サシャ   |    168 | F
 106 | コニー   |    158 | M
(6 rows)
//}

//list[][「@<code>|widecharfit=on|」がある場合：表示が崩れない][widecharfit=on]{
testdb1=> select * from members order by id;
 id  |   name   | height | gender
-----+----------+--------+--------
 101 | エレン   |    170 | M
 102 | ミカサ   |    170 | F
 103 | アルミン |    163 | M
 104 | ジャン   |    175 | M
 105 | サシャ   |    168 | F
 106 | コニー   |    158 | M
(6 rows)
//}

このオプションをデフォルトで有効にしたい場合は、@<secref>{04-customize|subsec-defaultopts}を参考にしてください。

//note[全角文字の判定]{
全角文字の判定は、現在は次のようなコードで行っており、かなりいい加減です。
改善については相談してください。

//list[][全角文字の判定方法(Ruby)][lang=ruby]{
string.each_char do |char|   # charは長さ1の文字列
  if char =~ /[\000-\177]/
    # 半角文字
  else
    # 全角文字
  end
end
//}

//}


==={subsec-output} 出力結果

出力結果や変換結果を表すための「@<code>|//output|」というブロック命令も用意されています。
使い方は「@<code>|//list|」と同じで、見た目が少し違うだけです。
たとえば自動生成されたHTMLやCSSを表示したり、SQLとその実行結果を分けて表示したいときに使うといいでしょう。

//list[][サンプル][]{
/@<nop>$$/list[][一覧を取得するSQL]{
select gender, count(*)
from members
group by gender
order by gender;
/@<nop>$$/}

@<b>|//output|[][実行結果]{
 gender | count
--------+-------
 F      |     2
 M      |     4
(2 rows)
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//list[][一覧を取得するSQL]{
select gender, count(*)
from members
group by gender
order by gender;
//}

//output[][実行結果]{
 gender | count
--------+-------
 F      |     2
 M      |     4
(2 rows)
//}

//sampleoutputend



「@<code>|//output|」では全角文字の幅が半角文字のちょうど2個分になるよう設定されているので、半角と全角が混在していても表示が崩れません@<fn>{fn-zt0xc}。

//footnote[fn-zt0xc][ただし、「@<code>|//output|」で使われる等幅フォントによっては表示が崩れることがあります。その場合は@<file>{config-starter.yml}で「@<code>|output_ttfont: beramono|」を指定してみてください。]

//list[][「@<code>|//list|」での表示結果（少し崩れる）]{
 id  |   name   | height | gender
-----+----------+--------+--------
 101 | エレン   |    170 | M
 102 | ミカサ   |    170 | F
 103 | アルミン |    163 | M
(3 rows)
//}

//output[][「@<code>|//output|」での表示結果（崩れない）]{
 id  |   name   | height | gender
-----+----------+--------+--------
 101 | エレン   |    170 | M
 102 | ミカサ   |    170 | F
 103 | アルミン |    163 | M
(3 rows)
//}


=== その他のオプション

「@<code>|//list|」の第3引数には、次のようなオプションも指定できます。

//desclist{
#@#//desc[@<code>$fold={on|off}$]{
#@#	長い行を自動で折り返します。
#@#	デフォルトは「@<code>|on|」。
#@#//}
#@#//desc[@<code>$foldmark={on|off}$]{
#@#	折り返したことを表す、小さな記号をつけます。
#@#	デフォルトは「@<code>|on|」。
#@#//}
#@#//desc[@<code>$eolmark={on|off}$]{
#@#	すべての行末に、行末であることを表す小さな記号をつけます。
#@#	「@<code>|foldmark=on|」 のかわりに使うことを想定していますが、両方を@<code>|on|。にしても使えます。
#@#	デフォルトは「@<code>|off|」。
#@#//}
//desc[@<code>$fontsize={small|x-small|xx-small|large|x-large|xx-large}$]{
	文字の大きさを小さく（または大きく）します。
	どうしてもプログラムコードを折返ししたくないときに使うといいでしょう。
//}
//desc[@<code>$lineno={on|off|@<i>{integer}}$]{
	行番号をつけます。詳細は次の節で説明します。
//}
//desc[@<code>$linenowidth={0|@<i>{integer}}$]{
	行番号の幅を指定します。詳細は次の節で説明します。
//}
//desc[@<code>$classname=@<i>{classname}$]{
	HTMLタグのクラス名を指定します。
	HTMLまたはePubのときだけ機能します。
//}
//desc[@<code>$lang=@<i>{langname}$]{
	プログラム言語の名前を指定します。
	コードハイライトのために使いますが、Starterではまだ対応していません。
//}
//}

なおオプションのデフォルト値は、「@<file>{congif-starter.yml}」で設定できます。
詳しくは@<secref>{04-customize|subsec-defaultopts}を参照してください。



=={sec-lineno} 行番号


=== プログラムリストに行番号をつける

プログラムリストに行番号をつけるには、「@<code>|//list|」ブロック命令の第3引数を次のように指定します。

//list[][サンプル][]{
/@<nop>$$/list[][][@<b>|lineno=on|]{
function fib(n) {
  return n <= 1 ? n : fib(n-1) + fib(n-2);
}
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//list[][][lineno=on]{
function fib(n) {
  return n <= 1 ? n : fib(n-1) + fib(n-2);
}
//}

//sampleoutputend



「@<code>{on}」のかわりに開始行番号を指定できます。

//list[][サンプル][]{
/@<nop>$$/list[][][@<b>|lineno=99|]{
function fib(n) {
  return n <= 1 ? n : fib(n-1) + fib(n-2);
}
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//list[][][lineno=99]{
function fib(n) {
  return n <= 1 ? n : fib(n-1) + fib(n-2);
}
//}

//sampleoutputend



「@<code>|lineno=1|」のかわりに「@<code>|1|」とだけ書いても、行番号がつきます。
行番号をつける方法としてはいちばん短い書き方です。

//list[][サンプル][]{
/@<nop>$$/list[][][@<b>|1|]{
function fib(n) {
  return n <= 1 ? n : fib(n-1) + fib(n-2);
}
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//list[][][1]{
function fib(n) {
  return n <= 1 ? n : fib(n-1) + fib(n-2);
}
//}

//sampleoutputend




=== 行番号の幅を指定する

前の例では行番号が外側に表示されました。
行番号の幅を指定すると、行番号が内側に表示されます。

//list[][サンプル][]{
/@<nop>$$/list[][][lineno=on,@<b>|linenowidth=3|]{
function fib(n) {
  return n <= 1 ? n : fib(n-1) + fib(n-2);
}
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//list[][][lineno=on,linenowidth=3]{
function fib(n) {
  return n <= 1 ? n : fib(n-1) + fib(n-2);
}
//}

//sampleoutputend



また幅を「@<code>{0}」に指定すると、行番号の幅を自動的に計算します。

//list[][サンプル][]{
/@<nop>$$/list[][][lineno=99,@<b>|linenowidth=0|]{
function fib(n) {
  return n <= 1 ? n : fib(n-1) + fib(n-2);
}
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//list[][][lineno=99,linenowidth=0]{
function fib(n) {
  return n <= 1 ? n : fib(n-1) + fib(n-2);
}
//}

//sampleoutputend



=== 複雑な行番号指定

行番号は「@<code>|lineno=80-83&97-100&105-|」のような複雑な指定もできます。

 * 「@<code>|80-83|」は80行目から83行目を表します。
 * 「@<code>|105-|」は105行目以降を表します。
 * 「@<code>|&|」は行番号をつけないことを表します。

//list[][サンプル][]{
/@<nop>$$/list[][][@<b>|lineno=80-83&97-100&105-|,linenowidth=0]{
/@<nop>$$/ JavaScript
function fib(n) {
  return n <= 1 ? n : fib(n-1) + fib(n-2);
}
...（省略）...
## Ruby
def fib(n)
  n <= 1 ? n : fib(n-1) + fib(n-2);
end
...（省略）...
## Python
def fib(n):
  return n if n <=1 else fib(n-1) + fib(n-2)
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//list[][][lineno=80-83&97-100&105-,linenowidth=0]{
// JavaScript
function fib(n) {
  return n <= 1 ? n : fib(n-1) + fib(n-2);
}
...（省略）...
## Ruby
def fib(n)
  n <= 1 ? n : fib(n-1) + fib(n-2);
end
...（省略）...
## Python
def fib(n):
  return n if n <=1 else fib(n-1) + fib(n-2)
//}

//sampleoutputend





=={sec-terminal} ターミナル


=== 基本的な書き方

ターミナル（端末）の画面を表すには、「@<code>|//terminal{ ... //}|」というブロック命令を使います。

//list[][サンプル][]{
@<b>|//terminal[?][PDFを生成]{|
$ rake pdf          @@<nop>$$<balloon>{Dockerを使わない場合}
$ rake docker:pdf   @@<nop>$$<balloon>{Dockerを使っている場合}
@<b>|//}|
//}

//sampleoutputbegin[表示結果]

//terminal[?][PDFを生成]{
$ rake pdf          @<balloon>{Dockerを使わない場合}
$ rake docker:pdf   @<balloon>{Dockerを使っている場合}
//}

//sampleoutputend



引数はプログラムリスト「@<code>|//list{ ... //}|」と同じなので、引数の説明は省略します。

過去との互換性のために、「@<code>|//cmd{ ... //}|」というブロック命令もあります。
しかしこの命令はリスト番号や行番号がつけられないし、「@<code>|//list|」命令と使い方が違うので、もはや使う必要はありません。

//list[][サンプル][]{
@<b>|//cmd|[PDFを生成]{
$ rake pdf          @@<nop>$$<balloon>{Dockerを使わない場合}
$ rake docker:pdf   @@<nop>$$<balloon>{Dockerを使っている場合}
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//cmd[PDFを生成]{
$ rake pdf          @<balloon>{Dockerを使わない場合}
$ rake docker:pdf   @<balloon>{Dockerを使っている場合}
//}

//sampleoutputend




=== ユーザ入力

「@<code>|@@<nop>{}<userinput>{}|」を使うと、ユーザによる入力箇所を示せます@<fn>{fn-pl9ll}。

//list[][サンプル][]{
/@<nop>$$/terminal[?][PDFを生成]{
$ @<b>|@@<nop>$$<userinput>{|rake pdf@<b>|}|          @@<nop>$$<balloon>{Dockerを使わない場合}
$ @<b>|@@<nop>$$<userinput>{|rake docker:pdf@<b>|}|   @@<nop>$$<balloon>{Dockerを使っている場合}
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//terminal[?][PDFを生成]{
$ @<userinput>{rake pdf}          @<balloon>{Dockerを使わない場合}
$ @<userinput>{rake docker:pdf}   @<balloon>{Dockerを使っている場合}
//}

//sampleoutputend



//footnote[fn-pl9ll][ただし、「@<code>|@@<nop>{}<userinput>{}|」では長い行を自動的に折り返せません。これは今後の課題です。]


=== ターミナルのカーソル

「@<code>|@@<nop>{}<cursor>{...}|」を使うと、ターミナルでのカーソルを表せます。

次の例では、2行目の真ん中の「f」にカーソルがあることを表しています。

//needvspace[latex][7zh]
//list[][サンプル][]{
/@<nop>$$/terminal{
function fib(n) {
  return n <= 1 ? n : @<b>|@@<nop>$$<cursor>{f}|ib(n-1) : fib(n-2);
}
~
~
"fib.js" 3L, 74C written
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//terminal{
function fib(n) {
  return n <= 1 ? n : @<cursor>{f}ib(n-1) : fib(n-2);
}
~
~
"fib.js" 3L, 74C written
//}

//sampleoutputend





=={sec-footnote} 脚注


=== 脚注の書き方

脚注は、脚注をつけたい箇所に「@<code>|@@<nop>{}<fn>{ラベル}|」を埋め込み、脚注の文は「@<code>|//footnote[ラベル][脚注文]|」のように書きます。

//list[][サンプル][]{
本文。本文@<b>|@@<nop>$$<fn>{fn-101}|。本文。

@<b>|//footnote[fn-101][脚注文。脚注文。]|
//}

//sampleoutputbegin[表示結果]

本文。本文@<fn>{fn-101}。本文。

//footnote[fn-101][脚注文。脚注文。]

//sampleoutputend



このページの最下部に脚注が表示されていることを確認してください。

また脚注文に「@<code>|]|」を埋め込む場合は、「@<code>|\]|」のようにエスケープしてください。

//list[][サンプル][]{
本文@@<nop>$$<fn>{fn-102}。

/@<nop>$$/footnote[fn-102][脚注に「@<b>|\]|」を入れる。]
//}

//sampleoutputbegin[表示結果]

本文@<fn>{fn-102}。

//footnote[fn-102][脚注に「\]」を入れる。]

//sampleoutputend




=== 脚注の注意点

@<LaTeX>{}の制限により、脚注が表示されなかったりエラーになることがあります。

 * コラムの中で脚注を使うと、脚注が表示されないことがあります。
   この場合、コラムを明示的に閉じてください。
   詳しくは@<secref>{subsec-columnfootnote}を参照してください。
 * ミニブロックの中で脚注を使うと、脚注が表示されないことがあります。
   ミニブロックについての詳細は@<secref>{subsec-miniblock}を参照してください。

//note[脚注がうまく表示されない理由]{
コラムやミニブロックでは、囲み枠が使われています。
@<LaTeX>{}で囲み枠を実現するには、「minipage環境」という機能を使うのが一般的です。
@<LaTeX>{}のminipage環境はページ内で別のページを実現する機能であり、HTMLでいうならiframeのようなものです。

そしてminipage環境はそれ自体が独立したページなので、minipage環境内で脚注を使うとそれが外側のページにうまく伝わりません。
これがコラムやミニブロックで脚注がうまく使えない理由です。

対策としては、コラムやミニブロックのデザイを枠線を使わないように変更することです。
または、コラムやミニブロックでは脚注を使わないように文章を工夫することです。

なおStarterでは、ミニブロックのうちノート（@<code>|//note|）に関してはminipage環境を使わないデザインにしています。
ノートについては次の節で紹介します。
//}



=={sec-note} ノート

補足情報や注意事項などを表示する枠を、Starterでは「ノート」と呼びます。


=== ノートの書き方

ノートは、「@<code>|//note{ ... //}|」というブロック命令で表します。

//list[][サンプル][]{
@<b>|//note[|締め切りを守るたったひとつの冴えたやり方@<b>|]{|
原稿の締め切りを守るための、素晴らしい方法を教えましょう。
それは、早い時期に執筆を開始することです。
@<b>|//}|
//}

//sampleoutputbegin[表示結果]

//note[締め切りを守るたったひとつの冴えたやり方]{
原稿の締め切りを守るための、素晴らしい方法を教えましょう。
それは、早い時期に執筆を開始することです。
//}

//sampleoutputend



ノートには、箇条書きやプログラムコードを入れられます（Starter独自拡張）。

//list[][サンプル][]{
/@<nop>$$/note[ノートタイトル]{
 * 箇条書き
 * 箇条書き

/@<nop>$$/list[][プログラムコード]{
def fib(n):
    return n if n <= 1 else fib(n-1) + fib(n-2)
/@<nop>$$/}
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//note[ノートタイトル]{
 * 箇条書き
 * 箇条書き

//list[][プログラムコード]{
def fib(n):
    return n if n <= 1 else fib(n-1) + fib(n-2)
//}
//}

//sampleoutputend



なお現在、ノートのタイトルに「@<code>|@@<nop>{}<code>{...}|」を入れると「@<code>|TeX capacity exceeded, sorry [input stack size=5000].|」という@<LaTeX>{}のエラーが発生します。
原因は不明なので、もしこのようなエラーが発生したらノートのタイトルから「@<code>|@@<nop>{}<code>{...}|」を外してみてください。


=== ラベルをつけて参照する

ノートにラベルをつけて、「@<code>|@@<nop>{}<noteref>{ラベル名}|」で参照できます（Starter独自拡張）。

//list[][サンプル][]{
/@<nop>$$/note@<b>|[note-123]|[詳細情報]{
詳細な説明は次のようになります。……
/@<nop>$$/}

詳しくは@<b>|@@<nop>$$<noteref>{note-123}|を参照してください。
//}

//sampleoutputbegin[表示結果]

//note[note-123][詳細情報]{
詳細な説明は次のようになります。……
//}

詳しくは@<noteref>{note-123}を参照してください。

//sampleoutputend



上の例で、第1引数がノートタイトルではなくラベル名になっていることに注意してください。
通常は次のどちらかを使うといいでしょう。

 * タイトルだけを指定するなら「@<code>|//note[タイトル]{...//}|」
 * ラベルとタイトルを指定するなら「@<code>|//note[ラベル][タイトル]{...//}|」

//note[ノートブロック命令における引数の詳しい仕様]{

「@<code>|//note|」ブロック命令は、過去との互換性を保ったままラベル機能を導入したので、引数の仕様が少し複雑になっています。

引数の詳しい仕様を@<table>{tbl-xthfx}にまとめました。
これを見ると分かるように、@<B>{第1引数だけを指定した場合はラベルではなくタイトルとみなされます}。
注意してください。

//tsize[*][|l|c|c|]
//table[tbl-xthfx][「@<code>|//note|」の引数の仕様]{
記述	ラベル	タイトル
--------------------
@<code>|//note[ラベル][タイトル]|	あり	あり
@<code>|//note[][タイトル]|	なし	あり
@<code>|//note[ラベル][]|	あり	なし
@<b>$@<code>|//note[タイトル]|$	@<B>{なし}	@<B>{あり}
@<code>|//note[][]|	なし	なし
@<code>|//note[]|	なし	なし
@<code>|//note|	なし	なし
//}

//}


==={subsec-miniblock} ノート以外のミニブロック

ノート以外にも、Re:VIEWでは次のようなブロックが用意されています。

 * 「@<code>|//memo|」（メモ）
 * 「@<code>|//tip|」（Tips）
 * 「@<code>|//info|」（情報）
 * 「@<code>|//warning|」（警告）
 * 「@<code>|//important|」（重要事項）
 * 「@<code>|//caution|」（注意喚起）
 * 「@<code>|//notice|」（お知らせ）

これらをRe:VIEWで使うとひどいデザインで表示されますが、Starterでは簡素なデザインで表示するよう修正しています。

//list[][サンプル][]{
@<b>|//notice|[ご来場のみなさまへ]{
本建物の内部には、王族しか入ることができません。
それ以外の方は入れないので、あらかじめご了承ください。
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//notice[ご来場のみなさまへ]{
本建物の内部には、王族しか入ることができません。
それ以外の方は入れないので、あらかじめご了承ください。
//}

//sampleoutputend



第1引数のタイトルは省略できます。

またStarterでは、「@<code>|//info|」と「@<code>|//caution|」と「@<code>|//warning|」に専用のアイコン画像@<fn>{fn-1sqbn}を用意しています。

//footnote[fn-1sqbn][これらのアイコン画像はパブリックドメインにするので、商用・非商用を問わず自由にお使いください。再配布も自由に行って構いません。]

//list[][サンプル][]{
@<b>|//info|[解決のヒント]{
本製品を手に取り、古くから伝わるおまじないを唱えてみましょう。
すると天空の城への門が開きます。
/@<nop>$$/}

@<b>|//caution|[使用上の注意]{
本製品を石版にかざすと、天空の城から雷が発射されます。
周りに人がいないことを確かめてから使用してください。
/@<nop>$$/}

@<b>|//warning|[重大な警告]{
本製品を持ったまま滅びの呪文を唱えると、天空の城は自動的に崩壊します。
大変危険ですので、決して唱えないでください。
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//info[解決のヒント]{
本製品を手に取り、古くから伝わるおまじないを唱えてみましょう。
すると天空の城への門が開きます。
//}

//caution[使用上の注意]{
本製品を石版にかざすと、天空の城から雷が発射されます。
周りに人がいないことを確かめてから使用してください。
//}

//warning[重大な警告]{
本製品を持ったまま滅びの呪文を唱えると、天空の城は自動的に崩壊します。
大変危険ですので、決して唱えないでください。
//}

//sampleoutputend



これらのアイコン画像はKeynoteでささっと作ったものなので、もっといいデザインのアイコン画像に変更するといいでしょう。
デザインの変更方法は@<secref>{04-customize|subec-miniblockdesign}を参照してください。

なお「@<code>|//note|」と違い、いくつか制限事項があります。

 * 参照用のラベルはつけられません。
 * @<LaTeX>{}の制限により、脚注がうまく表示されません。
 * @<LaTeX>{}の制限により、プログラムリストやターミナル画面がページをまたげません。
 * @<LaTeX>{}の制限により、画像と表の位置指定（「@<code>|[pos=h]|」のような指定）ができません。また強制的に「@<code>|pos=H|」が指定されたものとして扱われます。

//note[「warning」と「caution」の違い]{
「warning」と「caution」は、どちらも警告や注意を表す言葉ですが、次のような違いがあるそうです@<fn>{fn-2xk1v}。

 * 「warning」は致命的な結果になる可能性がある場合に使う。
 * 「caution」は望ましくない結果になる可能性がある場合に使う。

つまり「warning」は強い警告、「caution」は弱い警告だと思えばいいでしょう。

//footnote[fn-2xk1v][参考：@<href>{http://www.stevensstrategic.com/technical-writing-the-difference-between-warnings-and-cautions/, 『Technical Writing: The Difference Between Warnings and Cautions』}]

//}


=={sec-column} コラム


=== コラムとは

コラムは、補足情報や関連情報を記述する囲みです。
ノートとよく似ていますが、次のような違いがあります。

 * ノートは主に数行〜十数行程度の内容です。
   コラムはもっと長い内容に使うことが多いです。
 * ノートは目次に出ません。
   コラムは目次に出ます@<fn>{fn-ouf7u}。
 * ノートは文章のどこに書いても構いません。
   コラムは主に章(Chapter)の最後に書くことが多いです。

//footnote[fn-ouf7u][ただし「@<code>|[notoc\]|」オプションをつけた場合を除く。]

#@#ただし明確な違いはないので、ノートをコラム代わりに使っても、あるいはその逆でも間違いではないです。
ときどき、ノートで書くべき内容をすべてコラムとして書いている同人誌を見かけます。
間違いだとは言い切れないのですが、できれば両者の使い分けを意識しましょう。


=== コラムの書き方

コラムは「@<code>|==[column]|」と「@<code>|==[/column]|」か、または「@<code>|===[column]|」と「@<code>|===[/column]|」で囲みます（イコール記号の数が違うことに注意）。
また実装上の都合により、コラムを閉じる直前に空行を入れてください。

//list[][サンプル][]{
@<b>|===[column] サンプルコラム1|
コラム本文。

 - a. 箇条書き
 - b. 箇条書き

/@<nop>$$/list[][プログラムリスト]{
def fib(n):
    return n if n <= 1 else fib(n-1) + fib(n-2)
/@<nop>$$/}
                    @<balloon>|空行を入れてから、|
@<b>|===[/column]|        @<balloon>|コラムを閉じる|
//}

//sampleoutputbegin[表示結果]

===[column] サンプルコラム1
コラム本文。

 - a. 箇条書き
 - b. 箇条書き

//list[][プログラムリスト]{
def fib(n):
    return n if n <= 1 else fib(n-1) + fib(n-2)
//}

===[/column]

//sampleoutputend




==={subsec-columnfootnote} コラム内の脚注

前の例を見れば分かるように、コラムの中には箇条書きやプログラムリストなどを含めることができます。
ただし、脚注だけはコラムを閉じたあとに書く必要があります。

//list[][サンプル][]{
@<nop>$$===[column] サンプルコラム2
コラム本文@<b>|@@<nop>$$<fn>{fn-222}|。

@<nop>$$===[/column]                      @<balloon>|コラムを閉じて、|

@<b>|//footnote[fn-222][脚注の文章。]|  @<balloon>|そのあとに書くこと！|
//}

//sampleoutputbegin[表示結果]

===[column] サンプルコラム2
コラム本文@<fn>{fn-222}。

===[/column]

//footnote[fn-222][脚注の文章。]

//sampleoutputend




=== コラムを参照

コラムを参照するには、コラムにラベルをつけて、それを「@<code>|@@<nop>{}<column>{ラベル}|」で参照します。

//list[][サンプル][]{
@<nop>$$===[column]@<b>|{column3}| サンプルコラム3
サンプルコラム本文。

@<nop>$$===[/column]                      @<balloon>|コラムを閉じて、|

@<b>|@@<nop>$$<column>{column3}|を参照。
//}

//sampleoutputbegin[表示結果]

===[column]{column3} サンプルコラム3
サンプルコラム本文。

===[/column]

@<column>{column3}を参照。

//sampleoutputend




=== コラムの制限

現在、コラムには次のような制限があります。

 * コラム内で「@<code>|//list|」や「@<code>|//terminal|」を使うと、それらはページをまたいでくれません@<fn>{fn-giruq}。
 * 画像と表の位置指定ができません。「@<code>|//image[][][@<b>{pos=h}]|」や「@<code>|//table[][][@<b>{pos=h}]|」を指定するとエラーになるので@<fn>{fn-k247m}、指定しないでください。

これらの制限は仕様です。あきらめてください。

//footnote[fn-giruq][これは@<LaTeX>{}のframed環境による制限です。解決するにはframed環境を使わないよう変更する必要があります。]
//footnote[fn-k247m][oframe環境の中ではtable環境やfigure環境のようなフローティング要素が使えないという@<LaTeX>{}の制約が原因です。]

//note[コラムは見出しの一種]{
Re:VIEWおよびStarterでは、コラムは節(Section)や項(Subsection)といった見出しの一種として実装されています。
そのため、「@<code>|==[column]|」なら節(Section)と同じような扱いになり、「@<code>|===[column]|」なら項(Subsection)と同じような扱いになります（目次レベルを見るとよく分かります）。

また節や項は閉じる必要がない（勝手に閉じてくれる）のと同じように、コラムも「@<code>|===[/column]|」がなければ勝手に閉じてくれます。
しかし明示的に閉じないと脚注が出力されないことがあるので、横着をせずに明示的にコラムを閉じましょう。
//}



=={sec-image} 画像


=== 画像ファイルの読み込み方

画像を読み込むには、「@<code>|//image[画像ファイル名][説明文字列][オプション]|」を使います。

 * 画像ファイルは「@<file>{images/}」フォルダに置きます@<fn>{fn-6s711}。
 * 画像ファイル名には拡張子を指定しません（自動的に検出されます）。
 * 画像ファイル名がラベルを兼ねており、「@<code>|@@<nop>{}<img>{画像ファイル名}|」で参照できます。
 * 画像の表示幅は第3引数のオプションとして指定します。詳しくは後述します。
 * 第3引数のオプションは省略できます。どんなオプションが指定できるかは後述します。

//footnote[fn-6s711][画像ファイルを置くフォルダは、設定ファイル「@<file>{config.yml}」の設定項目「@<file>{imagedir}」で変更できますが、通常は変更する必要はないでしょう。]

次の例では、画像ファイル「@<file>{images/tw-icon1.jpg}」を読み込んでいます。

//list[][サンプル][]{
/@<nop>$$/image[tw-icon1][Twitterアイコン][width=30mm]
//}



表示例は@<img>{tw-icon1}を見てください。

//image[tw-icon1][Twitterアイコン][width=30mm]

//note[1つの画像ファイルを複数の箇所から読み込まない]{
「@<code>|//image|」コマンドでは、画像ファイル名がラベルを兼ねます。
そのせいで、1つの画像ファイルを複数の箇所で読み込むとラベルが重複してしまい、コンパイル時に警告が出ます。
また「@<code>|@@<nop>{}<img>{}|」で参照しても、画像番号がずれてしまい正しく参照できません。

Re:VIEWおよびStarterでは1つの画像ファイルを複数の箇所から読み込むのは止めておきましょう。
かわりにファイルをコピーしてファイル名を変えましょう@<fn>{fn-9d4pq}。
//footnote[fn-9d4pq][（分かる人向け）もちろんシンボリックリンクやハードリンクでもいいです。]
//}


=== 画像の表示幅を指定する

「@<code>|//image|」の第3引数に、画像を表示する幅を指定できます。
指定方法は2つあります。

//desclist[bold=off]{
//desc[@<code>|//image[\][\][@<b>{scale=0.5}\]|]{
画像の幅が本文幅より大きいか小さいかで挙動が変わります。

 * 画像の幅が本文幅より大きい場合は、本文幅を基準とします。この例なら、本文幅の半分の幅で表示されます。
 * 画像の幅が本文幅より小さい場合は、画像の幅を基準とします。この例なら、画像幅の半分の幅で表示されます。
//}
//desc[@<code>|//image[\][\][@<b>{width=50%}\]|]{
常に本文幅の半分の幅で画像を表示します。
また「@<code>|50%|」のような比率だけでなく、「@<code>|150px|」や「@<code>|50mm|」のように本文幅と関係ない長さの指定ができます。
値には必ず単位が必要であり、「@<code>|width=0.5|」のような指定はできません。
//}
//}

「@<code>|scale|」も「@<code>|width|」も指定しなかった場合は、次のように表示されます。

 * 画像の幅が本文幅より大きい場合は、本文幅に縮小されて表示されます。
 * 画像の幅が本文幅より小さい場合は、画像幅のままで表示されます@<fn>{3gyr7}。

//footnote[3gyr7][Re:VIEWでHTMLを生成すると、画像の幅が本文幅より小さい場合、本文幅いっぱいで表示されてしまいます。この挙動は困るので、Starterでは画像幅のままで表示するよう修正しています。]

なお「@<code>|scale=0.5|」はRe:VIEWでもStarterでも使えるオプションですが、「@<code>|width=50%|」はStarterでのみ使えるオプションです。
「@<code>|width=50%|」はRe:VIEWでは使えないので注意してください。

PDFとHTMLの場合で表示幅を変えるような指定もできます。
「@<code>|latex::width=100%, html::width=50%|」@<fn>{uzys8}のように指定すると、PDFのときは本文幅いっぱいに画像を表示し、HTMLのときは本文幅の半分の幅で画像を表示します。

//footnote[uzys8][この指定方法は、他のオプションや他のブロックコマンドでも使用できます。]

#@#//note[「@<code>|scale=0.5|」の挙動について]{
//note[「scale=0.5」の挙動について]{
@<href>{https://github.com/kmuto/review/blob/master/doc/format.ja.md#図, Re:VIEWのドキュメント}には、「@<code>|scale=0.5|」について次のように説明されています。

//quote{
3番目の引数として、画像の倍率・大きさを指定できます。
今のところ「scale=X」で倍率（X 倍）を指定でき、HTML、TeX ともに紙面（画面）幅に対しての倍率となります（0.5 なら半分の幅になります）。
//}

しかし、これは画像の幅が本文幅より大きい場合の説明です。
画像の幅が本文より小さい場合は、「@<code>|scale=0.5|」は本文幅の半分ではなく画像幅の半分になります。
つまり、こういうことです：

 * 画像の幅が本文幅より@<bou>{大きい}場合は、@<bou>{本文幅}を基準とする。
 * 画像の幅が本文幅より@<bou>{小さい}場合は、@<bou>{画像幅}を基準とする。

ややこしいことに、Re:VIEWがHTMLを生成するときは必ず本文幅を基準としてしまいます。
なぜなら、Re:VIEWでは画像の表示幅を指定するのに「@<code>|width:50%|」のようなCSSを使うためです。

これはPDFのときと挙動が大きく違うので、Starterではかわりに「@<code>|max-width:50%|」のようなCSSを使い、PDFの挙動に似せています。
ただし完全に同じ動作にはならないので、どうしてもRe:VIEWと互換性を持たせる必要がある場合を除き、「@<code>|scale=0.5|」ではなく「@<code>|width=50%|」を使うことを勧めます。
//}


=== 章ごとの画像フォルダ

画像ファイルは、章(Chapter)ごとのフォルダに置けます。
たとえば原稿ファイル名が「@<file>{02-tutorial.re}」であれば、章IDは「@<file>{02-tutorial}」なので、画像ファイルを「@<file>{images/02-tutorial/}」に置けます@<fn>{fn-31qgg}（特別な設定は不要です）。
これは複数の著者で一冊の本を執筆するときに便利です。
//footnote[fn-31qgg][もちろん「@<file>{images/}」にも置けます。]

詳しくは@<href>{https://github.com/kmuto/review/blob/master/doc/format.ja.md#%E7%94%BB%E5%83%8F%E3%83%95%E3%82%A1%E3%82%A4%E3%83%AB%E3%81%AE%E6%8E%A2%E7%B4%A2, Re:VIEWのマニュアル}を参照してください。


=== 画像のまわりに線をつける

第3引数に「@<code>|[border=on]|」をつけると、画像のまわりに灰色の線がつきます（Starter拡張）。

//list[][サンプル][]{
/@<nop>$$/image[tw-icon2][Twitterアイコン][scale=0.3@<b>|,border=on|]
//}



表示結果は@<img>{tw-icon2}を見てください。

//image[tw-icon2][Twitterアイコン][scale=0.3,border=on]


=== 画像の配置位置を指定する

第3引数に「@<code>|[pos=...]|」をつけると、読み込んだ画像をページのどこに配置するか、指定できます（Starter拡張）。

 : @<code>|pos=H|
	なるべく現在位置に配置します。
	現在位置に読み込めるスペースがなければ次のページの先頭に配置し、現在位置にはスペースが空いたままになります。
	Re:VIEWのデフォルトですが、ページ数が無駄に増えるのでお勧めしません。
 : @<code>|pos=h|
	上と似ていますが、画像が次のページの先頭に配置されたときは、現在位置に後続の文章が入るため、スペースが空きません。
	Starterのデフォルトです@<fn>{fn-4hoaz}。
 : @<code>|pos=t|
	ページ先頭に配置します。
 : @<code>|pos=b|
	ページ最下部に配置します。
 : @<code>|pos=p|
	独立したページに画像だけを配置します（後続の文章が入りません）。
	大きな画像はこれで表示するといいでしょう。

//footnote[fn-4hoaz][設定ファイル「@<file>{config-starter.yml}」の設定項目「@<file>{image_position:}」でデフォルト値を変更できます。]

//list[][サンプル][]{
現在位置に配置
/@<nop>$$/image[tw-icon][Twitterアイコン][scale=0.3@<b>|,pos=h|]

ページ先頭に配置
/@<nop>$$/image[tw-icon][Twitterアイコン][scale=0.3@<b>|,pos=t|]

ページ最下部に配置
/@<nop>$$/image[tw-icon][Twitterアイコン][scale=0.3@<b>|,pos=b|]
//}



「@<code>|pos=H|」と「@<code>|pos=h|」の違いは、@<img>{figure_heretop}を見ればよく分かるでしょう。

//image[figure_heretop][「@<code>{pos=H}」（上）と「@<code>{pos=h}」（下）の違い][scale=0.8]

ただし位置指定は、コラムの中では使えず、ノート以外のミニブロック（「@<code>|//info|」や「@<code>|//warning|」など）の中でも使えません。
どちらの場合も、位置指定は強制的に「@<code>|pos=H|」と同じ動作になります。
これは@<LaTeX>{}の制約からくる仕様です。


=== 画像に番号も説明もつけない

今まで説明したやり方では、画像に番号と説明文字列がつきました。
これらをつけず、単に画像ファイルを読み込みたいだけの場合は、「@<code>|//indepimage[ファイル名][][scale=1.0]|」を使ってください。
第2引数に説明文字列を指定できますが、通常は不要でしょう。

//list[][サンプル][]{
@<b>|//indepimage|[tw-icon3][][scale=0.3]
//}

//sampleoutputbegin[表示結果]

//indepimage[tw-icon3][][scale=0.3]

//sampleoutputend




=== 文章の途中に画像を読み込む

文章の途中に画像を読み込むには、「@<code>|@@<nop>{}<icon>{画像ファイル名}|」を使います。
画像の表示幅は指定できないようです。

//list[][サンプル][]{
文章の途中でファビコン画像「@<b>|@@<nop>$$<icon>{|favicon-16x16@<b>|}|」を読み込む。
//}

//sampleoutputbegin[表示結果]

文章の途中でファビコン画像「@<icon>{favicon-16x16}」を読み込む。

//sampleoutputend




=== 画像とテキストを並べて表示する

Starterでは、画像とテキストを並べて表示するためのコマンド「@<code>|//sideimage|」を用意しました。
著者紹介においてTwitterアイコンとともに使うといいでしょう。

//list[][サンプル][]{
@<b>|//sideimage[tw-icon4][20mm][side=L,sep=7mm,border=on]|{
/@<nop>$$/noindent
@@<nop>$$<B>{カウプラン機関極東支部}

 * @_kauplan (@@<nop>$$<href>{https://twitter.com/_kauplan/})
 * @@<nop>$$<href>{https://kauplan.org/}
 * 技術書典8新刊「Pythonの黒魔術」出ました。

/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//sideimage[tw-icon4][20mm][side=L,sep=7mm,border=on]{
//noindent
@<B>{カウプラン機関極東支部}

 * @_kauplan (@<href>{https://twitter.com/_kauplan/})
 * @<href>{https://kauplan.org/}
 * 技術書典8新刊「Pythonの黒魔術」出ました。

//}

//sampleoutputend



使い方は「@<code>$//sideimage[@<i>{画像ファイル}][@<i>{画像表示幅}][@<i>{オプション}]{$ ... @<code>$//}$」です。

 * 画像ファイルは「@<code>{//image}」と同じように指定します。
 * 画像表示幅は「@<code>{30mm}」「@<code>{3.0cm}」「@<code>{1zw}」「@<code>{10%}」などのように指定します。
   使用できる単位はこの4つであり、「@<code>{1zw}」は全角文字1文字分の幅、「@<code>{10%}」は本文幅の10%になります。
   なお「@<code>{//image}」と違い、単位がない「@<code>{0.1}」が10%を表すという仕様ではなく、エラーになります。
 * オプションはたとえば「@<code>{side=L,sep=7mm,boxwidth=40mm,border=on}」のように指定します。
 ** 「@<code>{side=L}」で画像が左側、「@<code>{side=R}」で画像が右側にきます。
    デフォルトは「@<code>{side=L}」。
 ** 「@<code>{sep=7mm}」は、画像と本文の間のセパレータとなる余白幅です。
    デフォルトはなし。
 ** 「@<code>{boxwidth=40mm}」は、画像を表示する領域の幅です。
    画像表示幅より広い長さを指定してください。
    デフォルトは画像表示幅と同じです。
 ** 「@<code>{border=on}」は、画像を灰色の線で囲みます。
    デフォルトはoff。

なお「@<code>{//sideimage}」は内部で@<LaTeX>{}のminipage環境を使っているため、次のような制限があります。

 * 途中で改ページされません。
 * 画像下へのテキストの回り込みはできません。
 * 脚注が使えません。

こういった制限があることを分かったうえで使ってください。



=={sec-table} 表


=== 表の書き方

表（テーブル）は「@<code>|//table[ラベル][説明文字列]{ ... //}|」のように書きます。

 * ラベルを使って「@<code>|@@<nop>{}table{ラベル}|」のように参照できます。
 * セルは1文字以上のタブ文字で区切ります。
 * ヘッダは12文字以上の「@<code>{-}」か「@<code>{=}」で区切ります。

//list[][サンプル][]{
@<b>|@@<nop>$$<table>{tbl-sample1}|を参照。

@<b>|//table[tbl-sample1][テーブルサンプル]{|
Name	Val	Val	Val
@<b>|--------------------------------|
AAA	10	10	10
BBB	100	100	100
CCC	1000	1000	1000
@<b>|//}|
//}

//sampleoutputbegin[表示結果]

@<table>{tbl-sample1}を参照。

//table[tbl-sample1][テーブルサンプル]{
Name	Val	Val	Val
--------------------------------
AAA	10	10	10
BBB	100	100	100
CCC	1000	1000	1000
//}

//sampleoutputend



#@#表示結果は@<table>{tbl-sample1}を見てください。



=== ラベルの自動採番

「@<code>|//table[][]|」の第1引数はラベルです。
これがないと、「表1.1」のような表示がされません。
しかし、重複しない文字列を用意して第1引数に設定するのは、結構面倒くさいです。

そこでStarterでは、ラベルのかわりに「@<code>{?}」を指定する機能を用意しました。
これを使うと、ランダム文字列が自動的に割り当てられるため、いつも「表1.1」のような表示がされます（これは「@<code>{//list[?]}」と同じ機能です）。

次の例では、「@<code>{//table}」の第1引数がラベルではなく「@<code>{?}」になっています。
これで重複しないランダム文字列が自動的に割り当てられるので、この表は番号つきで表示されます。

//list[][サンプル][]{
/@<nop>$$/table@<b>|[?]|[キャプション]{
Name	Val	Val	Val
--------------------------------
AAA	10	10	10
BBB	100	100	100
CCC	1000	1000	1000
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//table[?][キャプション]{
Name	Val	Val	Val
--------------------------------
AAA	10	10	10
BBB	100	100	100
CCC	1000	1000	1000
//}

//sampleoutputend




=== 右寄せ、左寄せ、中央揃え

セルの右寄せ(r)・左寄せ(l)・中央揃え(c)を指定するには、「@<code>{//tsize[latex][...]}」@<fn>{fn-8rpih}を使います。
ただし現在のところ、この機能はPDF用でありePubでは使えません。

//footnote[fn-8rpih][「@<code>{//tsize[pdf\][...\]}」ではなく「@<code>{//tsize[latex\][...\]}」なのは、内部で@<LaTeX>{}という組版用ソフトウェアを使っているからです。]

//list[][サンプル][]{
@<b>{//tsize[latex][|l|r|l|c|]}
/@<nop>$$/table[tbl-sample2][右寄せ(r)、左寄せ(l)、中央揃え(c)]{
Name	Val	Val	Val
--------------------------------
AAA	10	10	10
BBB	100	100	100
CCC	1000	1000	1000
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//tsize[latex][|l|r|l|c|]
//table[tbl-sample2][右寄せ(r)、左寄せ(l)、中央揃え(c)]{
Name	Val	Val	Val
--------------------------------
AAA	10	10	10
BBB	100	100	100
CCC	1000	1000	1000
//}

//sampleoutputend



#@#表示結果は@<table>{tbl-sample2}を見てください。

「@<code>{//tsize}」の使い方は2種類あります。

 - (A) 「@<code>{//tsize[|latex||r|l|c|]}」 … Re:VIEWでの書き方（Starterでも使える）
 - (B) 「@<code>{//tsize[latex][|r|l|c|]}」 … Starterで追加した書き方（Re:VIEWでは使えない）

(A)の書き方では、「@<code>|latex|」や「@<code>|html|」を表す縦線と、罫線を指定する縦線とが混在しており、とても分かりにくいです。
これに対し、Starterで追加された(B)の書き方であれば、ずっと見やすく書けます。
どうしてもRe:VIEWとの互換性が必要な場合を除き、(B)の書き方をお勧めします。

なお「@<code>{latex}」を指定しない場合は次のように書きます。

 * 「@<code>{//tsize[|||r|l|c|]}」 … Re:VIEWでの書き方
 * 「@<code>{//tsize[][|r|l|c|]}」 … Starterで追加した書き方
 * 「@<code>{//tsize[*][|r|l|c|]}」 … これでもよい

また「@<code>{//tsize[html,epub][...]}」のような指定もできます。
将来的に「@<code>{//tsize}」がHTMLやePubをサポートすれば、このような指定が役に立つでしょう。


=== 縦の罫線

「@<code>{//tsize[][|l|r|l|c|]}」の指定において、「@<code>{|}」は縦方向の罫線を表します。
これをなくすと罫線がつきません。
また「@<code>{||}」のように二重にすると、罫線も二重になります。

//list[][サンプル][]{
/@<nop>$$/tsize[][@<b>{l||rlc}]
/@<nop>$$/table[tbl-sample3][罫線をなくしたり、二重にしてみたり]{
Name	Val	Val	Val
--------------------------------
AAA	10	10	10
BBB	100	100	100
CCC	1000	1000	1000
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//tsize[][l||rlc]
//table[tbl-sample3][罫線をなくしたり、二重にしてみたり]{
Name	Val	Val	Val
--------------------------------
AAA	10	10	10
BBB	100	100	100
CCC	1000	1000	1000
//}

//sampleoutputend



#@#表示結果は@<table>{tbl-sample3}を見てください。


=== 横の罫線

Re:VIEWでは、表のどの行にも横の罫線が引かれます。
Starterでは、横の罫線を引かないように指定できます。
そのためには、第3引数に「@<code>{hline=off}」を指定します。

//needvspace[latex][6zw]
//list[][サンプル][]{
/@<nop>$$/tsize[][lrlc]
/@<nop>$$/table[tbl-sample4][横の罫線を引かない][@<b>|hline=off|]{
Name	Val	Val	Val
================================
AAA	10	10	10
BBB	100	100	100
CCC	1000	1000	1000
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//tsize[][lrlc]
//table[tbl-sample4][横の罫線を引かない][hline=off]{
Name	Val	Val	Val
================================
AAA	10	10	10
BBB	100	100	100
CCC	1000	1000	1000
//}

//sampleoutputend



「@<code>{hline=off}」を指定したとき、空行があるとそこに罫線が引かれます。

//needvspace[latex][6zw]
//list[][サンプル][]{
/@<nop>$$/tsize[][lrlc]
/@<nop>$$/table[tbl-sample5][空行が横の罫線になる][@<b>|hline=off|]{
Name	Val	Val	Val
================================
AAA	10	10	10
BBB	100	100	100

CCC	1000	1000	1000
DDD	1000	1000	1000

EEE	1000	1000	1000
FFF	1000	1000	1000
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//tsize[][lrlc]
//table[tbl-sample5][空行が横の罫線になる][hline=off]{
Name	Val	Val	Val
================================
AAA	10	10	10
BBB	100	100	100

CCC	1000	1000	1000
DDD	1000	1000	1000

EEE	1000	1000	1000
FFF	1000	1000	1000
//}

//sampleoutputend




必要な箇所だけに罫線を引くと、表が見やすくなります。
次の例を参考にしてください。

//needvspace[latex][6zw]
//list[][サンプル][widecharfit=on]{
/@<nop>$$/tsize[][llr]
/@<nop>$$/table[tbl-sample6][出版社別コミックス発行部数][@<b>|hline=off|]{
出版社  タイトル        発行部数
====================
集英社  鬼滅の刃        XXXX万部
.       ワンピース      XXX万部
.       ハイキュー!!    XXX万部
.       呪術廻戦        XXX万部

講談社  進撃の巨人      XXX万部
.       FAIRY TAIL      XXX万部

小学館  名探偵コナン    XXX万部
.       銀の匙          XXX万部
/@<nop>$$/}
//}



表示結果は@<table>{tbl-sample6}を見てください。

//tsize[][llr]
//table[tbl-sample6][出版社別コミックス発行部数][hline=off]{
出版社	タイトル	発行部数
====================
集英社	鬼滅の刃	XXXX万部
.	ワンピース	XXX万部
.	ハイキュー!!	XXX万部
.	呪術廻戦	XXX万部

講談社	進撃の巨人	XXX万部
.	FAIRY TAIL	XXX万部

小学館	名探偵コナン	XXX万部
.	銀の匙		XXX万部
//}


=== セル幅

セルの幅を指定するには、「@<code>{//tsize[][...]}」の中でたとえば「@<code>{p{20mm}}」のように指定します。

 * この場合、自動的に左寄せになります。右寄せや中央揃えにはできません。
 * セル内の長いテキストは自動的に折り返されます。
   表が横にはみ出てしまう場合はセル幅を指定するといいでしょう。

//list[][サンプル][]{
/@<nop>$$/tsize[latex][|l|@<b>|p{70mm}||]
/@<nop>$$/table[tbl-sample7][セルの幅を指定すると、長いテキストが折り返される]{
Name	Description
--------------------------------
AAA	text text text text text text text text text text text text text text text
BBB	text text text text text text text text text text text text text text text
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//tsize[latex][|l|p{70mm}|]
//table[tbl-sample7][セルの幅を指定すると、長いテキストが折り返される]{
Name	Description
--------------------------------
AAA	text text text text text text text text text text text text text text text
BBB	text text text text text text text text text text text text text text text
//}

//sampleoutputend



#@#表示結果は@<table>{tbl-sample4}を見てください。


=== 空欄

セルを空欄にするには、セルに「@<code>{.}」だけを書いてください。

//list[][サンプル][widecharfit=on]{
/@<nop>$$/tsize[latex][|l|ccc|]
/@<nop>$$/table[tbl-sample8][セルを空欄にするサンプル]{
評価項目                製品A   製品B   製品C
----------------------------------------
機能が充分か            ✓       ✓       .
価格が適切か            .       .       ✓
サポートがあるか        ✓       .       ✓
/@<nop>$$/}
//}



表示結果は@<table>{tbl-sample8}を見てください。

//tsize[latex][|l|ccc|]
//table[tbl-sample8][セルを空欄にするサンプル]{
評価項目		製品A	製品B	製品C
----------------------------------------
機能が充分か		✓	✓	.
価格が適切か		.	.	✓
サポートがあるか	✓	.	✓
//}

またセルの先頭が「@<code>{.}」で始まる場合は、「@<code>{..}」のように2つ書いてください。
そうしないと先頭の「@<code>{.}」が消えてしまいます。

//list[][サンプル][widecharfit=on]{
/@<nop>$$/table[tbl-sample9][セルの先頭が「@@<nop>$$<code>{.}」で始まる場合][headerrows=0]{
先頭に「.」が1つだけの場合      @<b>|.bashrc|
先頭に「.」が2つある場合        @<b>|..bashrc|
/@<nop>$$/}
//}



表示結果は@<table>{tbl-sample9}を見てください。

//table[tbl-sample9][セルの先頭が「@<code>{.}」で始まる場合][headerrows=0]{
先頭に「.」が1つだけの場合	.bashrc
先頭に「.」が2つある場合	..bashrc
//}


=== 表示位置の指定

表を表示する位置を、「@<code>{//table}」の第3引数で指定できます。

//list[][サンプル][]{
/@<nop>$$/table[tbl-sample10][表示位置を指定][@<b>|pos=ht|]{
....
/@<nop>$$/}
//}



指定できる文字は次の通りです。
また複数の文字を指定できます。

//desclist[compact=on,indent=5zw]{
//desc[pos=h][here（現在の場所）]
//desc[pos=H][here forcedly（現在の場所に強制）]
//desc[pos=t][top （ページ上部）]
//desc[pos=b][bottom （ページ下部）]
//desc[pos=p][page （その表だけのページ）]
//}

ただし位置指定は、コラムの中では使えず、ノート以外のミニブロック（「@<code>|//info|」や「@<code>|//warning|」など）の中でも使えません。
どちらの場合も、強制的に「@<code>|pos=H|」と同じ動作になります。
これは@<LaTeX>{}の制約からくる仕様です。


=== 表のフォントサイズ

表のフォントサイズを、「@<code>{//table}」の第3引数で指定できます。
表が大きくて1ページに収まらないとき使うといいでしょう@<fn>{dwrsy}。

//footnote[dwrsy][PDFでは表のフォントサイズがデフォルトでsmallになっています。そのため、「@<code>{//table[\][\][fontsize=small\]}」を指定しても小さくなりません。かわりに「@<code>{x-small}」を指定してください。]

//list[][サンプル][]{
/@<nop>$$/table[tbl-sample11][フォントを小さく][@<b>|fontsize=small|]{
Name	Val	Val	Val
================================
AAA	10	10	10
BBB	100	100	100
/@<nop>$$/}

/@<nop>$$/table[tbl-sample12][フォントをもっと小さく][@<b>|fontsize=x-small|]{
Name	Val	Val	Val
================================
AAA	10	10	10
BBB	100	100	100
/@<nop>$$/}

/@<nop>$$/table[tbl-sample13][フォントをもーっと小さく][@<b>|fontsize=xx-small|]{
Name	Val	Val	Val
================================
AAA	10	10	10
BBB	100	100	100
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//table[tbl-sample11][フォントを小さく][fontsize=small]{
Name	Val	Val	Val
================================
AAA	10	10	10
BBB	100	100	100
//}

//table[tbl-sample12][フォントをもっと小さく][fontsize=x-small]{
Name	Val	Val	Val
================================
AAA	10	10	10
BBB	100	100	100
//}

//table[tbl-sample13][フォントをもーっと小さく][fontsize=xx-small]{
Name	Val	Val	Val
================================
AAA	10	10	10
BBB	100	100	100
//}

//sampleoutputend



指定できるフォントサイズは次の通りです。

//table[on1lz][表のフォントサイズ]{
フォントサイズ	説明
====================
medium		本文と同じサイズ
small		少し小さく
x-small		小さく
xx-small	かなり小さく
large		少し大きく
x-large		大きく
xx-large	かなり大きく
//}


=== CSV形式の表

「@<code>|//table|」の第3引数に「@<code>|csv=on|」を指定すると、表をCSV形式で書けます（Starter拡張）。

//needvspace[latex][6zw]
//list[][サンプル][]{
/@<nop>$$/table[tbl-csv1][CSVテーブル][@<b>|csv=on|]{
Name,Val,Val,Val
================
AAA,10,10,10
BBB,100,100,100
CCC,1000,1000,1000
@<b>|//}|
//}

//sampleoutputbegin[表示結果]

//table[tbl-csv1][CSVテーブル][csv=on]{
Name,Val,Val,Val
================
AAA,10,10,10
BBB,100,100,100
CCC,1000,1000,1000
//}

//sampleoutputend



タブ区切りのときと同じように、12個以上の「@<code>{=}」でヘッダを区切ります。

CSV形式では、空欄はそのまま空欄として表示されます。
「@<code>{.}」を入力する必要はありません。
また「@<code>{"..."}」のようにすると、1つのセルに複数行の文字列を書けます。
ただし複数行で書いても表示は1行になります。

//list[][サンプル][]{
/@<nop>$$/table[tbl-csv2][CSVテーブル][csv=on]{
ぼくはか,@<b>|"|ぼくのとなりに
暗黒破壊神がいます@<b>|"|
はめふら,@<b>|"|乙女ゲームの破滅フラグしかない
悪役令嬢に転生してしまった…@<b>|"|
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//table[tbl-csv2][CSVテーブル][csv=on]{
ぼくはか,"ぼくのとなりに
暗黒破壊神がいます"
はめふら,"乙女ゲームの破滅フラグしかない
悪役令嬢に転生してしまった…"
//}

//sampleoutputend



表示も複数行にしたい場合は、明示的に改行します。

//list[][サンプル][]{
/@<nop>$$/table[tbl-csv3][CSVテーブル][csv=on]{
ぼくはか,"ぼくのとなりに@<b>|@@<nop>$$<br>{}|
暗黒破壊神がいます"
はめふら,"乙女ゲームの破滅フラグしかない@<b>|@@<nop>$$<br>{}|
悪役令嬢に転生してしまった…"
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//table[tbl-csv3][CSVテーブル][csv=on]{
ぼくはか,"ぼくのとなりに@<br>{}
暗黒破壊神がいます"
はめふら,"乙女ゲームの破滅フラグしかない@<br>{}
悪役令嬢に転生してしまった…"
//}

//sampleoutputend




=== 外部ファイルを読み込む

「@<code>|//table|」の第3引数に「@<code>|file=@<i>{filename}|」を指定すると、外部ファイルを読み込んでそれを表（テーブル）にできます（Starter拡張）。

 * ファイル名の拡張子が「@<code>{.csv}」なら、CSV形式で読み込まれます。
 * 第3引数に「@<code>{csv=on}」が指定された場合も、CSV形式で読み込まれます。
 * それ以外の場合は、タブ区切り形式で読み込まれます。

次の例では、「@<code>|data/data1.csv|」というファイルを読み込んで表にしています。
ブロック（「@<code>|{|」から「@<code>|//}|」まで）は省略できないので注意してください。

//list[][サンプル][]{
/@<nop>$$/table[tbl-csv4][サンプルデータ][@<b>|file=data/data1.csv|]{
/@<nop>$$/}
//}



文字コードを指定して読み込むこともできます。
指定できる文字コードは、「utf-8」「sjs」「shift_jis」「cp932」などです。
デフォルトはUTF-8です。

//list[][サンプル][]{
/@<nop>$$/table[tbl-csv5][サンプルデータ][file=data/data1.csv, @<b>|encoding=sjis|]{
/@<nop>$$/}
//}




=== ヘッダの行数を指定する

今までは、ヘッダを指定するには12個以上の「@<code>{=}」や「@<code>{-}」からなる区切り行を挿入する必要がありました。
しかし一般的なCSVファイルでは、このような区切り行は入れず、かわりに最初の行をヘッダ行と見なすことがほとんとではないでしょうか。

「@<code>|//table|」では第3引数に「@<code>|headerrows=1|」を指定すると、区切り行がなくても最初の行をヘッダとして扱ってくれます。

//list[][サンプル][]{
/@<nop>$$/table[tbl-csv6][先頭行をヘッダとみなす][csv=on,@<b>|headerrows=1|]{
Name,Val,Val,Val
AAA,10,10,10
BBB,100,100,100
CCC,1000,1000,1000
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//table[tbl-csv6][先頭行をヘッダとみなす][csv=on,headerrows=1]{
Name,Val,Val,Val
AAA,10,10,10
BBB,100,100,100
CCC,1000,1000,1000
//}

//sampleoutputend



また「@<code>|headerrows=@<b>{0}|」を指定すると、ヘッダ行のない表として表示されます。

//list[][サンプル][]{
/@<nop>$$/table[tbl-csv7][3×3の魔方陣][csv=on,@<b>|headerrows=0|]{
6,1,8
7,5,3
2,9,4
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//table[tbl-csv7][3×3の魔方陣][csv=on,headerrows=0]{
6,1,8
7,5,3
2,9,4
//}

//sampleoutputend




=== ヘッダのカラム数を指定する

「@<code>|//table[][][headercols=2]|」とすると、左から2つのカラムをヘッダとして表示します。

//list[][サンプル][]{
/@<nop>$$/table[tbl-csv8][左2つのカラムをヘッダとみなす][csv=on,@<b>|headercols=2|]{
Name,Val,Val,Val
AAA,10,10,10
BBB,100,100,100
CCC,1000,1000,1000
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//table[tbl-csv8][左2つのカラムをヘッダとみなす][csv=on,headercols=2]{
Name,Val,Val,Val
AAA,10,10,10
BBB,100,100,100
CCC,1000,1000,1000
//}

//sampleoutputend



このオプションは、ヘッダの行数を指定する「@<code>|headercols=1|」と共存できます。

//list[][サンプル][]{
/@<nop>$$/table[tbl-csv9][上と左をヘッダにする][csv=on,@<b>|headerrows=1,headercols=1|]{
Name,Val,Val,Val
AAA,10,10,10
BBB,100,100,100
CCC,1000,1000,1000
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//table[tbl-csv9][上と左をヘッダにする][csv=on,headerrows=1,headercols=1]{
Name,Val,Val,Val
AAA,10,10,10
BBB,100,100,100
CCC,1000,1000,1000
//}

//sampleoutputend




=== 表を画像で用意する

Re:VIEWやStarterでは、あまり複雑な表は作成できません。
複雑な表は画像として用意し、それを読み込むのがいいでしょう。

「@<code>|//imgtable|」コマンドを使うと、画像を表として読み込みます。
使い方は「@<code>|//image|」と同じです。

//needvspace[latex][6zw]
//list[][サンプル][]{
@<b>|//imgtable[order-detail][複雑な表の例：注文詳細][scale=0.5]{|
@<b>|//}|
//}

//sampleoutputbegin[表示結果]

//imgtable[order-detail][複雑な表の例：注文詳細][scale=0.5]{
//}

//sampleoutputend





=={sec-mathexpr} 数式


=== 数式の書き方

数式は「@<code>|//texequation[ラベル][説明文]{ ... //}|」のように書きます。

//list[][サンプル][]{
@<b>|//texequation[euler1][オイラーの公式]{|
e^{i\theta} = \sin{\theta} + i\cos{\theta}
@<b>|//}|
//}

//sampleoutputbegin[表示結果]

//texequation[euler1][オイラーの公式]{
e^{i\theta} = \sin{\theta} + i\cos{\theta}
//}

//sampleoutputend



数式の書き方が独特に見えますが、これは@<LaTeX>{}での書き方です。
@<LaTeX>{}における数式の書き方は、@<href>{https://en.wikibooks.org/wiki/LaTeX/Mathematics, Wikibooks}など他の資料をあたってください。

数式は、ラベルを使って「@<code>|@@<nop>{}<eq>{ラベル}|」のように参照できます。
たとえば「@<code>|@@<nop>{}<eq>{euler1}|」とすると「@<eq>{euler1}」となります。

ラベルや説明文がいらなければ、「@<code>|//texequation{ ... //}|」のように省略できます。


=== 数式を文中に埋め込む

数式を文中に埋め込むには「@<code>{@@<nop>{}<m>$...$}」を使います。

//list[][サンプル][]{
オイラーの公式は@<b>|@@<nop>$$<m>$e^{i\theta} = \sin{\theta} + i\cos{\theta}$|です。
特に、@<b>|@@<nop>$$<m>$\theta = \pi$|のときは@<b>|@@<nop>$$<m>$e^{i\pi} = -1$|となり、これはオイラーの等式と呼ばれます。
//}

//sampleoutputbegin[表示結果]

オイラーの公式は@<m>$e^{i\theta} = \sin{\theta} + i\cos{\theta}$です。
特に、@<m>$\theta = \pi$のときは@<m>$e^{i\pi} = -1$となり、これはオイラーの等式と呼ばれます。

//sampleoutputend




=== 数式のフォント

数式中では、アルファベットはイタリック体になります。
これは数式の伝統です。
次の例で、「@<code>|@@<nop>{}<m>$...$|」を使った場合と使わない場合を比べてください。

//list[][サンプル][]{
 * @<b>|@@<nop>$$<m>$y = f(x) + k$|  ← 使った場合
 * @<b>|y = f(x) + k|        ← 使わなかった場合
//}

//sampleoutputbegin[表示結果]

 * @<m>$y = f(x) + k$  ← 使った場合
 * y = f(x) + k        ← 使わなかった場合

//sampleoutputend




その他、Re:VIEWにおける数式の詳細は、Re:VIEWの@<href>{https://github.com/kmuto/review/blob/master/doc/format.ja.md#tex-%E5%BC%8F, Wiki}を参照してください。



=={sec-talk} 会話形式

Starterでは、会話形式の文章を書けます@<fn>{8a7k9}（Starter拡張）。

//footnote[8a7k9][LINEのようなチャット形式はサポートしていません。]


=== アイコン画像を使う場合

会話形式は次のようにして書きます。

 * 全体を「@<code>|//talklist{ ... //}|」で囲う。
 * 発言を「@<code>|//talk[]{ ... //}|」で囲う。
 * 「@<code>|//talk|」の第1引数にアイコン画像ファイルを指定する（「@<code>|//image|」の第1引数と同じ）。

//list[][サンプル][]{
@<b>|//talklist|{
@<b>|//talk[avatar-b]|{
できもしないことをおっしゃらないでください。
/@<nop>$$/}
@<b>|//talk[avatar-g]|{
不可能なことを言い立てるのは貴官の方だ。
それも安全な場所から動かずにな。
/@<nop>$$/}
@<b>|//talk[avatar-b]|{
……小官を侮辱なさるのですか。
/@<nop>$$/}
@<b>|//talk[avatar-g]|{
貴官は自己の才能を示すのに、弁舌ではなく実績をもってすべきだろう。
他人に命令するようなことが自分にもできるかどうか、やってみたらどうだ。
/@<nop>$$/}
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//talklist{
//talk[avatar-b]{
できもしないことをおっしゃらないでください。
//}
//talk[avatar-g]{
不可能なことを言い立てるのは貴官の方だ。
それも安全な場所から動かずにな。
//}
//talk[avatar-b]{
……小官を侮辱なさるのですか。
//}
//talk[avatar-g]{
貴官は自己の才能を示すのに、弁舌ではなく実績をもってすべきだろう。
他人に命令するようなことが自分にもできるかどうか、やってみたらどうだ。
//}
//}

//sampleoutputend



発言部分は自動的にカギ括弧でくくられます。
これを止めるには、設定ファイル「@<file>|config-starter.yml|」を変更します。
またアイコン画像の大きさも変更できます。
詳しくは後述します。

//note[白黒印刷でも判別できる画像を使う]{
このサンプルでは、色が違うだけのアイコン画像を使っています。
そのせいで、白黒印刷すると誰が誰だか判別できなくなります。
もし白黒印刷するなら、色に頼らず判別できるようなアイコン画像を使いましょう。
//}


=== アイコン画像を使わない場合

「@<code>|//talk|」の第1引数にアイコン画像を指定しない場合は、第2引数に名前を指定します。

//list[][サンプル][]{
/@<nop>$$/talklist{
@<b>|//talk[][A准将]|{
できもしないことをおっしゃらないでください。
/@<nop>$$/}
@<b>|//talk[][B提督]|{
不可能なことを言い立てるのは貴官の方だ。
それも安全な場所から動かずにな。
/@<nop>$$/}
@<b>|//talk[][A准将]|{
……小官を侮辱なさるのですか。
/@<nop>$$/}
@<b>|//talk[][B提督]|{
貴官は自己の才能を示すのに、弁舌ではなく実績をもってすべきだろう。
他人に命令するようなことが自分にもできるかどうか、やってみたらどうだ。
/@<nop>$$/}
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//talklist{
//talk[][A准将]{
できもしないことをおっしゃらないでください。
//}
//talk[][B提督]{
不可能なことを言い立てるのは貴官の方だ。
それも安全な場所から動かずにな。
//}
//talk[][A准将]{
……小官を侮辱なさるのですか。
//}
//talk[][B提督]{
貴官は自己の才能を示すのに、弁舌ではなく実績をもってすべきだろう。
他人に命令するようなことが自分にもできるかどうか、やってみたらどうだ。
//}
//}

//sampleoutputend



名前が長い場合は、会話の1行目だけ自動的に開始位置がずれます。

//list[][サンプル][]{
/@<nop>$$/talklist{
/@<nop>$$/talk[][@<b>|ビュコック提督|]{
貴官は自己の才能を示すのに、弁舌ではなく実績をもってすべきだろう。
他人に命令するようなことが自分にもできるかどうか、やってみたらどうだ。
/@<nop>$$/}
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//talklist{
//talk[][ビュコック提督]{
貴官は自己の才能を示すのに、弁舌ではなく実績をもってすべきだろう。
他人に命令するようなことが自分にもできるかどうか、やってみたらどうだ。
//}
//}

//sampleoutputend




アイコン画像と名前の両方を指定することは、現在はできません。
できるようにして欲しい人は、相談してください。


=== コンパクトな書き方

ブロック本体のかわりに、「@<code>|//talk|」の第3引数に会話文を書けます。
こうするとブロック本体を省略できるので、コンパクトな書き方になります。

また第3引数を使わない書き方と混在できます。
文章が短い場合だけ第3引数を使い、ある程度の長さがある場合はブロック本体に書くのがいいでしょう。

//list[][サンプル][]{
/@<nop>$$/talklist{
/@<nop>$$/talk[avatar-b][]@<b>|[|できもしないことをおっしゃらないでください。@<b>|]|
/@<nop>$$/talk[avatar-g][]@<b>|[|不可能なことを言い立てるのは貴官の方だ。それも安全な場所から動かずにな。@<b>|]|
/@<nop>$$/talk[avatar-b][]@<b>|[|……小官を侮辱なさるのですか。@<b>|]|
/@<nop>$$/talk[avatar-g]{
貴官は自己の才能を示すのに、弁舌ではなく実績をもってすべきだろう。
他人に命令するようなことが自分にもできるかどうか、やってみたらどうだ。
/@<nop>$$/}
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//talklist{
//talk[avatar-b][][できもしないことをおっしゃらないでください。]
//talk[avatar-g][][不可能なことを言い立てるのは貴官の方だ。それも安全な場所から動かずにな。]
//talk[avatar-b][][……小官を侮辱なさるのですか。]
//talk[avatar-g]{
貴官は自己の才能を示すのに、弁舌ではなく実績をもってすべきだろう。
他人に命令するようなことが自分にもできるかどうか、やってみたらどうだ。
//}
//}

//sampleoutputend



会話文を第3引数に書く場合は、「@<code>|]|」を「@<code>|\]|」のように書いてください@<fn>{mk3fo}。
そうしないとコンパイルエラーになるでしょう。

//footnote[mk3fo][これは脚注を書くときと同じ制約です。]


=== 短縮名

大量の会話を入力する場合、いちいちアイコン画像や名前を入力するのは面倒です。
そこでStarterでは、会話に使うアイコン画像や名前を短縮名で登録できる機能を用意しました。

まず、「@<file>{config-starter.yml}」に短縮名を登録します。
すでに以下のような設定がされているので、それを上書きするといいでしょう。

//list[][「@<file>{config-starter.yml}」に短縮名を登録]{
  talk_shortcuts:
    "b1":    {image: "avatar-b"}  # アイコン画像を使う場合
    "g1":    {image: "avatar-g"}  # アイコン画像を使う場合
    #"b1":   {name: "アリス"}     # アイコン画像を使わない場合
    #"g1":   {name: "ボブ"}       # アイコン画像を使わない場合
//}

そして、原稿では「@<code>|//t[短縮名]|」のように書きます。
たとえば「@<code>|//t[b1]|」は「@<code>|//talk[avatar-b]|」の短縮形となります。

前の項のサンプルを、短縮名を使って書いてみましょう。

//list[][サンプル][]{
/@<nop>$$/talklist{
@<b>|//t[b1]|[できもしないことをおっしゃらないでください。]
@<b>|//t[g1]|[不可能なことを言い立てるのは貴官の方だ。それも安全な場所から動かずにな。]
@<b>|//t[b1]|[……小官を侮辱なさるのですか。]
@<b>|//t[g1]|{
貴官は自己の才能を示すのに、弁舌ではなく実績をもってすべきだろう。
他人に命令するようなことが自分にもできるかどうか、やってみたらどうだ。
/@<nop>$$/}
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//talklist{
//t[b1][できもしないことをおっしゃらないでください。]
//t[g1][不可能なことを言い立てるのは貴官の方だ。それも安全な場所から動かずにな。]
//t[b1][……小官を侮辱なさるのですか。]
//t[g1]{
貴官は自己の才能を示すのに、弁舌ではなく実績をもってすべきだろう。
他人に命令するようなことが自分にもできるかどうか、やってみたらどうだ。
//}
//}

//sampleoutputend



短縮名を使うと、アイコン画像や登場人物名を変更するのも簡単になります。
変更の発生が予想される場合も、短縮機能を使うといいでしょう。


=== カスタマイズ

「@<code>|//talklist|」の第1引数にオプションを指定すると、会話形式の表示をカスタマイズできます。
たとえば次の例では、アイコン画像の幅を全角2文字分にし、会話文のインデント幅を全角4文字分にしています。

//list[][サンプル][]{
/@<nop>$$/talklist[@<b>|imagewidth=2zw,indent=4zw|]{
/@<nop>$$/talk[avatar-g]{
貴官は自己の才能を示すのに、弁舌ではなく実績をもってすべきだろう。
他人に命令するようなことが自分にもできるかどうか、やってみたらどうだ。
/@<nop>$$/}
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//talklist[imagewidth=2zw,indent=4zw]{
//talk[avatar-g]{
貴官は自己の才能を示すのに、弁舌ではなく実績をもってすべきだろう。
他人に命令するようなことが自分にもできるかどうか、やってみたらどうだ。
//}
//}

//sampleoutputend



指定できるオプションは@<table>{wkajz}の通りです。
これらは「@<code>|classname|」を除いて@<LaTeX>{}用であり、HTMLには「@<code>|classname|」しか適用されません。
またオプションを指定できるのは「@<code>|//talklist|」だけであり、「@<code>|//talk|」には指定できません。

//tsize[latex][|lcl|]
//table[wkajz][「@<code>|//talklist|」のオプション][hline=off]{
オプション名	デフォルト値	説明
--------------------
@<code>{indent}		@<code>{6zw}	本文左端から会話部分までの幅
@<code>{separator}	@<code>{：}	名前と会話文との区切り文字列
@<code>{imagewidth}	@<code>{4zw}	アイコン画像の幅
@<code>{imageheight}	.		画像高さ（通常は無指定でよい）
@<code>{imageborder}	@<code>{off}	「@<code>|on|」なら画像に枠線をつける
@<code>{needvspace}	@<code>{4zw}	必要な空きがなければ改ページ
@<code>{itemmargin}	@<code>{1mm}	会話項目間の空き
@<code>{listmargin}	@<code>{4mm}	会話リストの最初と最後の空き
@<code>{itemstart}	@<code>{「 }	会話文の先頭につける文字列
@<code>{itemend}	@<code>{」}	会話文の最後につける文字列
@<code>{classname}	.		HTMLタグに含めるクラス名
//}

@<table>{wkajz}のデフォルト値は、設定ファイル「@<file>|config-starter.yml|」で設定されています。
必要に応じて変更してください。

//list[][@<file>|config-starter.yml|]{
  ## 会話形式（`//talklist`）のデフォルトオプション
  ## （注：YAMLでは on は true と同じ、off は false と同じ）
  talklist_default_options:
    indent:      6zw       # 本文左端から会話部分までの幅
    separator:   "："      # 名前と会話文との区切り文字列
    imagewidth:  4zw       # アイコン画像の幅
    imageheight:           # 画像高さ（通常はnullでよい）
    imageborder: off       # on なら画像に枠線をつける
    needvspace:  4zw       # 必要な空きがなければ改ページ
    itemmargin:  1mm       # 会話項目間の空き
    listmargin:  0.5zw     # 会話リストの最初と最後の空き
    itemstart:   "「"      # 会話文の先頭につける文字列
    itemend:     "」"      # 会話文の最後につける文字列
    classname:             # HTMLタグに含めるクラス名
//}

たとえばアイコン画像の幅を全角3文字分にするには、次のように変更します。

//list[][@<file>|config-starter.yml|]{
  talklist_default_options:
    @<weak>|#...(省略)...|
    imagewidth:  @<b>{3zw}    # アイコン画像の幅
    @<weak>|#...(省略)...|
//}

また会話文にカギ括弧をつけないようにするには、次のように変更します。

//list[][@<file>|config-starter.yml|]{
  talklist_default_options:
    @<weak>|#...(省略)...|
    itemstart:   @<b>{""}     # 会話文の先頭につける文字列
    itemend:     @<b>{""}     # 会話文の最後につける文字列
    @<weak>|#...(省略)...|
//}

なお会話形式に関する@<LaTeX>{}マクロは「@<file>|sty/starter-talk.sty|」に定義されています。
必要であれば、マクロを「@<file>|sty/mystyle.sty|」にコピーしてから変更してください。

HTMLの場合は、「@<file>|css/webstyle.css|」をカスタマイズしてください。
クラス名が「@<code>|.talk-xxx|」のエントリが会話形式に関するルールです。

//list[][@<file>|css/webstyle.css|]{
.talk-image {
	width: 60px;   /* アイコン画像の表示幅 */
}
.talk-name {
	font-family: sans-serif;  /* 名前のフォント */
	font-weight: normal;
}
.talk-text {
	display: block;
	margin-left: 100px;   /* 会話文のインデント幅 */
	padding-top: 5px;
}
....（省略）....
//}



=={sec-term} 用語、索引

たいていの本では、巻末に索引が用意されています（@<img>{index-page}）。
Starterでは、指定した用語を索引に登録できます。
また用語に親子関係を持たせたり、転送先の用語を指定できます。

//image[index-page][索引ページ][width=80%, border=on]


=== 索引機能をオンにする

索引を作る機能は、デフォルトではオフになっています。
オンにするには、@<file>{config.yml}の370行目ぐらいにある「@<code>|makeindex: true|」を設定してください。

なお索引に用語が何も登録されていない場合、索引機能をオンにするとPDFのコンパイルがエラーになります。
1つでもいいから本文に用語を指定してから、索引機能をオンにしてください。

ややこしいのですが、索引機能がオフでも用語を索引に登録できます。
つまり、こういうことです：

 * 索引機能がオンのとき、索引に用語が何も登録されていないとエラー。
 * 索引機能がオフのとき、索引に用語を登録してもエラーにならない。

索引は@<LaTeX>{}の機能を使って生成しているので、索引機能は今のところPDFでのみサポートしています。
また索引機能をオンにすると、@<LaTeX>{}のコンパイル回数が増えてコンパイルに時間がかかるようになります。
執筆中は索引機能をオフにし、完成間近になったらオンにするといいでしょう。


=== 用語の書き方

用語の書き方は次の通りです。

 * 初めて登場した用語は「@<code>|@@<nop>{}<term>{用語名((よみかた))}|」のように書きます。
   すると用語名がゴシック体で表示され、かつ巻末の索引に載ります。
 * 再登場した用語は「@<code>|@@<nop>{}<idx>{用語名((よみかた))}|」のように書きます。
   すると索引には載るけど、ゴシック体にはなりません。
 * 「@<code>|@@<nop>{}<hidx>{用語名((よみかた))}|」(hidden index)とすると、索引に載るけど本文には何も表示されません。
 * 用語名が漢字を含まない場合（つまりひらがなやカタカナや英数字だけの場合）は、読み方を省略して「@<code>|@@<nop>{}<term>{用語名}|」のように書けます。
 * 索引に登録せずゴシック体で表示したいだけのときは、「@<code>|@@<nop>{}<termnoidx>{用語名}|」と書きます。
   「@<code>|@@<nop>{}<hidx>{}|」と組み合わせて使うことを想定しています。
   索引に登録しないので、よみがなは含めないでください。

//list[][サンプル][]{
@<b>|@@<nop>$$<term>|{アンジェ@<b>|(|@<b>|(|あんじぇ@<b>|)|@<b>|)|}。
@<b>|@@<nop>$$<idx>|{侍従長@<b>|(|@<b>|(|じじゅうちょう@<b>|)|@<b>|)|}。
@<b>|@@<nop>$$<term>|{Cボール}。
//}

//sampleoutputbegin[表示結果]

@<term>{アンジェ((あんじぇ))}。
@<idx>{侍従長((じじゅうちょう))}。
@<term>{Cボール}。

//sampleoutputend



この例だと、「アンジェ」と「Cボール」は@<code>|@@<nop>{}<term>{}|を使っているのでゴシック体、「内務卿」は@<code>|@@<nop>{}<idx>{}|を使っているので本文と同じ明朝体のままです。

用語には他のインライン命令を含められます。
その場合、必ず「@<code>$@@<nop>{}<term>@<b>{|}@@<nop>{}<xxx>{...}@<b>{|}$」のように書いてください（これは実装上の都合です）。
「@<code>$@@<nop>{}<term>@<b>|{|@@<nop>{}<xxx>{...}@<b>|}|$」だとエラーになります。

//list[][サンプル][]{
@@<nop>$$<term>|@@<nop>$$<ruby>{鹿威, ししおど}し((ししおどし))|。
@@<nop>$$<term>|@@<nop>$$<ruby>{黒星, くろぼし}@@<nop>$$<ruby>{紅白, こうはく}((くろぼしこうはく))|。
//}

//sampleoutputbegin[表示結果]

@<term>|@<ruby>{鹿威, ししおど}し((ししおどし))|。
@<term>|@<ruby>{黒星, くろぼし}@<ruby>{紅白, こうはく}((くろぼしこうはく))|。

//sampleoutputend



本文では用語にルビをつけたいけど索引ではつけたくないなら、「@<code>|@@<nop>{}<hidx>{}|」を使うといいでしょう。

//list[][サンプル][]{
@@<nop>$$<termnoidx>|@@<nop>$$<ruby>{鹿威, ししおど}し|@<b>|@@<nop>$$<hidx>|{鹿威し((ししおどし))}。
@@<nop>$$<ruby>{黒星, くろぼし}@@<nop>$$<ruby>{紅白, こうはく}@<b>|@@<nop>$$<hidx>|{黒星紅白((くろぼしこうはく))}。
//}




=== 親子関係にある用語

用語に親子関係がある場合、索引でそのように表示できます。
そのためには用語を「@<code>|<<>>|」で区切ります。

たとえば2つの用語「ケイバーライト」と「ケイバーライト症候群」がある場合は、前者を親項目、後者を子項目にして索引に登録できます。
また「アルビオン王国」「アルビオン共和国」「アルビオン王立航空軍」という3つの用語では、共通する「アルビオン」をあたかも存在する用語かのように見立てて索引に登録できます。

//list[][サンプル][]{
@@<nop>$$<term>{ケイバーライト((けいばーらいと))}。
@@<nop>$$<term>{ケイバーライト((けいばーらいと))@<b>|<<>>|症候群((しょうこうぐん))}。

@@<nop>$$<term>{アルビオン((あるびおん))@<b>|<<>>|王国((おうこく))}。
@@<nop>$$<term>{アルビオン((あるびおん))@<b>|<<>>|共和国((きょうわこく))}。
@@<nop>$$<term>{アルビオン((あるびおん))@<b>|<<>>|王立航空軍((おうりつこうくうぐん))}。
//}

//sampleoutputbegin[表示結果]

@<term>{ケイバーライト((けいばーらいと))}。
@<term>{ケイバーライト((けいばーらいと))<<>>症候群((しょうこうぐん))}。

@<term>{アルビオン((あるびおん))<<>>王国((おうこく))}。
@<term>{アルビオン((あるびおん))<<>>共和国((きょうわこく))}。
@<term>{アルビオン((あるびおん))<<>>王立航空軍((おうりつこうくうぐん))}。

//sampleoutputend



索引ページの表示結果は@<img>{index-page}を見てください。
これを見ると、「アルビオン」という用語は本文には登場していないので、索引の項目にページ番号がありません。
これに対し、同じ親項目でも「ケイバーライト」は本文に登場したので、ページ番号がついています。

なお、「@<code>|@@<nop>{}<idx>{アルビオン<<>>王国}|」と「@<code>|@@<nop>{}<idx>{アルビオン王国}|」は別々の用語として扱われるので、索引にも別々に載ります。
どちからに統一しましょう。

また用語に「@<code>|<<>>|」を2つ埋め込むと、親・子・孫の関係を表せます（が推奨しません）。
それ以上の深い関係は未対応です。


=== 親子関係の順番を入れ替える

今までのサンプルでは、親項目が前にきて子項目がその後ろについていました（例：「アルビオン」＋「王国」）。
そうではなく、親項目のほうが後ろ、子項目のほうが前にくる用語もあります。
たとえば「二重スパイ」という用語では、後ろにある「スパイ」が親項目、前にある「二重」が子項目です。

 * 「@<code>|@@<nop>{}<term>{二重((にじゅう))<<>>スパイ((すぱい))}|」だと、「二重」が親で「スパイ」が「子」になってしまいます。
 * 「@<code>|@@<nop>{}<term>{スパイ((すぱい))<<>>二重((にじゅう))}|」だと、親子関係は正しいものの、本文には「スパイ二重」と表示されてしまいます。

つまり、どちらの書き方も正しくありません。

このような場合、子要素の用語名に「@<code>|---|」を含めると、そこに親要素が入るものとして扱います。
たとえば「@<code>|@@<nop>{}<term>{スパイ((すぱい))<<>>二重@<b>{---}((にじゅう))}|」と書くと、「スパイ」が親で「二重」が子になる構造を指定しつつ、本文には「二重スパイ」と表示されます。

//list[][サンプル][]{
@@<nop>$$<term>{スパイ((すぱい))}。
@@<nop>$$<term>{スパイ((すぱい))<<>>二重@<b>|---|((にじゅう))}。
//}

//sampleoutputbegin[表示結果]

@<term>{スパイ((すぱい))}。
@<term>{スパイ((すぱい))<<>>二重---((にじゅう))}。

//sampleoutputend



索引ページの表示結果は@<img>{index-page}を見てください。

念のために注意しますが、「@<code>|---|」を含めるのは子要素の用語名です。
よみがなの中に入れてはいけません。
また親要素に入れた場合は何の効果もなくそのまま表示されます。


=== 転送先の用語を指定する

索引では、用語ごとにページ番号がつきます。
ただし、ページ番号ではなく「〜を見よ」のように転送先の用語を指定することがあります。
このような場合は、「@<code>|@@<nop>{}<term>{用語((よみがな))==>>転送先}|」のように書きます。
たとえば「空中艦隊」が「アルビオン王立航空軍」の別名なら、次のようにして前者から後者へ転送するといいでしょう。

//list[][サンプル][]{
@@<nop>$$<term>{アルビオン((あるびおん))<<>>王立航空軍((おうりつこうくうぐん))}。
@@<nop>$$<term>{空中艦隊((くうちゅうかんたい))@<b>|==>>|アルビオン王立航空軍}。
//}

//sampleoutputbegin[表示結果]

@<term>{アルビオン((あるびおん))<<>>王立航空軍((おうりつこうくうぐん))}。
@<term>{空中艦隊((くうちゅうかんたい))==>>アルビオン王立航空軍}。

//sampleoutputend



実際に試すと、転送先を表すのに「→」が使われます。
また表示結果（@<img>{index-page}）を見ると「→」に下線が引かれていますが、これは意図したものではありません。
原因は調査中です。

なお、転送先の用語が索引に登録されているかどうかのチェックは行っていません。
この場合だと、もし転送先の「アルビオン王立航空軍」が索引に登録されていなくてもエラーになりません。
これは仕様です{{(索引の機能を@<LaTeX>{}に任せているため、用語のチェックが難しいのです。)}}。


=== よみがなの再利用

一度指定したよみがなは、その用語が再び登場したときに再利用されます。

たとえば、用語が初めて登場したときに「@<code>|@@<nop>{}<term>{侍従長((じじゅうちょう))}|」のようによみがなを指定してます。
そして用語が再び登場したときに「@<code>|@@<nop>{}<idx>{侍従長}|」のようによみがなを省略すると、さきほどのよみがなが再利用されます。

親子関係にある用語でも、よみがなは再利用されます。
たとえば「@<code>|@@<nop><term>{アルビオン((あるびおん))<<>>王国((おうこく))}|」と一度書いておけば、その後は「@<code>|@@<nop><idx>{アルビオン<<>>王国}|」のようによみがなを省略できます。

再登場した用語のよみがなは、省略してもいいししなくてもいいです。
省略すれば前のよみがなが再利用され、省略しなければ再利用されないだけです。


=== よみがな辞書を使う

用語のよみがなは、辞書となるファイルに登録しておくこともできます。
そうしておけば、用語のよみがなを省略できます。
また複数人で執筆しているときに、索引に載せる用語と載せない用語を統一するのにも辞書ファイルが役立ちます。

よみがなの辞書ファイルはタブ区切りのテキストファイルであり、@<file>{config.yml}の「@<code>|makeindex_dic: yomigana.txt|」（370行目付近）でファイル名を指定します。
デフォルトでは@<file>{yomigana.txt}というファイルが指定されており、その中身は用語とよみがなのリストです@<fn>{fn-u2zh8}。
用語とよみがなは1つ以上のタブ文字で区切ってください。

//list[][よみがな辞書ファイルの中身]{
侍従長		じじゅうちょう
内務卿		ないむきょう
ハイランダー連隊	はいらんだーれんたい
//}

こうしておけば、「@<code>|@@<nop>{}<term>{侍従長((じじゅうちょう))}|」と書くかわりに「@<code>|@@<nop>{}<term>{じじゅうちょう}|」のように読みを省略して書けます。

//footnote[fn-u2zh8][このファイルは@<LaTeX>{}において索引を生成する「@<code>|mendex|」というコマンドで読み込まれます。@<code>|mendex|コマンドで読み取れるのが、タブ区切りのテキストファイルなのです。CSV形式は使えません。]

このほか、形態素解析エンジン「MeCab」を使うことでよみがなを用語から自動的に取得する機能がありますが、Starterでは推奨していません。
説明は省略するので、知りたい人は@<href>{https://github.com/kmuto/review/blob/master/doc/makeindex.ja.md, Re:VIEWのドキュメント}を読んでください。


=== 用語と索引の補足事項


==== 1つの用語に複数の読み方がある場合

たとえば「一也」という用語の読み方が「かずや」と「いちや」の2つある場合は、面倒でも
「@<code>|@@<nop>{}<idx>{一也((かずや))}|」と
「@<code>|@@<nop>{}<idx>{一也((いちや))}|」を使い分けてください。

またこのようなケースがあるため、同じ用語に対して違うよみがなが指定されてもエラーにはなりません。


==== 用語のよみがなが見つからなかった場合

よみがなが指定されず、よみがなの辞書ファイルにも登録されておらず、かつ漢字を含んだ用語（ひらがな・カタカナ・英数字以外の文字を含む用語）は、索引の最後に「■漢字」というグループがつくられ、そこに載ります。
本に索引をつけた場合は、索引の最後に「■漢字」がないかチェックしましょう。
もしあれば、よみがなを指定し忘れています@<fn>{fn-1ix79}。

//footnote[fn-1ix79][よみがなの指定し忘れを警告にする機能は検討中です。]


==== 索引の表示をカスタマイズする

索引の表示は、次のようなカスタマイズができます。

 * 用語とページ番号の間を、連続したピリオドではなく空白にする。
 * 用語のグループ化を行単位ではなく文字単位で行う。
 * 用語見出しを「■あ」のようなデザインから変更する。
 * 子要素の用語で使う「――」を別の文字列に変更する。
 * 「@<code>|@@<nop>{}<term>{}|」の表示をゴシック体から別の書体に変更する。

詳しくは@<secref>{04-customize|sec-index}を参照してください。
なお索引のカスタマイズには、@<LaTeX>{}の知識が必要です。

#@# * 索引ページにて用語とページ番号との間は、デフォルトでは連続したピリオドで埋めています。
#@#   これを空白で埋めるよう変更するには、@<file>{sty/indexsty.ist}を編集してください。
#@#   なお@<file>{sty/indexsty.ist}の中の設定項目については、@<href>{http://tug.ctan.org/info/mendex-doc/mendex.pdf, mendexコマンドのマニュアル}を参照してください。
#@# * 索引ページでは用語が「あ か さ た な は ……」のようにグループ化されます。
#@#   これを「あ い う え お か き ……」のようにグループ化するには、@<file>{config.yml}の「@<code>|makeindex_options: "-g"|」を「@<code>|makeindex_options: ""|」のように変更してください。
#@# * 索引ページの用語見出しは「■あ」「■か」のようになっています。
#@#   このデザインは@<file>{sty/starter-misc.sty}の「@<code>|\starterindexgroup|」で設定されています。
#@#   変更するには「@<code>|\starterindexgroup|」の定義を@<file>{sty/starter-misc.sty}から@<file>{sty/mystyle.sty}にコピーして、「{{,\newcommand,}}」を「{{,\renewcommand,}}」に変更して中身をカスタマイズしてください。
#@#   また@<file>{sty/indexsty.ist}を編集すると、別の@<LaTeX>{}マクロ名を指定できます。
#@# * 索引ページにおいて子要素の用語で使う「――」は、@<file>{sty/starter-misc.sty}の「@<code>|\starterindexplaceholder|」で定義されています。
#@# * 「@<code>|@@<nop>{}<term>{}|」で表示するフォントは、@<file>{sty/starter-misc.sty}の「@<code>|\starterterm|」で定義されています。
#@#   デフォルトではゴシック体にで表示するように定義されています。
#@# * 用語の転送先を表す「→」を別の記号や文字列に変更するには、@<file>{sty/mystyle.sty}にたとえば「@<code>|\renewcommand{\seename}{\textit{see: }}|」のように書きます。


=== Re:VIEWとの違い

Starterの索引機能は、Re:VIEWのそれを拡張しています。
違いは次の通りです。

 * 「@<code>|@@<nop>{}<idx>{}|」と「@<code>|@@<nop>{}<hidx>{}|」は、Re:VIEWにある機能です。
   Starterではそれを引き継いでいます。
 * 「@<code>|@@<nop>{}<term>{}|」はStarterによる拡張であり、Re:VIEWにはありません。
 * 「@<code>|@@<nop>{}<idx>{用語((よみがな))}|」のようによみがなを埋め込む機能は、Starterによる独自拡張です。
 * 「@<code>|@@<nop>{}<idx>{親用語<<>>子用語}|」のような親子関係の指定は、Re:VIEWにある機能です。
   Starterでも使えます。
 * 「@<code>|@@<nop>{}<idx>{親<<>>子---}|」のような親の位置を子で指定する機能は、Starterによる独自拡張です。
 * 「@<code>|@@<nop>{}<idx>{用語==>>転送先}|」のような親子関係の指定は、Starterによる独自拡張です。
 * よみがな辞書ファイルの機能は、Re:VIEWにある機能です。
 * 形態素解析エンジン「MeCab」を使ったよみがな自動取得機能は、Re:VIEWにある機能です。
   Starterでも設定すれば使えますが、トラブルが多いので推奨していません。

Re:VIEWの索引機能については、@<href>{https://github.com/kmuto/review/blob/master/doc/makeindex.ja.md, Re:VIEWのドキュメント}を参照してください。

.+note: これを読んでるRe:VIEW関係者の方へ
これを読んでるRe:VIEW関係者の方へお願いがあります。
Starterの機能を真似していただくのは構わないです（それどころか歓迎します）。
しかし、特に理由がないのにわざと違う仕様にするのはユーザに不利益を与えるだけなので、止めていただくようお願いします。

Starterによる拡張機能に問題があるから仕様を変えて導入した、というなら道理はあるでしょう。
しかしStarterを新機能の参考にしておきながら、わざわざ違う仕様にして導入するのは、ユーザの利益になりません。
#@#たとえばRe:VIEWに新しく「@<code>|@@<nop>{}<term>{}|」インライン命令を追加したり、「@<code>|@@<nop>{}<idx>{}|」の中によみがなを書けるよう拡張するなら、わざと違う仕様にせず、同じ仕様にしてくださるようお願いします。

競うなら公平・公正に。ユーザの利益を犠牲にする必要はありません。
.-note:



=={sec-words} 単語展開

キーと単語の組を単語辞書ファイルに登録しておけば、キーを単語に展開できます。
たとえば、辞書ファイル「@<file>{data/words.txt}」の中にキー「apple」と単語「アップル」を登録しておけば、「@<code>|@@<nop>{}<w>{apple}|」が「アップル」に展開されます。

この機能を使うと、表記が定まっていない単語の表記をあとから簡単に変更できます。
たとえば「Apple」と「アップル」のどちらの表記にするかまだ決まってなくても、本文に `@<w>{apple}` と書いておけば、あとから辞書の中身を変えるだけでどちらの表記にも対応できます。

なお単語にはインライン命令を含められません。


=== 単語展開用のインライン命令

単語展開のためのインライン命令は3つあります。

 * 「@<code>|@@<nop>{}<w>{}|」は、キーに対応した単語へと展開するだけです。
 * 「@<code>|@@<nop>{}<wb>{}|」は、展開してから太字にします。
   実質的に「@<code>|@@<nop>{}<b>{@@<nop>{}<w>{}}|」と同じです。
 * 「@<code>|@@<nop>{}<W>{}|」は、展開してから強調表示します。
   実質的に「@<code>|@@<nop>{}<B>{@@<nop>{}<w>{}}|」と同じです。

//list[][サンプル][]{
 * @<b>|@@<nop>$$<w>|{apple} …… 展開するだけ
 * @<b>|@@<nop>$$<wb>|{apple} …… 展開して太字に
 * @<b>|@@<nop>$$<W>|{apple} …… 展開して強調表示
//}

//sampleoutputbegin[表示結果]

 * @<w>{apple} …… 展開するだけ
 * @<wb>{apple} …… 展開して太字に
 * @<W>{apple} …… 展開して強調表示

//sampleoutputend




=== 単語展開用の辞書ファイル

単語展開用の辞書ファイルは、@<file>{config.yml}の「@<code>|words_file|」で指定します。
デフォルトでは「@<code>|data/words.txt|」が指定されています。

辞書ファイルは、CSVファイル（@<file>{*.csv}）か、タブ文字区切りのファイル（@<file>{*.txt}または@<file>{*.tsv}）を指定します。
どちらの形式かはファイル名の拡張子で判断します。

辞書ファイルは複数指定できます。
たとえば「@<code>|words_file: [data/f1.txt, data/f2.txt]|」とすれば、@<file>{data/f1.txt}と@<file>{data/f2.txt}を読み込みます。
キーが重複していてもエラーにはならず、あとから読み込まれたほうが使われます。

辞書ファイルの文字コードはUTF-8しか使えません。


=== Re:VIEWとの違い

 * Re:VIEWでは、辞書ファイルとしてCSVファイルしか指定できません。
   Starterだと、タブ文字区切りのテキストファイルも指定できます。
   テキストエディタで編集しやすいのは、CSVファイルよりもタブ文字区切りのテキストファイルのほうです。
 * Re:VIEWには「@<code>|@@<nop>{}<W>|」がありません。
 * Starterではデフォルトで辞書ファイル「@<file>|data/words.txt|」が提供済みです。
   設定ファイルを編集しなくても最初から@<code>|@@<nop>{}<w>{}|が利用可能です。



=={sec-misc} その他


=== URL、リンク

URLは「@<code>|@@<nop>{}<href>{URL}|」と書きます。

//list[][サンプル][]{
Re:VIEW Starter：@<b>|@@<nop>$$<href>{|https://kauplan.org/reviewstarter/@<b>|}|
//}

//sampleoutputbegin[表示結果]

Re:VIEW Starter：@<href>{https://kauplan.org/reviewstarter/}

//sampleoutputend



リンクは「@<code>|@@<nop>{}<href>{URL, テキスト}|」と書きます。

//list[][サンプル][]{
@<b>|@@<nop>$$<href>{|https://kauplan.org/reviewstarter/@<b>|, |Re:VIEW Starter@<b>|}|
//}

//sampleoutputbegin[表示結果]

@<href>{https://kauplan.org/reviewstarter/, Re:VIEW Starter}

//sampleoutputend



PDFの場合、リンクのURLは自動的に脚注に書かれます（Starter拡張）。
これは印刷時でもURLが読めるようにするためです。
この拡張機能をオフにするには、@<file>{starter-config.yml}で設定項目「@<code>{linkurl_footnote:}」を「@<code>{false}」または「@<code>{off}」にします。

もし「@<code>{linkurl_footnote:}」の設定に関係なく、必ずリンクを使いたい（URLを脚注に書かない）場合は、「@<code>|@@<nop>{}<hlink>{...}|」を使ってください。
使い方は「@<code>|@@<nop>{}<href>{...}|」と同じです。

「@<code>|@@<nop>{}<href>{}|」と「@<code>|@@<nop>{}<hlink>{}|」の違いを比べて見ましょう。

//list[][サンプル][]{
 * @<b>|@@<nop>$$<href>|{https://twitter.com/_kauplan/, @_kauplan}
 * @<b>|@@<nop>$$<hlink>|{https://twitter.com/_kauplan/, @_kauplan}
//}

//sampleoutputbegin[表示結果]

 * @<href>{https://twitter.com/_kauplan/, @_kauplan}
 * @<hlink>{https://twitter.com/_kauplan/, @_kauplan}

//sampleoutputend




=== 引用

引用は「@<code>|//quote{ ... //}|」で表します。

//list[][サンプル][]{
@<b>|//quote{|
/@<nop>$$/noindent
その者、蒼き衣を纏いて金色の野に降り立つべし。@@<nop>$$<br>{}
失われし大地との絆を結び、ついに人々を青き清浄の地に導かん。
@<b>|//}|
//}

//sampleoutputbegin[表示結果]

//quote{
//noindent
その者、蒼き衣を纏いて金色の野に降り立つべし。@<br>{}
失われし大地との絆を結び、ついに人々を青き清浄の地に導かん。
//}

//sampleoutputend




=== 傍点

傍点は「@<code>|@@<nop>{}<bou>{...}|」でつけられます。

//list[][サンプル][]{
@<b>|@@<nop>$$<bou>{|三分間@<b>|}|、待ってやる。
//}

//sampleoutputbegin[表示結果]

@<bou>{三分間}、待ってやる。

//sampleoutputend



傍点は、太字で強調するほどではないけど読者の注意を向けたいときに使います。
ただしアルファベットや記号ではあまりよいデザインにはなりません。


=== ルビ、読みがな

ルビ（あるいは読みがな）は「@<code>|@@<nop>{}<ruby>{テキスト, ルビ}|」のように書きます。

//list[][サンプル][]{
@<b>|@@<nop>$$<ruby>{|約束された勝利の剣@<b>|, |エクスカリバー@<b>|}|
//}

//sampleoutputbegin[表示結果]

@<ruby>{約束された勝利の剣, エクスカリバー}

//sampleoutputend



途中の「@<code>{, }」は必ず半角文字を使い、全角文字は使わないでください。


=== 何もしないコマンド

「@<code>|@@<nop>{}<nop>{}|」@<fn>{fn-tflcc}は、何もしないコマンドです。
これは、たとえばインライン命令の「@<code>|@|」と「@<code>|<|」の間に入れることで、インライン命令として解釈されないようごまかすために使います。

//footnote[fn-tflcc][「nop」は「No Operation」の略です。]

//list[][サンプル][]{
強調される： @@<nop>$$<B>{テキスト}。

強調されない： @@<b>|@@<nop>$$<nop>{}|<B>{テキスト}。
//}

//sampleoutputbegin[表示結果]

強調される： @<B>{テキスト}。

強調されない： @@<nop>{}<B>{テキスト}。

//sampleoutputend



またブロック命令の行頭に「@<code>|@@<nop>{}<nop>{}|」を入れると、ブロック命令として解釈されなくなります。


=== コード中コメント

プログラムコードやターミナルにおいて、コメントを記述するための「@<code>|@@<nop>{}<balloon>{...}|」というコマンドが用意されています。

//needvspace[latex][5zw]
//list[][サンプル][]{
/@<nop>$$/terminal{
$ @@<nop>$$<userinput>{unzip mybook.zip}       @<b>|@@<nop>$$<balloon>{|zipファイルを解凍@<b>|}|
$ @@<nop>$$<userinput>{cd mybook/}             @<b>|@@<nop>$$<balloon>{|ディレクトリを移動@<b>|}|
$ @@<nop>$$<userinput>{rake pdf}               @<b>|@@<nop>$$<balloon>{|PDFファイルを生成@<b>|}|
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//terminal{
$ @<userinput>{unzip mybook.zip}       @<balloon>{zipファイルを解凍}
$ @<userinput>{cd mybook/}             @<balloon>{ディレクトリを移動}
$ @<userinput>{rake pdf}               @<balloon>{PDFファイルを生成}
//}

//sampleoutputend



Re:VIEWのドキュメントを読むと、本来は吹き出し（バルーン）形式で表示することを意図していたようです。
Starterでは、「←」つきのグレーで表示しています。

なおプログラムコードにおいて改行記号を表示している場合、「@<code>|@@<nop>{}<balloon>{}|」があるとそれより後に改行文字が表示されてしまいます。
たとえば次の例だと、改行記号は「←再帰呼び出し」の前につくべきですが、実際には後についています。
これは期待される挙動ではないでしょう。

//needvspace[latex][5zw]
//list[][サンプル][]{
/@<nop>$$/program[][改行記号と「@@@<nop>$$<nop>{}<balloon>{}」は相性が悪い][@<b>|eolmark=on|]{
function fib(n) {
  if (n <= 1) { return n };
  return fib(n-1) + fib(n-2);  @<b>|@@<nop>$$<balloon>{|再帰呼び出し@<b>|}|
}
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//program[][改行記号と「@@<nop>{}<balloon>{}」は相性が悪い][eolmark=on]{
function fib(n) {
  if (n <= 1) { return n };
  return fib(n-1) + fib(n-2);  @<balloon>{再帰呼び出し}
}
//}

//sampleoutputend



この問題については将来的に対応予定ですが、現在はまだ対応できていません。


=== 特殊文字

 * 「@<code>|@@<nop>{}<hearts>{}|」で「@<hearts>{}」が表示できます。
 * 「@<code>|@@<nop>{}<TeX>{}|」で「@<TeX>{}」が表示できます。
 * 「@<code>|@@<nop>{}<LaTeX>{}|」で「@<LaTeX>{}」が表示できます。


=== 右寄せ、センタリング

右寄せとセンタリングのブロック命令があります。

//list[][サンプル][]{
/@<nop>$$/flushright{
右寄せのサンプル
/@<nop>$$/}
/@<nop>$$/centering{
センタリングのサンプル
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//flushright{
右寄せのサンプル
//}
//centering{
センタリングのサンプル
//}

//sampleoutputend




=== 縦方向の空き（実験的機能）

「@<code>|//vspace|」を使って、縦方向の空きを入れられます。
マイナスの値を指定すると、空きを削除できます。

//list[][サンプル][]{
AAAAA

BBBBB

@<b>|//vspace[latex][-4mm]|
CCCCC
//}

//sampleoutputbegin[表示結果]

AAAAA

BBBBB

//vspace[latex][-4mm]
CCCCC

//sampleoutputend




=== 生データ

@<LaTeX>{}のコード（PDFのとき）やHTMLのコード（ePubのとき）を埋め込む機能があります。
たとえば次の例では、PDFのときは「@<code>|//embed[latex]{...//}|」のコードが使われ、HTMLとePubのときだけ「@<code>|//embed[html,epub]{...//}|」のコードが使われます。

//list[][サンプル][]{
@<b>|//embed[latex]{|
\textcolor{red}{Red}
\textcolor{green}{Green}
\textcolor{blue}{Blue}
\par
@<b>|//}|

@<b>|//embed[html,epub]{|
<div>
  <span style="color:red">Red</span>
  <span style="color:green">Green</span>
  <span style="color:blue">Blue</span>
</div>
@<b>|//}|
//}

//sampleoutputbegin[表示結果]

//embed[latex]{
\textcolor{red}{Red}
\textcolor{green}{Green}
\textcolor{blue}{Blue}
\par
//}

//embed[html,epub]{
<div>
  <span style="color:red">Red</span>
  <span style="color:green">Green</span>
  <span style="color:blue">Blue</span>
</div>
//}

//sampleoutputend



またインライン命令の「@<code>|@@<nop>{}<embed>{...}|」もあります。

 * 「@<code>$@@<nop>{}<embed>{|latex|...}$」なら@<LaTeX>{}のときだけ中身が出力されます。
 * 「@<code>$@@<nop>{}<embed>{|htlm,epub|...}$」ならHTMLとePubのときだけ中身が出力されます。


=== 参考文献

（未執筆。Re:VIEWの@<href>{https://github.com/kmuto/review/blob/master/doc/format.ja.md#%E5%8F%82%E8%80%83%E6%96%87%E7%8C%AE%E3%81%AE%E5%AE%9A%E7%BE%A9, Wiki}を参照してください。）
