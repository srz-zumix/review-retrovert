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

//list[][サンプル]{
本文1
@<b>|#@#|本文2
本文3
//}

//sampleoutputbegin[表示結果]

本文1
#@#本文2
本文3

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

//list[][サンプル]{
本文1

@<b>|#@+++|
本文2

本文3
@<b>|#@---|

本文4
//}

//sampleoutputbegin[表示結果]

本文1

#@+++
本文2

本文3
#@---

本文4

//sampleoutputend



範囲コメントは入れ子にできません。
また「@<code>{+}」「@<code>{-}」の数は3つと決め打ちされてます。

なお範囲コメントはStarterによる拡張機能です。



=={sec-paragraph} 段落と改行と空行


=== 段落

空行を入れると、段落の区切りになります。
空行は何行入れても、1行の空行と同じ扱いになります。

//list[][サンプル]{
言葉を慎みたまえ！君はラピュタ王の前にいるのだ！

これから王国の復活を祝って、諸君にラピュタの力を見せてやろうと思ってね。見せてあげよう、ラピュタの雷を！

旧約聖書にあるソドムとゴモラを滅ぼした天の火だよ。ラーマヤーナではインドラの矢とも伝えているがね。
//}

//sampleoutputbegin[表示結果]

言葉を慎みたまえ！君はラピュタ王の前にいるのだ！

これから王国の復活を祝って、諸君にラピュタの力を見せてやろうと思ってね。見せてあげよう、ラピュタの雷を！

旧約聖書にあるソドムとゴモラを滅ぼした天の火だよ。ラーマヤーナではインドラの矢とも伝えているがね。

//sampleoutputend



段落は、PDFなら先頭の行を字下げ（インデント）し、ePubなら1行空けて表示されます。
また段落の前に「@<code>|//noindent|」をつけると、段落の先頭の字下げ（インデント）をしなくなります。

//list[][サンプル]{
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

//list[][サンプル]{
あいうえ@<b>|お|
@<b>|か|きくけ@<b>|こ|
@<b>|さ|しすせそ

たちつてとAB@<b>|C|
@<b>|な|にぬね@<b>|の|
@<b>|D|EFはひふへほ

まみむめもGH@<b>|I|
@<b>|J|KLらりるれろMN@<b>|O|
@<b>|P|QRやゆよ
//}

//sampleoutputbegin[表示結果]

あいうえお
かきくけこ
さしすせそ

たちつてとABC
なにぬねの
DEFはひふへほ

まみむめもGHI
JKLらりるれろMNO
PQRやゆよ

//sampleoutputend




=== 強制改行

強制的に改行したい場合は、「@<code>|@@<nop>{}<br>{}|」を使います。

//list[][サンプル]{
土に根をおろし、風と共に生きよう@<b>|@@<nop>$$<br>{}|
種と共に冬を越え、鳥と共に春をうたおう
//}

//sampleoutputbegin[表示結果]

土に根をおろし、風と共に生きよう@<br>{}
種と共に冬を越え、鳥と共に春をうたおう

//sampleoutputend



なおこの例だと、「@<code>|//noindent|」をつけて段落の字下げをしないほうがいいでしょう。

//list[][サンプル]{
@<b>|//noindent|
土に根をおろし、風と共に生きよう@@<nop>$$<br>{}
種と共に冬を越え、鳥と共に春をうたおう
//}

//sampleoutputbegin[表示結果]

//noindent
土に根をおろし、風と共に生きよう@<br>{}
種と共に冬を越え、鳥と共に春をうたおう

//sampleoutputend




=== 強制空行

