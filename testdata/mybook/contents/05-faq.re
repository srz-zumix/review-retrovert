= FAQ

//abstract{
よくある質問とその回答(Frequentry Asked Question, FAQ)を紹介します。
//}

#@#//makechaptitlepage[toc=on]


=={sec-compileerror} コンパイルエラー


=== コンパイルエラーが出たとき

PDFファイル生成時のコンパイルエラーについて、対処方法を説明します。

PDFへのコンパイルは、内部では大きく3つのステージに分かれます。

 - (1) 設定ファイルを読み込む（@<file>{config.yml}、@<file>{config-starter.yml}、@<file>{catalog.yml}）
 - (2) 原稿ファイル(@<file>{*.re})を@<LaTeX>{}ファイルへ変換する
 - (3) @<LaTeX>{}ファイルからPDFファイルを生成する

(1)のステージでは、設定ファイルの書き方に間違いがあるとエラーが発生します。
たとえば次のような点に注意してください。

 * タブ文字を使ってないか（使っているとエラー）
 * インデントが揃っているか（揃ってないとエラー）
 * 必要な空白が抜けてないか（「@<code>{-}」や「@<code>{:}」の直後）

(2)のステージでは、インライン命令やブロック命令の書き方に間違いがあるとエラーが発生します。
たとえば次のような点に注意してください。

 * インライン命令がきちんと閉じているか
 * ブロック命令の引数が足りているか、多すぎないか
 * 「@<code>|//}|」が足りてないか、または多すぎないか
 * 「@<code>|@@<nop>{}<fn>{}|」や「@<code>|@@<nop>{}<img>{}|」や「@<code>|@@<nop>{}<table>{}|」のラベルが合っているか
 * 「@<code>|@@<nop>{}<chapref>{}|」で指定した章IDが合っているか
 * 「@<code>|@@<nop>{}<secref>{}|」で指定した節や項が存在するか
 * 脚注の中で「@<code>{]}」を「@<code>{\]}」とエスケープしているか
 * 「@<code>|//image|」で指定した画像ファイルが存在するか
 * 原稿ファイル名を間違っていないか
 * 原稿ファイルの文字コードがUTF-8になっているか

このエラーの場合はエラーメッセージが出るので、それを@<bou>{注意深く読めば}解決の糸口が掴めます。

(3)のステージでのエラーはあまり発生しないものの、原因がとても分かりにくく、@<LaTeX>{}に慣れている人でないと解決は難しいです。
ときどきキャッシュファイル(@<file>{*-pdf/})のせいでおかしくなることがあるので、@<B>{困ったらキャッシュファイルを消して再コンパイル}してみましょう。

//terminal[][困ったらキャッシュファイルを消して再コンパイル]{
$ @<userinput>{rm -rf mybook-pdf} @<balloon>{キャッシュファイルを消す}
$ @<userinput>{rake pdf}          @<balloon>{または rake docker:pdf}
//}

