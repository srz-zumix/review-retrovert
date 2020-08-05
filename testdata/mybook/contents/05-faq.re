= FAQ

//abstract{
よくある質問とその回答(Frequentry Asked Question, FAQ)を紹介します。
//}

#@#//makechaptitlepage[toc=on]


=={sec-compileerror} コンパイルエラー


=== コンパイルエラーが出たとき

PDFファイル生成時にコンパイルエラーになったときの対処方法について説明します。

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

「@<code>|@@<nop>{}<code>{...}|」を使って文章中に埋め込んだプログラムコードに、背景色をつけられます。
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

具体的には、ファイル「@<file>{config-starter.yml}」の中の「@<code>{program_widen: 0.0mm}」や「@<code>{terminal_wide: 0.0mm}」を、たとえば「@<code>{0.3mm}」に設定してください（値は各自で調整してください）。

//list[][ファイル「config-starter.yml」]{
  ## プログラム（//list）の表示幅をほんの少しだけ広げる。
  @<del>{program_waiden:   0.0mm}
  @<b>{program_widen:   0.3mm}

  ## ターミナル（//terminal, //cmd）の表示幅をほんの少しだけ広げる。
  @<del>{terminal_widen:  0.0mm}
  @<b>{terminal_widen:  0.3mm}
//}

こうすると、プログラムやターミナルの表示幅が少しだけ広がり、文字が右端まで埋まるようになります（@<img>{codeblock_rpadding2}）。

//image[codeblock_rpadding2][表示幅をほんの少し広げると、右端まで埋まるようになった][scale=0.7]


=== 半角文字の幅を全角文字の半分にしたい

英数字の幅が狭いフォントを使うと、半角文字の幅が全角文字の約半分になります（ぴったりにはなりません）。

@<file>{config-starter.yml}で、以下のうち必要なほうを設定してください。

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

//list[][サンプル]{
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



== その他


=== @<LaTeX>{}のスタイルファイルから環境変数を参照する

Starterでは、名前が「@<em>{STARTER_}」で始まる環境変数を@<LaTeX>{}のスタイルファイルから参照できます。

たとえば「@<code>{STARTER_FOO_BAR}」という環境変数を設定すると、@<code>{sty/mystyle.sty}や@<code>{sty/starter.sty}では「@<code>{\STARTER@FOO@BAR}」という名前で参照できます。
想像がつくと思いますが、環境変数名の「@<code>{_}」は「@<code>{@}」に変換されます。

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