強制的に空行を入れるには、「@<code>|@@<nop>{}<br>{}|」を連続してもいいですが、専用の命令「@<code>{//blankline}」を使うほうがいいでしょう。

//list[][サンプル]{
/@<nop>$$/noindent
土に根をおろし、風と共に生きよう

@<b>|//blankline|
/@<nop>$$/noindent
種と共に冬を越え、鳥と共に春をうたおう
//}

//sampleoutputbegin[表示結果]

//noindent
土に根をおろし、風と共に生きよう

//blankline
//noindent
種と共に冬を越え、鳥と共に春をうたおう

//sampleoutputend





=={sec-heading} 見出し


=== 見出しレベル

章(Chapter)や節(Section)といった見出しは、「@<code>{= }」や「@<code>{== }」で始めます。

//list[][サンプル]{
@<b>|=| 章(Chapter)見出し

@<b>|==| 節(Section)見出し

@<b>|===| 項(Subsection)見出し

@<b>|====| 目(Subsubsection)見出し

@<b>|=====| 段(Paragraph)見出し

@<b>|======| 小段(Subparagraph)見出し
//}



このうち、章・節・項・目はこの順番で（入れ子にして）使うことが想定されています。
たとえば、章(Chapter)の次に節ではなく項(Subsection)が登場するのはよくありません。

ただし段と小段はそのような制約はなく、たとえば目(Subsubsection)を飛ばして節や項の中で使って構いません。

//list[][サンプル]{
@<nop>$$= 章(Chapter)

@<nop>$$== 節(Section)

@<b>|===== 段(Paragraph)|   @<balloon>|節の中に段が登場しても構わない|
//}



Starterでは、章は1ファイルにつき1つだけにしてください。
1つのファイルに複数の章を入れないでください。

//list[][サンプル]{
@<nop>$$= 章1

@<nop>$$== 節

@<b>|= 章2|         @<balloon>|（エラーにならないけど）これはダメ|
//}




=== 見出し用オプション

見出しには次のようなオプションが指定できます。

//list[][サンプル]{
==@<b>|[nonum]| 章番号や節番号をつけない（目次には表示する）
==@<b>|[nodisp]| 見出しを表示しない（目次には表示する）
==@<b>|[notoc]| 章番号や節番号をつけず、目次にも表示しない
//}



一般的には、「まえがき」や「あとがき」には章番号をつけません。
そのため、これらのオプションは「まえがき」や「あとがき」で使うとよさそうに見えます。

しかしこのようなオプションをつけなくても、「まえがき」や「あとがき」の章や節には番号がつきません。
そのため、これらのオプションを使う機会は、実はほとんどありません。


=== 章の概要

章タイトルの直後に、章の概要を書くことをお勧めします。

//list[][サンプル]{
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




#@+++
=== 章タイトルページ

章ごとのタイトルページを作れます。

 * 章の概要を書く（必須）。
 * そのあとに「@<code>|//makechaptitlepage[toc=section]|」と書く。
 * これを全部の章で行う（ただし「まえがき」と「あとがき」を除く）。

//list[][サンプル]{
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

章IDは、章そのものを参照する場合や、ある章から別の章の節(Section)や図やテーブルを参照するときに使います。
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

//list[][サンプル]{
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

//list[][サンプル]{
==@<b>|{sec-heading}| 見出し
===@<b>|{subsec-headingref}| 節や項を参照する
//}



そして「@<code>|@@<nop>{}<hd>{ラベル}|」を使ってそれらを参照します。

//list[][サンプル]{
@<b>|@@<nop>$$<hd>{|sec-heading@<b>|}|

@<b>|@@<nop>$$<hd>{|subsec-headingref@<b>|}|
//}

//sampleoutputbegin[表示結果]

@<hd>{sec-heading}

@<hd>{subsec-headingref}

//sampleoutputend



またStarter拡張である「@<code>|@@<nop>{}<secref>{ラベル}|」を使うと、ページ番号も表示されます。
コマンド名は「@<code>|@@<nop>{}<secref>|」ですが、節(Section)だけでなく項(Subsection)や目(Subsubsection)にも使えます。

//list[][サンプル]{
@<b>|@@<nop>$$<secref>{|sec-heading@<b>|}|

@<b>|@@<nop>$$<secref>{|subsec-headingref@<b>|}|
//}

//sampleoutputbegin[表示結果]

@<secref>{sec-heading}

@<secref>{subsec-headingref}

//sampleoutputend



他の章の節や項（つまり他の原稿ファイルの節や項）を参照するには、ラベルの前に章IDをつけます。

//list[][サンプル]{
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
「@@<nop>{}<secref>{}」を使うとたとえば『3.1「見出し」の「見出し用オプション」』となるので多少ましですが、探しやすいとは言えません。

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

//list[][サンプル]{
テキストテキストテキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキストテキストテキスト

@<b>|===== 段見出し1|
テキストテキストテキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキストテキストテキスト

テキストテキストテキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキストテキストテキスト

@<b>|===== 段見出し2|
テキストテキストテキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキストテキストテキスト

テキストテキストテキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキストテキストテキスト
//}

//sampleoutputbegin[表示結果]

テキストテキストテキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキストテキストテキスト

===== 段見出し1
テキストテキストテキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキストテキストテキスト

テキストテキストテキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキストテキストテキスト

===== 段見出し2
テキストテキストテキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキストテキストテキスト

テキストテキストテキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキストテキストテキスト

//sampleoutputend



これを見ると分かるように、段見出しの前に少しスペースが入ります。
しかし終わりにはそのようなスペースが入りません。
終わりにもスペースを入れるには、次のように「@<code>|//paragraphend|」を使ってください。

//list[][サンプル]{
テキストテキストテキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキストテキストテキスト

@<nop>$$===== 段見出し
テキストテキストテキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキストテキストテキスト
@<b>|//paragraphend|

テキストテキストテキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキストテキストテキスト
//}

//sampleoutputbegin[表示結果]

テキストテキストテキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキストテキストテキスト

===== 段見出し
テキストテキストテキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキストテキストテキスト
//paragraphend

テキストテキストテキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキストテキストテキスト

//sampleoutputend



また、小段(Subparagraph)見出しは次のように表示されます。

//list[][サンプル]{
テキストテキストテキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキストテキストテキスト

@<b>|====== 小段見出し1|
テキストテキストテキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキストテキストテキスト

テキストテキストテキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキストテキストテキスト

@<b>|====== 小段見出し2|
テキストテキストテキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキストテキストテキスト

テキストテキストテキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキストテキストテキスト
//}

//sampleoutputbegin[表示結果]

テキストテキストテキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキストテキストテキスト

====== 小段見出し1
テキストテキストテキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキストテキストテキスト

テキストテキストテキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキストテキストテキスト

====== 小段見出し2
テキストテキストテキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキストテキストテキスト

テキストテキストテキストテキストテキストテキストテキストテキスト
テキストテキストテキストテキストテキストテキストテキストテキスト

//sampleoutputend



これを見ると分かるように、小段見出しではスペースは入りません。
「@<code>|//subparagraph|」は用意されていますが、スペースは入りません。


=={sec-list} 箇条書き

=== 番号なし箇条書き

番号なし箇条書きは「@<code>{ * }」で始めます。
先頭に半角空白が入っていることに注意してください。

//list[][サンプル]{
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

//list[][サンプル]{
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

//list[][サンプル]{
 @<b>|1.| 番号つき箇条書き（数字しか指定できない）
 @<b>|2.| 番号つき箇条書き（入れ子にできない）
//}

//sampleoutputbegin[表示結果]

 1. 番号つき箇条書き（数字しか指定できない）
 2. 番号つき箇条書き（入れ子にできない）

//sampleoutputend



2つ目はStarterによる拡張で、「@<code>{ - 1. }」のように始める書き方です。
この書き方は「@<code>{ - A. }」や「@<code>{ - (1) }」など任意の文字列が使え、また「@<code>{-}」を連続することで入れ子にもできます。

//list[][サンプル]{
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


=={sec-termlist} 用語リスト

HTMLでいうところの「@<code>{<dl><dt><dd>}」は、「@<code>{ : }」で始めて、次の行からインデントします@<fn>{diwmv}。
先頭の半角空白は入れるようにしましょう@<fn>{axm3t}。
//footnote[diwmv][説明文のインデントは、半角空白でもタブ文字でもいいです。]
//footnote[axm3t][過去との互換性のため、先頭の半角空白がなくても動作しますが、箇条書きとの整合性のために半角空白を入れたほうがいいでしょう。]

//list[][サンプル]{
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



なお説明文の中に箇条書きやプログラムコードを入れることはできません。


=={sec-command} インライン命令とブロック命令

ここで少し話を変えて、命令の正式について説明します。

Re:VIEWおよびStarterでのコマンドは、大きく3つの形式に分けられます。

 * インライン命令（例：「@<code>|@@<nop>{}<B>{...}|」）
 * ブロック命令（例：「@<code>|//list{...//}|」）
 * 特殊な形式の命令（例：箇条書きの「@<code>|*|」や見出しの「@<code>|=|」など）

ここではインライン命令とブロック命令について、それぞれ説明します。


==={subsec-inlinecmd} インライン命令

「インライン命令」とは、「@<code>|@@<nop>{}<B>{...}|」のような形式の命令のことです。
主に文章中に埋め込むために使います。

Re:VIEWのインライン命令は入れ子にできませんが、Starterでは入れ子にできるよう拡張しています。

//list[][サンプル]{
@<b>|@@<nop>$$<code>{|func(@<b>|@@<nop>$$<b>{|@<b>|@@<nop>$$<i>{|arg@<b>|}}|)@<b>|}|
//}

//sampleoutputbegin[表示結果]

@<code>{func(@<b>{@<i>{arg}})}

//sampleoutputend



インライン命令は、複数行を対象にできません。
たとえば次のような書き方はできません。

//list[][サンプル]{
@<b>|@@<nop>$$<B>{|テキスト
テキスト@<b>|}|
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

//list[][サンプル]{
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
 * @<LaTeX>やHTMLの生テキストを埋め込む「@<code>|//embed|」

ブロック命令の引数は、たとえば「@<code>|//list[ラベル][説明文]{...//}|」のように書きます。
この場合だと、第1引数が「@<code>{ラベル}」で第2引数が「@<code>{説明文}」です。
引数の中に「@<code>|]|」を入れたい場合は、「@<code>|\]|」のようにエスケープしてください。