それでもエラーが解決できない場合は、ハッシュタグ「@<em>{#reviewstarter}」をつけてTwitterで聞いてみてください（宛先はなくて構いません）。


=== 「@<code>|review-pdfmaker|」でPDFが生成できない

Starterでは、「@<code>|review-pdfmaker|」や「@<code>|review-epubmaker|」は使えません。
かわりに「@<code>|rake pdf|」や「@<code>|rake epub|」を使ってください。



== 本文


=== 左右の余白が違う

印刷用PDFファイルでは、左右の余白幅を意図的に変えています。
これは印刷時の読みやすさを確保したまま、本文の幅を最大限に広げているからです。
詳しくは@<secref>{06-bestpractice|subsec-sidemargin}を見てください。


=== 文章中のプログラムコードに背景色をつけたい

「@<code>|@@<nop>{}<code>{...}|」による文章中のプログラムコードに、背景色をつけられます。
そのためには、「@<file>{config-starter.yml}」で「@<code>|inlinecode_gray: true|」を設定してください。

//list[][ファイル「@<file>{config-starter.yml}」]{
    inlinecode_gray: true
//}

こうすると、@<file>{sty/starter.sty}において次のような@<LaTeX>{}マクロが有効になります。
背景色を変えたい場合はこのマクロを変更してください。

//list[][ファイル「sty/starter.sty」]{
  \renewcommand{\reviewcode}[1]{%
    \,%                        % ほんの少しスペースを入れる
    \colorbox{shadecolor}{%    % 背景色を薄いグレーに変更
      \texttt{#1}%             % 文字種を等幅フォントに変更
    }%
    \,%                        % ほんの少しスペースを入れる
  }
//}


=== 索引をつけたい

Re:VIEWのWikiページを参照してください。

 * @<href>{https://github.com/kmuto/review/blob/master/doc/makeindex.ja.md}



== プログラムコードとターミナル


=== プログラムコードの見た目が崩れる

おそらく、プログラムコードの中でタブ文字が使われています。
タブ文字を半角空白に置き換えてみてください。

Starterでは、プログラム中のタブ文字は自動的に半角空白に置き換わります。
しかしインライン命令があるとどうしてもカラム幅を正しく計算できないので、意図したようには半角空白に置き換わらず、プログラムの見た目が崩れます。


=== 右端に到達してないのに折り返しされる

Starterではプログラム中の長い行が自動的に右端で折り返されます。
このとき、右端にはまだ文字が入るだけのスペースがありそうなのに折り返しされることがあります（@<img>{codeblock_rpadding1}）。

//image[codeblock_rpadding1][右端にはまだ文字が入るだけのスペースがありそうだが…][scale=0.7]

このような場合、プログラムやターミナルの表示幅をほんの少し広げるだけで、右端まで文字が埋まるようになります。

具体的には、ファイル「@<file>{config-starter.yml}」の中の「@<code>{program_widen: 0.0mm}」や「@<code>{terminal_widen: 0.0mm}」を、たとえば「@<code>{0.3mm}」に設定してください（値は各自で調整してください）。

//list[][ファイル「config-starter.yml」]{
  ## プログラム（//list）の表示幅をほんの少しだけ広げる。
  @<del>{program_widen:   0.0mm}
  @<b>{program_widen:   0.3mm}

  ## ターミナル（//terminal, //cmd）の表示幅をほんの少しだけ広げる。
  @<del>{terminal_widen:  0.0mm}
  @<b>{terminal_widen:  0.3mm}
//}

こうすると、プログラムやターミナルの表示幅が少しだけ広がり、文字が右端まで埋まるようになります（@<img>{codeblock_rpadding2}）。

//image[codeblock_rpadding2][表示幅をほんの少し広げると、右端まで埋まるようになった][scale=0.7]


=== 全角文字の幅を半角文字2個分にしたい

「@<code>|//list|」や「@<code>|//terminal|」の第3引数に「@<code>|widecharfit=on|」を指定すると、全角文字の幅が半角文字2文字分になります。
すべての「@<code>|//list|」や「@<code>|//terminal|」でこのオプションを有効化したい場合は、@<file>{config-starter.yml}の「@<code>|program_default_options:|」や「@<code>|terminal_default_options:|」に、「@<code>|widecharfit: on|」を指定してください。

または英数字の幅が狭いフォントを使うと、半角文字の幅が全角文字の約半分になります（ぴったりにはなりません）。
@<file>{config-starter.yml}で、次のうち必要なほうを設定してください。

//list[][]{
  ## //list用
  program_ttfont: inconsolata-narrow

  ## //terminal用
  terminal_ttfont: inconsolata-narrow
//}


=== ターミナルの出力を折り返しせずに表示したい

ターミナルの出力結果を折り返しせずに表示するには、いくつか方法があります。

===== 小さいフォントで表示する

「@<code>|//terminal|」や「@<code>|//list|」では、小さいフォントで表示するオプションがあります。
フォントサイズは「@<code>|small|」「@<code>|x-small|」「@<code>|xx-small|」の3つが選べます。

//list[][サンプル][]{
/@<nop>$$/terminal[][小さいフォントで表示する][@<b>|fontsize=x-small|]{
                              Table "public.customers"
   Column   |  Type   | Nullable |                Default
------------+---------+----------+---------------------------------------
 id         | integer | not null | nextval('customers_id_seq'::regclass)
 name       | text    | not null |
 created_on | date    | not null | CURRENT_DATE
Indexes:
    "customers_pkey" PRIMARY KEY, btree (id)
    "customers_name_key" UNIQUE CONSTRAINT, btree (name)
/@<nop>$$/}
//}

//sampleoutputbegin[表示結果]

//terminal[][小さいフォントで表示する][fontsize=x-small]{
                              Table "public.customers"
   Column   |  Type   | Nullable |                Default
------------+---------+----------+---------------------------------------
 id         | integer | not null | nextval('customers_id_seq'::regclass)
 name       | text    | not null |
 created_on | date    | not null | CURRENT_DATE
Indexes:
    "customers_pkey" PRIMARY KEY, btree (id)
    "customers_name_key" UNIQUE CONSTRAINT, btree (name)
//}

//sampleoutputend



===== 幅の狭い等幅フォントを使う

Starterでは等幅フォントを複数の中から選べます。
このうち「@<em>{inconsolata-narrow}」は文字の表示幅が狭いので、できるだけ折り返しをさせたくない場合に有効です。

「@<file>{config-starter.yml}」で「@<code>|terminal_ttfont:|」を「@<code>|inconsolata-narrow|」に設定してください。


=== コードハイライトしたい

コードハイライトは、Starterでは未サポートです@<fn>{fn-rkpw8}。
将来的にはサポートする予定ですが、時期は未定です。

//footnote[fn-rkpw8][Re:VIEWではコードハイライトができるそうです。]



== 画像


=== PDFとHTMLとで画像の表示サイズを変えたい

Re:VIEWやStarterでは、PDFとHTMLとで画像の表示サイズを別々に指定できます。
たとえば次のサンプルでは、PDF (@<LaTeX>{})では本文幅いっぱい、HTMLでは本文幅の半分の大きさで画像を表示します。

//list[][サンプル][]{
/@<nop>$$/image[dummy-image][表示幅を変える][@<b>|latex::scale=1.0,html::scale=0.5|]
//}

//sampleoutputbegin[表示結果]

//image[dummy-image][表示幅を変える][latex::scale=1.0,html::scale=0.5]

//sampleoutputend



なお「@<code>|latex::xxx|」や「@<code>|html::xxx|」のような指定方法は、他のオプションやコマンドでも使えます。


=== 印刷用PDFと電子用PDFとで異なる解像度の画像を使いたい

印刷用PDFでは解像度の高い画像を使いたい、けど電子用PDFでは画像の解像度を低くしてデータサイズを小さくしたい、という場合は、「@<file>{images/}」フォルダごと切り替えるのがいいでしょう。
具体的には次のようにします。

//terminal[][高解像度と低解像度の画像を切り替える（macOSまたはLinuxの場合）]{
### 事前準備
$ mkdir images_highres  @<balloon>{解像度の高い画像用のフォルダを作る(印刷用)}
$ mkdir images_lowhres  @<balloon>{解像度の低い画像用のフォルダを作る(電子用)}
$ mv images images.bkup @<balloon>{既存のimagesフォルダを削除するか別名にする}

### 解像度の高い画像に切り替えて印刷用PDFを生成
$ rm -f images                  @<balloon>{シンボリックリンクを消す}
$ ln -s images_highres images   @<balloon>{シンボリックリンクを作る}
$ rake pdf t=pbook              @<balloon>{印刷用PDFを生成する}

### 解像度の低い画像に切り替えて電子用PDFを作成
$ rm -f images                  @<balloon>{シンボリックリンクを消す}
$ ln -s images_lowres images    @<balloon>{シンボリックリンクを作る}
$ rake pdf t=ebook              @<balloon>{電子用PDFを生成する}
//}

切り替え作業が面倒なら、独自のRakeタスクを作成するといいでしょう。
「@<file>{lib/tasks/mytasks.rake}」に次のようなタスクを追加してください。

//list[][@<file>{lib/tasks/mytasks.rake}]{
desc "印刷用PDFを生成"
task :pbook do
  rm_f 'images'
  ln_s 'images_highres', 'images'
  sh "rake pdf t=pbook"
  #sh "rake docker:pdf t=pbook"
end

desc "電子用PDFを生成"
task :ebook do
  rm_f 'images'
  ln_s 'images_rowres', 'images'
  sh "rake pdf t=ebook"
  #sh "rake docker:pdf t=ebook"
end
//}

これにより、「@<code>|rake pbook|」で高解像度の画像を使って印刷用PDFが生成され、また「@<code>|rake ebook|」で低解像度の画像を使って電子用PDFが生成されます。


=== 画像の解像度はどのくらいにすればいいか

画像の「解像度」(Resolution)とは、簡単にいえば画像の「きめ細かさ」です。
解像度が高い（＝きめ細かい）ほど画像のドットやギザギザがなくなり、解像度が低いほど画像のドットやギザギザが目立ちます。

解像度は「dpi」(dot per inch)という単位で表します。
この値が大きいほどきめ細かく、低いほど粗くなります。
望ましい解像度は用途によって異なります。
大雑把には次のように覚えておくといいでしょう。

 * 安いWindowsノートPCで表示するなら、72dpiで十分
 * MacbookのRetinaディスプレイできれいに表示するなら、144dpiが必要
 * 高級スマートフォンできれいに表示するなら、216dpi必要
 * 商業印刷で使うなら、カラー画像で350dpi、モノクロ画像で600dpi必要

たとえば安いWindowsノートPCでスクリーンショットを撮ると、画像の解像度が72dpiになります。
これをMacbookやスマートフォンで等倍表示すると、必要な解像度に足りないせいで画像のドットが目立ちます@<fn>{fn-v6uxm}。
印刷すれば粗さがもっと目立ちます。

//footnote[fn-v6uxm][等倍で表示すると荒い画像でも、大きい画像を縮小して表示すれば粗さは目立たなくなります。解像度の高い画像を用意できない場合は、かわりに大きい画像を用意して印刷時に縮小するといいでしょう。]

では、技術同人誌では画像の解像度をどのくらいにすればいいでしょうか。
すでに説明したように、商業印刷に使う画像は350dpi以上の解像度が必要だとよく言われます。
しかし（マンガやイラストの同人誌ではなく）技術系同人誌であれば、そこまで高解像度の画像を用意しなくても大丈夫です。

実際には、Retinaディスプレイや最近のスマートフォンで画像を等倍表示して気にならない解像度であれば、印刷してもあまり気になりません。
つまり画像の解像度が144dpiであれば、印刷しても問題は少ないし、電子用PDFで使っても350dpiと比べてデータサイズをかなり小さくできます。

印刷用と電子用とで解像度の違う画像を用意するのは面倒なので、画像の解像度を144dpiにして印刷用と電子用とで同じ画像を使うのが簡単かつ妥当な方法でしょう。


=== 白黒印刷用のPDFにカラー画像を使っても大丈夫か

白黒印刷用のPDFにカラー画像を使っても、たいていは大丈夫です。
たとえばカラーのスクリーンショット画像を、わざわざモノクロ画像に変換する必要はありません。

ただし、白黒印刷すれば当然ですがカラーではなくなるので、@<B>{色の違いだけで見分けをつけていたものは白黒印刷すると見分けがつかなくなります}。
形を変えたり線の種類を変えるなどして、白黒になっても見分けがつくような工夫をしましょう。

また図の一部を赤い丸や四角で囲んでいる場合、白黒印刷すると赤ではなくなるので、たとえば「赤い丸で囲った部分に注目してください」という文章が読者に通じなくなります。
これもよくある失敗なので気をつけましょう。



=={sec-nombre} ノンブル


=== ノンブルとは

「ノンブル」とは、すべてのページにつけられた通し番号のことです。
ページ番号と似ていますが、次のような違いがあります。

//desclist[indent=0zw]{
//desc[通し番号]{
 * ページ番号は、まえがきや目次では「i, ii, iii, ...」で、本文が始まると「1, 2, 3, ...」とまる。つまり通し番号になっていない。
 * ノンブルは、まえがきや目次や本文に関係なく「1, 2, 3, ...」と続く通し番号になっている。
//}
//desc[用途]{
 * ページ番号は、読者が目的のページへ素早くアクセスするために必要。
 * ノンブルは、印刷所がページの印刷順序を間違わないために必要。
//}
//desc[表示位置]{
 * ページ番号は読者のために存在するので、読者からよく見える位置に置く。
 * ノンブルは印刷所の人だけが見られればよく、読者からは見えないほうがよい。
//}
//}

ノンブルは、印刷所へ入稿するときに必要です。
印刷しないならノンブルは不要であり、電子用PDFにはノンブルはつけません。

ノンブルについてもっと知りたい場合は「ノンブル 同人誌」でGoogle検索すると詳しい情報が見つかります。


=== ノンブルを必要とする印刷所

たいていの印刷所では入稿するPDFにノンブルが必要ですが、必要としない印刷所もあります。
たとえば技術書典でよく利用される印刷所のうち、「日光企画」ではノンブルが必須で、「ねこのしっぽ」では不要（だけどあると望ましい）です。
主な同人誌向け印刷所の情報を@<table>{tbl-uyzhu}にまとめたので参考にしてください。

//tsize[latex][lcp{81mm}]
//table[tbl-uyzhu][同人誌向け印刷所ごとのノンブル必要・不要情報][hline=on,fontsize=x-small]{
印刷所		ノンブル	参考URL
--------------------
日光企画	必要	@<href>{http://www.nikko-pc.com/qa/yokuaru-shitsumon.html#3-1}
ねこのしっぽ	不要	@<href>{https://www.shippo.co.jp/neko/faq_3.shtml#faq_039}
しまや出版	必要	@<href>{https://www.shimaya.net/howto/data-genkou.html#no}
栄光		必要	@<href>{https://www.eikou.com/qa/answer/66}
サンライズ	必要	@<href>{https://www.sunrisep.co.jp/09_genkou/002genko_kiso.html#title-6}
オレンジ工房	必要	@<href>{https://www.orangekoubou.com/order/question.php#article05}
太陽出版	必要	@<href>{https://www.taiyoushuppan.co.jp/doujin/howto/nombre.php}
ポプルス	不要	@<href>{https://www2.popls.co.jp/pop/genkou/q_and_a.html#nombre}
丸正インキ	必要	@<href>{https://www.marusho-ink.co.jp/howto/nombre.html}
トム出版	必要	@<href>{https://www.tomshuppan.co.jp/manual/data.html}
金沢印刷	必要	@<href>{http://www.kanazawa-p.co.jp/howtodata/howtodata_kihon-rule.html}
ケーナイン	必要	@<href>{https://www.k-k9.jp/data/nomble/}
booknext	必要	@<href>{https://booknext.ink/guide/making/}
//}

このように印刷所によって違いますが、@<B>{ノンブル不要の印刷所であってもノンブルをつけるほうが望ましい}です。
強い理由がないなら、印刷用PDFにはノンブルをつけましょう。


==={subsec-addnombre} ノンブルのつけ方

Re:VIEWとStarterのどちらも、印刷用PDFにはノンブルが自動的につきます（電子用にはつきません）。
Starterでは、印刷用PDFならページの右下隅または左下隅に、グレーの通し番号がついているはずです。
これがノンブルです。

ノンブルは印刷所の人だけが見られればいいので、読者からは見えにくい位置（見開きの内側）に置かれます。
このように読者から見えにくい位置に置かれたノンブルを、特に「隠しノンブル」といいます。

またStarterでは、すでに生成済みのPDFに対してあとからノンブルを追加できます。
たとえば大扉（タイトルページ）や奥付をIllustratorやKeynoteで作成し@<fn>{fn-dv7j2}、それを使って印刷用PDFの大扉や奥付のページを手動で入れ替えるような場合は@<fn>{fn-5eb1s}、入れ替えたページにノンブルがつきません。
このような場合は、次のような作業手順になります。

//footnote[fn-dv7j2][大扉（タイトルページ）を別のソフトで作成した例が@<secref>{06-bestpractice|subsec-visualtitlepage}にあります。]
//footnote[fn-5eb1s][昔はこうする必要がありましたが、現在のStarterは大扉と奥付をPDFファイルで用意すればそれを読み込めるので、手動で入れ替える必要はなくなりました。詳しくは@<secref>{04-customize|subsec-coverpdf}を参照してください。]

 - (1) 印刷用PDFをノンブルなしで生成する。
 - (2) 手動で大扉や奥付のページを入れ替える。
 - (3) 生成済みの印刷用PDFにノンブルをつける。

ここで(1)印刷用PDFをノンブルなしで生成するには、@<file>{config-starter.yml}で「@<code>|nombre: off|」を設定します。
また(3)生成済みの印刷用PDFにノンブルをつけるには、ターミナル画面で「@<code>|rake pdf:nombre|」を実行してください。

//terminal[][生成済みの印刷用PDFにノンブルをつける]{
$ @<userinput>|rake pdf:nombre|          @<balloon>{PDFの全ページにノンブルをつける}
$ @<userinput>|rake docker:pdf:nombre|   @<balloon>{Dockerを使っている場合はこちら}
//}

このRakeタスクでは、ノンブルをつけたいPDFファイル名と出力先のPDFファイル名を指定できます。
たとえば@<file>{mybook.pdf}にノンブルをつけたものを@<file>{mybook_nombre.pdf}として出力するには、次のようにします。

//terminal[][生成済みの印刷用PDFにノンブルをつける]{
$ @<userinput>|rake pdf:nombre @<b>{file=mybook.pdf} @<b>{out=mybook_nombre.pdf}|
//}

「@<code>|out=...|」が指定されなければ、「@<code>|file=...|」と同じファイル名が使われます。
また「@<code>|file=...|」が指定されなければ、「@<code>|rake pdf|」で生成されるPDFファイルの名前が使われます。

なお「@<code>{rake pdf:nombre}」はノンブルをつけるだけであり、再コンパイルはしないので注意してください。
また「@<href>{https://kauplan.org/pdfoperation/, PDFOperation}」を使っても、PDFファイルにノンブルが簡単につけられます。

//note[ノンブル用フォントの埋め込み]{
残念ながら、「@<code>{rake pdf:nombre}」でノンブルをつけるとそのフォントがPDFファイルに埋め込まれません（これはPDFファイルを操作しているライブラリの限界によるものです）。
そのため、印刷所へ入稿するまえにフォントを埋め込む必要があります。

対策方法は@<href>{https://kauplan.org/pdfoperation/}を見てください。
また印刷用PDFにデフォルトでつくノンブルならこのような問題はありません。
//}


=== ノンブルの調整

印刷所によっては、ノンブルの位置や大きさを指定される場合があります。
その場合は@<file>{config-starter.yml}の中の、ノンブルに関する設定項目を調整してください。
なおこの設定は、「@<code>|rake pdf:nombre|」タスクでも使われます。

//needvspace[latex][6zw]
//list[][@<file>{config-starter.yml}：ノンブルに関する設定項目]{
  ## ノンブル（1枚目からの通し番号）の設定
  nombre:               on       @<balloon>{on ならノンブルをつける}
  nombre_sidemargin:    0.5mm    @<balloon>{ページ左右からのマージン幅}
  nombre_bottommargin:  2.0mm    @<balloon>{ページ下からのマージン高}
  nombre_fontcolor:     gray     @<balloon>{'gray' or 'black'}
  nombre_fontsize:      6pt      @<balloon>{フォントサイズ（6〜8pt）}
  nombre_startnumber:   1        @<balloon>{ノンブルの開始番号（3から始める流儀もある）}
//}


=== ノンブルの注意点

印刷所への入稿に慣れていないと、ノンブルに関するトラブルを起こしがちです。
初心者の人は次のような点に注意してください。

 * すでに説明したように、ノンブルは印刷するときに必要であり、印刷しなければ不要です。
   Starterでは印刷用PDFにのみ自動でノンブルがつきますが、電子用PDFにはつきません。
 * ノンブルは、表紙と裏表紙には必要ありません。
   印刷所へ入稿するとき、表紙と裏表紙の入稿は本文とは別に行います。
   そのため、表紙と裏表紙にはノンブルをつける必要はありませんし、つけてはいけません。
 * ノンブルは、表紙と裏表紙を除いたすべてのページに必要です。
   たとえ空白ページであってもノンブルを省略してはいけません。
 * 別のソフトで作った大扉（タイトルページ）や奥付をPDFに入れた場合は、それらのページにもノンブルをつけることを忘れないでください。
 * 印刷所からノンブルの位置や大きさの指定がある場合は、それに従ってください。
   ノンブルの調整方法は@<file>{config-starter.yml}で行えます。
 * ノンブルは「1」から始めることがほとんどですが、印刷所によっては「3」から始めるよう指示されることがあります。
   その場合は@<file>{config-starter.yml}に「@<code>|nombre_startnumber: 3|」を設定してください。
 * ノンブルのフォントがPDFに埋め込まれていることを確認してください。
   ただし本文のフォントほど重要ではないので、もしノンブルのフォントがうまく埋め込めない場合は、そのままで入稿できないか印刷所に相談してみましょう。



== @<LaTeX>{}関連


=== LuaLaTeXとjlreqを使いたい

Starterでは、LuaLaTeXとjlreq.clsにはまだ対応していません。
どうしてもこれらが使いたい場合は、Re:VIEWが対応しているのでそちらを使うといいでしょう。

LuaLaTeXは好きなフォントが簡単に使えるという大きな利点がありますが、コンパイルが遅くなるという欠点があります。
またjlreq.clsはカスタマイズ方法がよく分かっていないので、採用ができません。

これらの採用は今後の課題です。


=== @<LaTeX>{}のスタイルファイルから環境変数を参照する

Starterでは、名前が「@<em>{STARTER_}」で始まる環境変数を@<LaTeX>{}のスタイルファイルから参照できます。

たとえば「@<code>{STARTER_FOO_BAR}」という環境変数を設定すると、@<code>{sty/mystyle.sty}や@<code>{sty/starter.sty}では「@<code>{\STARTER@FOO@BAR}」という名前で参照できます。
この例で分かるように、環境変数名の「@<code>{_}」は「@<code>{@}」に変換されます。

//terminal[][環境変数を設定する例(macOS, UNIX)]{
$ @<userinput>{export STARTER_FOO_BAR="foobar"}
//}

//list[][環境変数を参照する例]{
%% ファイル：sty/mystyle.sty
\newcommand\foobar[0]{%             % 引数なしコマンドを定義
  \@ifundefined{STARTER@FOO@BAR}{%  % 未定義なら
    foobar%                         % デフォルト値を使う
  }{%                               % 定義済みなら
    \STARTER@FOO@BAR%               % その値を使う
  }%
}
//}

この機能を使うと、出力や挙動を少し変更したい場合に環境変数でコントロールできます。
また値の中に「@<code>{$}」や「@<code>{\\}」が入っていてもエスケープはしないので注意してください。



== その他


=== 高度なカスタマイズ

設定ファイルや@<LaTeX>{}スタイルファイルでは対応できないようなカスタマイズが必要になることがあります。
たとえば次のような場合です。

 * 印刷用とタブレット用でPDFファイルの仕様を大きく変えたい。
 * B5サイズとA5サイズの両方のPDFファイルを生成したい。
 * β版と本番用とで設定を切り替えたい。
 * コンパイルするたびに、あるプログラムの実行結果を原稿ファイルに埋め込みたい。

このような要件を、Re:VIEWやStarterの機能を使い倒して実現してもいいですが、それよりも汎用的なやり方で実現しましょう。
方針としては、設定ファイルや原稿ファイルを用途に応じて生成するのがいいでしょう。

ここでは例として「印刷用とタブレット用で@<file>{config-starter.yml}の内容を変える」ことを考えてみます。

//blankline
//noindent
(1) 「@<file>{config-starter.yml}」に拡張子「@<file>{.eruby}」をつけます。

//terminal{
$ @<userinput>{mv config-starter.yml config-starter.yml.eruby}
## またはこうでもよい
$ @<userinput>$mv config-starter.yml{,.eruby}$
//}

//noindent
(2) 次に、そのファイルに次のような条件分岐を埋め込みます。

//list[][ファイル「config-starter.yml.eruby」]{
....(省略)....
@<b>$<% if buildmode == 'printing'   # 印刷向け %>$
  target:    pbook
  pagesize:  B5
  fontsize:  10pt
  textwidth: 44zw
@<b>$<% elsif buildmode == 'tablet'  # タブレット向け %>$
  target:    tablet
  pagesize:  A5
  fontsize:  10pt
  textwidth: 42zw
@<b>$<% else abort "error: buildmode=#{buildmode.inspect}" %>$
@<b>$<% end %>$
//}

//noindent
(3) 「@<file>{config-starter.yml}」を生成するRakeタスクを定義します。
ここまでが準備です。

//source[lib/tasks/mytasks.rake]{
def render_eruby_files(param)   # 要 Ruby >= 2.2
  Dir.glob('**/*.eruby').each do |erubyfile|
    origfile = erubyfile.sub(/\.eruby$/, '')
    sh "erb -T 2 -P '#{param}' #{erubyfile} > #{origfile}"
  end
end

namespace :setup do

  desc "*印刷用に設定 (B5, 10pt, mono)"
  task :printing do
    render_eruby_files('buildmode=printing')
  end

  desc "*タブレット用に設定 (A5, 10pt, color)"
  task :tablet do
    render_eruby_files('buildmode=tablet')
  end

end
//}

//noindent
(4)「@<code>{rake setup:printing}」または「@<code>{rake setup:tablet}」を実行すると、@<file>{config-starter.yml}が生成されます。
そのあとで「@<code>{rake pdf}」を実行すれば、用途に応じたPDFが生成されます。

//cmd{
$ @<b>{rake setup:printing  # 印刷用}
$ rake pdf
$ mv mybook.pdf mybook_printing.pdf

$ @<b>{rake setup:tablet    # タブレット用}
$ rake pdf
$ mv mybook.pdf mybook_tablet.pdf
//}