=={sec-decoration} 強調と装飾


=== 強調

文章の一部を強調するには「@<code>|@@<nop>{}<B>{...}|」または「@<code>|@@<nop>{}<strong>{...}|」で囲みます。
囲んだ部分は太字のゴシック体になります。

//list[][サンプル]{
テキスト@<b>|@@<nop>$$<B>{|テキスト@<b>|}|テキスト
//}

//sampleoutputbegin[表示結果]

テキスト@<B>{テキスト}テキスト

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
テキスト@<B>|}|
//}

//}


=== 太字

太字にするだけなら「@<code>|@@<nop>{}<b>{...}|」で囲みます。
強調と違い、ゴシック体になりません。

//list[][サンプル]{
テキスト@<b>|@@<nop>$$<b>{|テキスト@<b>|}|テキスト
//}

//sampleoutputbegin[表示結果]

テキスト@<b>{テキスト}テキスト

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



=={sec-program} プログラムリスト

=== 基本的な書き方

プログラムリストは「@<code>|//list{ ... //}|」で囲み、第2引数に説明書きを指定します。

//list[][サンプル]{
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

//list[][サンプル]{
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

//list[][サンプル]{
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

//list[][サンプル]{
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

//list[][サンプル]{
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



ただし折り返し箇所が日本語だと、折り返しはされるものの、折返し記号がつきません@<fn>{fn-zekaz}。
あまりいい対策ではありませんが、折り返したい箇所に「@<code>|@@<nop>{}<foldhere>{}|」を書くと折り返しされつつ折返し記号もつきます。

//footnote[fn-zekaz][原因と対策が分かる人いたらぜひ教えてください。]

折り返しをしたくないときは、「@<code>|//list[][][@<b>{fold=off}]|」と指定します。

//list[][サンプル]{
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

//list[][サンプル]{
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

//list[][サンプル]{
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




==={subsec-indentwidth} インデント

第3引数にたとえば「@<code>|[indentwidth=4]|」のような指定をすると、4文字幅でのインデントを表す縦線がうっすらとつきます。

//list[][サンプル]{
/@<nop>$$/list[][]@<b>|[indentwidth=4]|{
class Fib:

    def __call__(n):
        if n <= 1:
            return n
        else:
            return fib(n-1) + fib(n-2)
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//list[][][indentwidth=4]{
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


=== 外部ファイルの読み込み

プログラムコードを外部ファイルから読み込むには次のようにします@<fn>{fn-yph1o}。

//footnote[fn-yph1o][参考：@<href>{https://github.com/kmuto/review/issues/887}]

//list[][別ファイルのソースコード (source/fib3.rb) を読み込む方法]{
@<nop>{}//list[fib3][フィボナッチ数列]{
@<b>|@@<nop>{}<include>{source/fib3.rb}|
@<nop>{}//}
//}

脚注のリンク先にあるように、この方法はRe:VIEWでは undocumented です。
Starterでは正式な機能としてサポートします。


=== タブ文字

プログラムコードの中にタブ文字があると、8文字幅のカラムに合うよう自動的に半角空白に展開されます。

しかし「@<code>|@@<nop>{}<b>{...}|」のようなインライン命令があると、カラム幅の計算が狂うため、意図したようには表示されないことがあります。

そのため、プログラムコードにはなるべくタブ文字を含めないほうがいいでしょう。


=== その他のオプション

「@<code>|//list|」の第3引数には、次のようなオプションも指定できます。

#@# : @<code>$fold={on|off}$
#@#	長い行を自動で折り返します。
#@#	デフォルトは「@<code>|on|」。
#@# : @<code>$foldmark={on|off}$
#@#	折り返したことを表す、小さな記号をつけます。
#@#	デフォルトは「@<code>|on|」。
#@# : @<code>$eolmark={on|off}$
#@#	すべての行末に、行末であることを表す小さな記号をつけます。
#@#	「@<code>|foldmark=on|」 のかわりに使うことを想定していますが、両方を@<code>|on|。にしても使えます。
#@#	デフォルトは「@<code>|off|」。
 : @<code>$fontsize={small|x-small|xx-small|large|x-large|xx-large}$
	文字の大きさを小さく（または大きく）します。
	どうしてもプログラムコードを折返ししたくないときに使うといいでしょう。
 : @<code>$lineno={on|off|@<i>{integer}}$
	行番号をつけます。詳細は次の節で説明します。
 : @<code>$linenowidth={0|@<i>{integer}}$
	行番号の幅を指定します。詳細は次の節で説明します。
 : @<code>$lang=@<i>{langname}$
	プログラム言語の名前を指定します。
	コードハイライトのために使いますが、Re:VIEW Starterではまだ対応していません。



=={sec-lineno} 行番号


=== プログラムリストに行番号をつける

プログラムリストに行番号をつけるには、「@<code>|//list|」ブロック命令の第3引数を次のように指定します。

//list[][サンプル]{
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

//list[][サンプル]{
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



=== 行番号の幅を指定する

前の例では行番号が外側に表示されました。
行番号の幅を指定すると、行番号が内側に表示されます。

//list[][サンプル]{
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



また幅を@<code>{0}に指定すると、行番号の幅を自動的に計算します。

//list[][サンプル]{
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

//list[][サンプル]{
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

ターミナル（端末）の画面を表すには、「@<code>|//terminal{ ... //}|」というブロック命令を使います。

//list[][サンプル]{
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

「@<code>|@@<nop>{}<userinput>{}|」を使うと、ユーザによる入力箇所を示せます@<fn>{fn-pl9ll}。

//list[][サンプル]{
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

過去との互換性のために、「@<code>|//cmd{ ... //}|」というブロック命令もあります。
しかしこの命令はリスト番号や行番号がつけられないし、「@<code>|//list|」命令と使い方が違うので、もはや使う必要はありません。

//list[][サンプル]{
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





=={sec-footnote} 脚注

脚注は、脚注をつけたい箇所に「@<code>|@@<nop>{}<fn>{ラベル}|」を埋め込み、脚注の文は「@<code>|//footnote[ラベル][脚注文]|」のように書きます。

//list[][サンプル]{
本文。本文@<b>|@@<nop>$$<fn>{fn-123}|。本文。

@<b>|//footnote[fn-123][脚注文。脚注文。]|
//}

//sampleoutputbegin[表示結果]

本文。本文@<fn>{fn-123}。本文。

//footnote[fn-123][脚注文。脚注文。]

//sampleoutputend



このページの最下部に脚注が表示されていることを確認してください。

また脚注文に「@<code>|]|」を埋め込む場合は、「@<code>|\]|」のようにエスケープしてください。



=={sec-note} ノート

補足情報や注意事項などを表示する枠を、Starterでは「ノート」と呼びます。


=== ノートの書き方

ノートは、「@<code>|//note{ ... //}|」というブロック命令で表します。

//list[][サンプル]{
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

//list[][サンプル]{
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




=== ラベルをつけて参照する

ノートにラベルをつけて、「@<code>|@@<nop>{}<noteref>{ラベル名}|」で参照できます（Starter独自拡張）。

//list[][サンプル]{
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

//tsize[|latex||l|c|c|]
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
 * 「@<code>|//important|」（重要）
 * 「@<code>|//caution|」（警告）
 * 「@<code>|//notice|」（注意）

これらをRe:VIEWで使うとひどいデザインで表示されますが、Starterでは簡素なデザインで表示するよう修正しています（デザインは同一です）。

//list[][サンプル]{
/@<nop>$$/warning[破滅の呪文]{
破滅の呪文を唱えると、本建物は自動的に瓦解します。
ご使用には十分注意してください。
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//warning[破滅の呪文]{
破滅の呪文を唱えると、本建物は自動的に瓦解します。
ご使用には十分注意してください。
//}

//sampleoutputend



このデザインを変更するには、@<secref>{04-customize|subec-miniblockdesign}

なお「@<code>|//note|」と違い、参照用のラベルはつけられません。
また@<LaTeX>{}の制限により、これらのブロックの内部では脚注がうまく表示されないことがあります。



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

ただし明確な違いはないので、ノートをコラム代わりに使っても、あるいはその逆でも間違いではないです。

=== コラムの書き方

コラムは「@<code>|==[column]|」と「@<code>|==[/column]|」か、または「@<code>|===[column]|」と「@<code>|===[/column]|」で囲みます（イコール記号の数が違うことに注意）。
また実装上の都合により、コラムを閉じる直前に空行を入れてください。

//list[][サンプル]{
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



=== コラム内の脚注

前の例を見れば分かるように、コラムの中には箇条書きやプログラムリストなどを含めることができます。
ただし、脚注だけはコラムを閉じたあとに書く必要があります。

//list[][サンプル]{
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

//list[][サンプル]{
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

コラム内で「@<code>|//list|」や「@<code>|//terminal|」を使うと、それらはページをまたいでくれません@<fn>{fn-giruq}。

現在のところ、これは仕様です。あきらめてください。

//footnote[fn-giruq][これは@<LaTeX>{}のframed環境による制限です。解決するにはframed環境を使わないよう変更する必要があります。]


=== ノートとコラムの使い分け

ノートとコラムは、次のように使い分けるといいでしょう。

 * 基本的には、ノートを使う。
 * 章(Chapter)の終わりに、長めの関連情報やエッセーを書く場合はコラムを使う。
   これは節(Section)と同じ扱いにするので、「@<code>|==[column]|」を使う。

//note[コラムは見出しの一種]{
Re:VIEWおよびStarterでは、コラムは節(Section)や項(Subsection)といった見出しの一種として実装されています。
そのため、「@<code>|==[column]|」なら節(Section)と同じような扱いになり、「@<code>|===[column]|」なら項(Subsection)と同じような扱いになります（目次レベルを見るとよく分かります）。

また節や項は閉じる必要がない（勝手に閉じてくれる）のと同じように、コラムも「@<code>|===[/column]|」がなければ勝手に閉じてくれます。
しかし明示的に閉じないと脚注が出力されない場合があるので、横着をせずに明示的にコラムを閉じましょう。
//}



=={sec-image} 画像


=== 画像ファイルの読み込み方

画像を読み込むには、「@<code>|//image[画像ファイル名][説明文字列][scale=1.0]|」を使います。

 * 画像ファイルは「@<file>{images/}」フォルダに置きます@<fn>{fn-6s711}。
 * 画像ファイル名には拡張子を指定しません（自動的に検出されます）。
 * 画像ファイル名がラベルを兼ねており、「@<code>|@@<nop>{}<img>{画像ファイル名}|」で参照できます。
 * 第3引数には画像の表示幅を、本文幅に対する割合で指定します。
   たとえば「@<code>|[scale=1.0]|」なら本文幅いっぱい、「@<code>|[scale=0.5]|」なら本文幅の半分になります。

//footnote[fn-6s711][画像ファイルを置くフォルダは、設定ファイル「@<file>{config.yml}」の設定項目「@<file>{imagedir}」で変更できますが、通常は変更する必要はないでしょう。]

次の例では、画像ファイル「@<file>{images/tw-icon1.jpg}」を読み込んでいます。

//list[][サンプル]{
/@<nop>$$/image[tw-icon1][Twitterアイコン][scale=0.3]
//}



表示例は@<img>{tw-icon1}を見てください。

//image[tw-icon1][Twitterアイコン][scale=0.3]

//note[1つの画像ファイルを複数の箇所から読み込まない]{
画像ファイル名がラベルを兼ねるせいで、1つの画像ファイルを複数の箇所から読み込むとラベルが重複してしまい、コンパイル時に警告が出ます。
また「@<code>|@@<nop>{}<img>{}|」で参照しても、画像番号がずれてしまい正しく参照できません。

Re:VIEWおよびStarterでは1つの画像ファイルを複数の箇所から読み込むのは止めておきましょう。
かわりにファイルをコピーしてファイル名を変えましょう@<fn>{fn-9d4pq}。
//footnote[fn-9d4pq][（分かる人向け）もちろんシンボリックリンクやハードリンクでもいいです。]
//}


=== 章ごとの画像フォルダ

画像ファイルは、章(Chapter)ごとのフォルダに置けます。
たとえば原稿ファイル名が「@<file>{02-tutorial.re}」であれば、章IDは「@<file>{02-tutorial}」になり、画像ファイルを「@<file>{images/02-tutorial/}」に置けます@<fn>{fn-31qgg}（特別な設定は不要です）。
これは複数の著者で一冊の本を執筆するときに便利です。
//footnote[fn-31qgg][もちろん「@<file>{images/}」にも置けます。]

詳しくは@<href>{https://github.com/kmuto/review/blob/master/doc/format.ja.md#%E7%94%BB%E5%83%8F%E3%83%95%E3%82%A1%E3%82%A4%E3%83%AB%E3%81%AE%E6%8E%A2%E7%B4%A2, Re:VIEWのマニュアル}を参照してください。


=== 画像のまわりに線をつける

第3引数に「@<code>|[border=on]|」をつけると、画像のまわりに灰色の線がつきます（Starter拡張）。

//list[][サンプル]{
/@<nop>$$/image[tw-icon2][Twitterアイコン][scale=0.3@<b>|,border=on|]
//}



表示結果は@<img>{tw-icon2}を見てください。

//image[tw-icon2][Twitterアイコン][scale=0.3,border=on]


=== 画像の配置位置を指定する

第3引数に「@<code>|[pos=...]|」をつけると、読み込んだ画像をページのどこに配置するか、指定できます。

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

//list[][サンプル]{
現在位置に配置
/@<nop>$$/image[tw-icon][Twitterアイコン][scale=0.3@<b>|,pos=h|]

ページ先頭に配置
/@<nop>$$/image[tw-icon][Twitterアイコン][scale=0.3@<b>|,pos=t|]

ページ最下部に配置
/@<nop>$$/image[tw-icon][Twitterアイコン][scale=0.3@<b>|,pos=b|]
//}



「@<code>|pos=H|」と「@<code>|pos=h|」の違いは、@<img>{figure_heretop}を見ればよく分かるでしょう。

//image[figure_heretop][「@<code>{pos=H}」（上）と「@<code>{pos=h}」（下）の違い][scale=0.8]


=== 画像に番号も説明もつけない

今まで説明したやり方では、画像に番号と説明文字列がつきました。
これらをつけず、単に画像ファイルを読み込みたいだけの場合は、「@<code>|//indepimage[ファイル名][][scale=1.0]|」を使ってください（第2引数に説明文字列を指定できますが、通常は不要でしょう）。

//list[][サンプル]{
@<b>|//indepimage|[tw-icon3][][scale=0.3]
//}

//sampleoutputbegin[表示結果]

//indepimage[tw-icon3][][scale=0.3]

//sampleoutputend




=== 文章の途中に画像を読み込む

文章の途中に画像を読み込むには、「@<code>|@@<nop>{}<icon>{画像ファイル名}|」を使います。
画像の表示幅は指定できないようです。

//list[][サンプル]{
文章の途中でファビコン画像「@<b>|@@<nop>$$<icon>{|favicon-16x16@<b>|}|」を読み込む。
//}

//sampleoutputbegin[表示結果]

文章の途中でファビコン画像「@<icon>{favicon-16x16}」を読み込む。

//sampleoutputend




=== 画像とテキストを並べて表示する

Starterでは、画像とテキストを並べて表示するためのコマンド「@<code>|//sideimage|」を用意しました。
著者紹介においてTwitterアイコンとともに使うといいでしょう。

//list[][サンプル]{
@<b>|//sideimage[tw-icon4][20mm][side=L,sep=7mm,border=on]|{
/@<nop>$$/noindent
@@<nop>$$<B>{カウプラン機関極東支部}

 * @_kauplan (@@<nop>$$<href>{https://twitter.com/_kauplan/})
 * @@<nop>$$<href>{https://kauplan.org/}
 * 技術書典8新刊「Pythonの黒魔術」出ました！

/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//sideimage[tw-icon4][20mm][side=L,sep=7mm,border=on]{
//noindent
@<B>{カウプラン機関極東支部}

 * @_kauplan (@<href>{https://twitter.com/_kauplan/})
 * @<href>{https://kauplan.org/}
 * 技術書典8新刊「Pythonの黒魔術」出ました！

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

//list[][サンプル]{
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


=== 右寄せ、左寄せ、中央揃え

セルの右寄せ(r)・左寄せ(l)・中央揃え(c)を指定するには、「@<code>{//tsize[|latex|...]}」@<fn>{fn-8rpih}を使います。
ただし現在のところ、この機能はPDF用でありePubでは使えません。

//footnote[fn-8rpih][「@<code>{//tsize[|pdf|...\]}」ではなく「@<code>{//tsize[|latex|...\]}」なのは、内部で@<LaTeX>{}という組版用ソフトウェアを使っているからです。]

//list[][サンプル]{
@<b>{//tsize[|latex||l|r|l|c|]}
/@<nop>$$/table[tbl-sample2][右寄せ(r)、左寄せ(l)、中央揃え(c)]{
Name	Val	Val	Val
--------------------------------
AAA	10	10	10
BBB	100	100	100
CCC	1000	1000	1000
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//tsize[|latex||l|r|l|c|]
//table[tbl-sample2][右寄せ(r)、左寄せ(l)、中央揃え(c)]{
Name	Val	Val	Val
--------------------------------
AAA	10	10	10
BBB	100	100	100
CCC	1000	1000	1000
//}

//sampleoutputend



#@#表示結果は@<table>{tbl-sample2}を見てください。


=== 罫線

「@<code>{//tsize[|latex||l|r|l|c|]}」の指定において、「@<code>{|l|r|l|c|}」の部分における「@<code>{|}」は、縦方向の罫線を表します。
これをなくすと罫線がつきません。
また「@<code>{||}」のように二重にすると、罫線も二重になります。

//list[][サンプル]{
/@<nop>$$/tsize[|latex|@<b>{l||rlc}]
/@<nop>$$/table[tbl-sample3][罫線をなくしたり、二重にしてみたり]{
Name	Val	Val	Val
--------------------------------
AAA	10	10	10
BBB	100	100	100
CCC	1000	1000	1000
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//tsize[|latex|l||rlc]
//table[tbl-sample3][罫線をなくしたり、二重にしてみたり]{
Name	Val	Val	Val
--------------------------------
AAA	10	10	10
BBB	100	100	100
CCC	1000	1000	1000
//}

//sampleoutputend



#@#表示結果は@<table>{tbl-sample3}を見てください。


=== セル幅

セルの幅を指定するには、「@<code>{//tsize[|latex|...]}」の中でたとえば「@<code>{p{20mm}}」のように指定します。

 * この場合、自動的に左寄せになります。右寄せや中央揃えにはできません。
 * セル内の長いテキストは自動的に折り返されます。
   テーブルが横にはみ出てしまう場合はセル幅を指定するといいでしょう。

//list[][サンプル]{
/@<nop>$$/tsize[|latex||l|@<b>|p{70mm}||]
/@<nop>$$/table[tbl-sample4][セルの幅を指定すると、長いテキストが折り返される]{
Name	Description
--------------------------------
AAA	text text text text text text text text text text text text text text text
BBB	text text text text text text text text text text text text text text text
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//tsize[|latex||l|p{70mm}|]
//table[tbl-sample4][セルの幅を指定すると、長いテキストが折り返される]{
Name	Description
--------------------------------
AAA	text text text text text text text text text text text text text text text
BBB	text text text text text text text text text text text text text text text
//}

//sampleoutputend



#@#表示結果は@<table>{tbl-sample4}を見てください。


=== 空欄

セルを空欄にするには、セルに「@<code>{.}」だけを書いてください。

//list[][サンプル]{
/@<nop>$$/tsize[|latex||l|ccc|]
/@<nop>$$/table[tbl-sample5][セルを空欄にするサンプル]{
評価項目		製品A	製品B	製品C
----------------------------------------
機能が充分か		✓	✓	.
価格が適切か		.	.	✓
サポートがあるか	✓	.	✓
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//tsize[|latex||l|ccc|]
//table[tbl-sample5][セルを空欄にするサンプル]{
評価項目		製品A	製品B	製品C
----------------------------------------
機能が充分か		✓	✓	.
価格が適切か		.	.	✓
サポートがあるか	✓	.	✓
//}

//sampleoutputend



またセルの先頭が「@<code>{.}」で始まる場合は、「@<code>{..}」のように2つ書いてください。
そうしないと先頭の「@<code>{.}」が消えてしまいます。

//list[][サンプル]{
/@<nop>$$/table[tbl-sample6][セルの先頭が「@@<nop>$$<code>{.}」で始まる場合]{
先頭に「.」が1つだけの場合	@<b>|.bashrc|
先頭に「.」が2つある場合	@<b>|..bashrc|
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//table[tbl-sample6][セルの先頭が「@<code>{.}」で始まる場合]{
先頭に「.」が1つだけの場合	.bashrc
先頭に「.」が2つある場合	..bashrc
//}

//sampleoutputend





=={sec-mathexpr} 数式


=== 数式の書き方

数式は「@<code>|//texequation[ラベル][説明文]{ ... //}|」のように書きます。

//list[][サンプル]{
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

//list[][サンプル]{
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

//list[][サンプル]{
 * @<b>|@@<nop>$$<m>$y = f(x) + k$|  ← 使った場合
 * @<b>|y = f(x) + k|        ← 使わなかった場合
//}

//sampleoutputbegin[表示結果]

 * @<m>$y = f(x) + k$  ← 使った場合
 * y = f(x) + k        ← 使わなかった場合

//sampleoutputend




その他、Re:VIEWにおける数式の詳細は、Re:VIEWの@<href>{https://github.com/kmuto/review/blob/master/doc/format.ja.md#tex-%E5%BC%8F, Wiki}を参照してください。



=={sec-misc} その他


=== URL、リンク

URLは「@<code>|@@<nop>{}<href>{URL}|」と書きます。

//list[][サンプル]{
Re:VIEW Starter：@<b>|@@<nop>$$<href>{|https://kauplan.org/reviewstarter/@<b>|}|
//}

//sampleoutputbegin[表示結果]

Re:VIEW Starter：@<href>{https://kauplan.org/reviewstarter/}

//sampleoutputend



リンクは「@<code>|@@<nop>{}<href>{URL, テキスト}|」と書きます。

//list[][サンプル]{
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

//list[][サンプル]{
 * @<b>|@@<nop>$$<href>|{https://twitter.com/_kauplan/, @_kauplan}
 * @<b>|@@<nop>$$<hlink>|{https://twitter.com/_kauplan/, @_kauplan}
//}

//sampleoutputbegin[表示結果]

 * @<href>{https://twitter.com/_kauplan/, @_kauplan}
 * @<hlink>{https://twitter.com/_kauplan/, @_kauplan}

//sampleoutputend




=== 引用

引用は「@<code>|//quote{ ... //}|」で表します。

//list[][サンプル]{
@<b>|//quote{|
/@<nop>$$/noindent
その者、蒼き衣を纏いて金色の野に降り立つべし。@@<nop>$$<br>{}
失われた大地との絆を結び、ついに人々を清浄の地に導かん。
@<b>|//}|
//}

//sampleoutputbegin[表示結果]

//quote{
//noindent
その者、蒼き衣を纏いて金色の野に降り立つべし。@<br>{}
失われた大地との絆を結び、ついに人々を清浄の地に導かん。
//}

//sampleoutputend




=== 傍点

傍点は「@<code>|@@<nop>{}<bou>{...}|」でつけられます。

//list[][サンプル]{
@<b>|@@<nop>$$<bou>{|三分間@<b>|}|、待ってやる。
//}

//sampleoutputbegin[表示結果]

@<bou>{三分間}、待ってやる。

//sampleoutputend



傍点は、太字で強調するほどではないけど読者の注意を向けたいときに使います。
ただしアルファベットや記号ではあまりよいデザインにはなりません。


=== ルビ、読みがな

ルビ（あるいは読みがな）は「@<code>|@@<nop>{}<ruby>{テキスト, ルビ}|」のように書きます。

//list[][サンプル]{
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

//list[][サンプル]{
強調される： @@<nop>$$<b>{テキスト}

強調されない： @@<b>|@@<nop>$$<nop>{}|<b>{テキスト}
//}

//sampleoutputbegin[表示結果]

強調される： @<b>{テキスト}

強調されない： @@<nop>{}<b>{テキスト}

//sampleoutputend



またブロック命令の行頭に「@<code>|@@<nop>{}<nop>{}|」を入れると、ブロック命令として解釈されなくなります。


=== コード中コメント

プログラムコードやターミナルにおいて、コメントを記述するための「@<code>|@@<nop>{}<balloon>{...}|」というコマンドが用意されています。

//needvspace[latex][5zw]
//list[][サンプル]{
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


=== 改ページ

「@<code>|//clearpage|」で強制的に改ページできます。


=== 特殊文字

 * 「@<code>|@@<nop>{}<hearts>{}|」で「@<hearts>{}」が表示できます。
 * 「@<code>|@@<nop>{}<TeX>{}|」で「@<TeX>{}」が表示できます。
 * 「@<code>|@@<nop>{}<LaTeX>{}|」で「@<LaTeX>{}」が表示できます。


=== ターミナルのカーソル

「@<code>|@@<nop>{}<cursor>{...}|」を使うと、ターミナルでのカーソルを表せます。

次の例では、2行目の真ん中の「f」にカーソルがあることを表しています。

//list[][サンプル]{
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




=== 右寄せ、センタリング

右寄せとセンタリングのブロック命令があります。

//list[][サンプル]{
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




=== 生データ

@<LaTeX>{}のコード（PDFのとき）やHTMLのコード（ePubのとき）を埋め込む機能があります。
たとえば次の例では、PDFのときは「@<code>|//embed[latex]{...//}|」のコードが使われ、HTMLやePubのときだけ「@<code>|//embed[html]{...//}|」のコードが使われます。

//list[][サンプル]{
@<b>|//embed[latex]{|
\textcolor{red}{Red}
\textcolor{green}{Green}
\textcolor{blue}{Blue}
\par
@<b>|//}|

@<b>|//embed[html]{|
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

//embed[html]{
<div>
  <span style="color:red">Red</span>
  <span style="color:green">Green</span>
  <span style="color:blue">Blue</span>
</div>
//}

//sampleoutputend




=== 索引

（未執筆。Re:VIEWの@<href>{https://github.com/kmuto/review/blob/master/doc/makeindex.ja.md, Wiki}を参照してください。）


=== 参考文献

（未執筆。Re:VIEWの@<href>{https://github.com/kmuto/review/blob/master/doc/format.ja.md#%E5%8F%82%E8%80%83%E6%96%87%E7%8C%AE%E3%81%AE%E5%AE%9A%E7%BE%A9, Wiki}を参照してください。）


=== 単語展開

（未執筆。Re:VIEWの@<href>{https://github.com/kmuto/review/blob/master/doc/format.ja.md#%E5%8D%98%E8%AA%9E%E3%83%95%E3%82%A1%E3%82%A4%E3%83%AB%E3%81%AE%E5%B1%95%E9%96%8B, Wiki}を参照してください。）
