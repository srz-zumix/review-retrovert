= カスタマイズ

//abstract{
Starterをカスタマイズする方法を紹介します。
//}

#@#//makechaptitlepage[toc=on]



== 命令

新しい命令を追加するには、ファイル「@<file>{review-ext.rb}」を編集します。


=== 新しいインライン命令を追加する

たとえば次の例では、新しいインライン命令「@<code>|@@<nop>{}<bold>{...}|」を追加しています。

//list[][ファイル「review-ext.rb」]{
module ReVIEW

  ## インライン命令「@@<nop>{}<bold>{}」を宣言
  @<b>{Compiler.definline :bold}

  ## LaTeX用の定義
  @<b>{class LATEXBuilder}
    @<b>{def on_inline_bold(&b)}  # 入れ子を許す場合
      return "\\textbf{#{yield}}"
    end
    #@<b>{def inline_bold(str)}    # 入れ子をさせない場合
    #  return "\\textbf{#{escape(str)}}"
    #end
  end

  ## HTML（ePub）用の定義
  @<b>{class HTMLBuilder}
    @<b>{def on_inline_bold(&b)}  # 入れ子を許す場合
      return "<b>#{yield}</b>"
    end
    #@<b>{def inline_bold(str)}    # 入れ子をさせない場合
    #  return "<b>#{escape(str)}</b>"
    #end
  end

end
//}

なお既存のインライン命令を変更するのも、これと同じ方法で行えます。


=== 新しいブロック命令を追加する

たとえば次の例では、新しいブロック命令「@<code>|//blockquote{ ... //}|」を追加しています@<fn>{fn-g4he6}。

//footnote[fn-g4he6][インライン命令のときは「@<code>|on_inline_xxx()|」なのにブロック命令では「@<code>|on_xxx_block()|」なのは、歴史的な事情です。非対称で格好悪いですが、ご了承ください。]

//list[][ファイル「review-ext.rb」]{
module ReVIEW

  ## ブロック命令「//blockquote」を宣言（引数は0〜1個）
  @<b>{Compiler.defblock :blockquote, 0..1}

  ## LaTeX用の定義
  @<b>{class LATEXBuilder}
    ## 入れ子を許す場合
    @<b>{def on_blockquote_block(arg=nil)}
      if arg.present?
        puts "\\noindent"
        puts escape(arg)
      end
      puts "\\begin{quotation}"
      @<b>{yield}
      puts "\\end{quotation}"
    end
    ## 入れ子を許さない場合
    #@<b>{def blockquote(lines, arg=nil)}
    #  if arg.present?
    #    puts "\\noindent"
    #    puts escape(arg)
    #  end
    #  puts "\\begin{quotation}"
    #  puts lines
    #  puts "\\end{quotation}"
    #end
  end

  ## HTML（ePub）用の定義
  @<b>{class HTMLBuilder}
    ## 入れ子を許す場合
    @<b>{def on_blockquote_block(arg=nil)}
      if arg.present?
        puts "<p><span>#{escape(arg)}</span></p>"
      end
      puts "<blockquote>"
      yield
      puts "</blockquote>"
    end
    ## 入れ子を許さない場合
    #@<b>{def blockquote(lines, arg=nil)}
    #  if arg.present?
    #    puts "<p><span>#{escape(arg)}</span></p>"
    #  end
    #  puts "<blockquote>"
    #  puts lines
    #  puts "</blockquote>"
    #end
  end

end
//}

ブロック命令には「@<code>|{ ... //}|」を使わないタイプのものもあります。
その場合は「@<code>|Compiler.defsingle|」を使います。

たとえば縦方向にスペースを空ける「@<code>|//verticalspace[タイプ][高さ]|」というブロック命令を追加するとしましょう。
使い方は次の通りとします。

//list{
@<nop>{}//verticalspace[latex][5mm]   @<balloon>{PDFのときは5mm空ける}
@<nop>{}//verticalspace[epub][10mm]   @<balloon>{ePubのときは10mm空ける}
@<nop>{}//verticalspace[*][15mm]      @<balloon>{PDFでもePubでも15mm空ける}
//}

このようなブロック命令は、次のように定義します。
「@<code>|Compiler.defblock|」ではなく「@<code>|Compiler.defsingle|」を使っている点に注意してください。

//list[][ファイル「review-ext.rb」]{
module ReVIEW

  ## ブロック命令「//verticalspace」を宣言（引数は2個）
  @<b>{Compiler.defsingle :verticalspace, 2}

  ## LaTeX用の定義
  @<b>{class LATEXBuilder}
    ## '{ ... //}' を使わないので入れ子対応にはしない
    @<b>{def verticalspace(type, length)}
      if type == 'latex' || type == '*'
        puts "\\vspace{#{length}}"
      end
    end
  end

  ## HTML（ePub）用の定義
  @<b>{class HTMLBuilder}
    ## '{ ... //}' を使わないので入れ子対応にはしない
    @<b>{def veritcalspace(type, length)}
      if type == 'html' || type == 'epub' || type == '*'
        puts "<div style=\"height: #{length}\"></div>"
      end
    end
  end

end
//}

なお既存のブロック命令を変更するのも、これらと同じ方法で行えます。



== ページと本文


=== [PDF] ページサイズをB5やA5に変更する

ページサイズをB5やA5に変更するには、「@<file>{config-starter.yml}」の設定項目「@<code>|pagesize:|」を変更します@<fn>{fn-yq0ne}。

//list[][ファイル「config-starter.yml」]{
  pagesize: @<b>{A5}    # A5 or B5
//}

//footnote[fn-yq0ne][以前は「@<file>{config.yml}」の中の「@<code>|texdocumentclass:|」を変更していましたが、その必要はなくなりました。]


==={subsec-textwidth} [PDF] 本文の幅を指定する

本文の幅を指定するには、「@<file>{config-starter.yml}」の設定項目「@<code>|textwidth:|」を変更します@<fn>{fn-ragkm}。

//list[][ファイル「config-starter.yml」]{
  textwidth: @<b>{39zw}    # 全角文字数で指定
//}

//footnote[fn-ragkm][以前は「@<file>{sty/mytextsize.sty}」を編集していましたが、本文幅を変更するだけならその必要はなくなりました。]

ここで、「@<code>|zw|」は全角1文字分の幅を表す単位です。
「@<code>|39zw|」なら全角39文字分の幅（長さ）を表します。

Starterでは@<table>{tbl-rlsli}のような本文幅を推奨しています。

//tsize[latex][ccl]
//table[tbl-rlsli][本文幅の推奨値（タブレット向けを除く）][hline=off]{
ベージサイズ	フォントサイズ	本文幅
--------------------
A5		9pt		全角38文字か39文字
A5		10pt		全角35文字
B5		10pt		全角44文字か45文字
B5		11pt		全角41文字
//}

Starterでは、印刷用PDFではページ左右の余白幅を変えています。
これは印刷時の読みやすさを確保したまま、本文の幅を最大限に広げているからです。
詳しくは@<secref>{06-bestpractice|subsec-sidemargin}を見てください。


==={subsec-textheight} [PDF] 本文の高さを指定する

本文の高さを調整するには、「@<file>{sty/mytextsize.sty}」を編集します。

//list[][ファイル「sty/mytextsize.sty」]{
%% 天（ページ上部）の余白を狭め、その分を本文の高さに加える
\addtolength{\topmargin}{@<b>|-2\Cvs|}  % 上部の余白を2行分減らす
\addtolength{\textheight}{@<b>|2\Cvs|}  % 本文の高さを2行分増やす
//}

通常は、このような変更は必要ないはずです。


==={subsec-bleed} [PDF] 塗り足しをつける

印刷所に入稿するとき、本文の全ページに上下左右3mmの「塗り足し」が必要になることがあります。
塗り足しについては次のページなどを参考にしてください。

 * 原稿作成の基礎知識：塗り足し（同人誌印刷栄光）@<br>{}
   @<href>{https://www.eikou.com/making/basis#nuritashi}
 * 原稿作成マニュアル：印刷範囲と塗り足し（同人誌印刷の緑陽社）@<br>{}
   @<href>{https://www.ryokuyou.co.jp/doujin/manual/basic.html#nuritashi}

塗り足しは、技術系同人誌の本文ではたいていの場合必要ありませんが、次のような場合は必要です。

 * ページ端まで絵や線が描かれている場合
 * 背景色をつけたページがある場合（大扉や章扉など）

//note[技術系同人誌でも表紙と裏表紙には塗り足しが必要]{
同人誌作成の経験がない方のために補足説明をします。

 * 印刷所に入稿するとき、表紙や裏表紙と、本文とは別のPDFファイルにします。
   前者はカラー印刷、後者は白黒印刷です。
 * 表紙や裏表紙では背景色をつけることがほとんどなので、塗り足しが必要です。
 * マンガ系の同人誌では背景色があったりページ端まで絵を描くことがあるので、塗り足しが必要です。
   同人誌印刷所のサイトで「塗り足しは必須です」と説明されているのは、マンガ同人誌を前提としているからです。
 * 技術系同人誌の本文では背景色をつけないしページ端まで何かを描くこともないので、塗り足しは必要ありません。
   ただしこれは印刷所によって違う可能性があるので、詳しくは入稿先の印刷所に聞いてみてください。
 * 塗り足しが必要ないのに塗り足しをつけてしまっても、問題ありません。
 * 塗り足しは印刷するときにのみ必要であり、印刷しないなら必要ありません。
//}

Starterでは、塗り足しをつける設定が用意されています。

//list[][@<file>{configi-starter.yml}：塗り足しをつける]{
  ## 上下左右の塗り足し幅（印刷用PDFのみ）
  bleedsize: 3mm      # 上下左右に3mmの塗り足しをつける
//}

塗り足しがつくのは印刷用PDFのみであり、電子用にはつきません@<fn>{fn-alz7r}。
また塗り足しは上下左右につくので、塗り足し幅が3mmだとページサイズの縦と横は6mmずつ増えます。

//footnote[fn-alz7r][印刷用PDFと電子用PDFの違いについては、@<secref>{02-tutorial|sec-pdftype}を参照してください。]


=== [PDF] 塗り足しを可視化する

塗り足しがどのくらいの幅を取るのか、見た目で確認したい人もいるでしょう。
そのような場合は、@<file>{config-starter.yml}で「@<code>|bleedcolor: blue|」のように指定してください。
すると塗り足しが可視化されます。
色はred/green/blue/yello/grayなどが使えます。

この機能は、あくまで確認用のみで使ってください。
入稿するときは必ず設定を外してください。


=== [PDF] 章の右ページ始まりをやめる

横書きの本では、章(Chapter)を見開きの右ページから始めるのが一般的です。
そのため、その前のページが空ページになることがよくあります。
この空ページを入れたくないなら、章の右ページ始まりを止めて左右どちらのページからも始めるようにします。

右ページ始まりをやめるには、「@<file>{config.yml}」の設定項目「@<code>|texdocumentclass:|」を変更します。

//list[][ファイル「config.yml」]{
texdocumentclass: ["jsbook",
    @<del>|"dvipdfmx,uplatex,papersize,twoside,@<b>{openright}"| @<balloon>{右ページはじまり}
    "dvipdfmx,uplatex,papersize,twoside,@<b>{openany}"   @<balloon>{両ページはじまり}
]
//}


==={subec-miniblockdesign} [PDF] 「//info」や「//warning」のデザインを変更する

Re:VIEWやStarterでは、「@<code>|//note|」以外にも「@<code>|//info|」や「@<code>|//warning|」が使えます（詳しくは@<secref>{03-syntax|subsec-miniblock}を見てください）。

「@<code>|//info|」や「@<code>|//warning|」で使われているアイコン画像を変更するには、「@<file>{sty/mystyle.sty}」にたとえば次のように書いてください。

//list[][ファイル「@<file>{sty/mystyle.sty}」]{
\def\starter@miniblock@info@imagefile{./images/info-icon.png}
\def\starter@miniblock@warning@imagefile{./images/warning-icon.png}
//}

アイコン画像の表示サイズや本文のフォントを変更するには、次のように書いてください。

//list[][ファイル「@<file>{sty/mystyle.sty}」]{
\def\starter@miniblock@imagewidth{3zw} % アイコン画像の表示幅
\def\starter@miniblock@indent{4zw}     % 本文のインデント幅
\def\starter@miniblock@font{\small}    % 本文のフォント
//}

「@<code>|//memo|」や「@<code>|//tips|」や「@<code>|//important|」などには、デフォルトではアイコン画像はつきません。
これらにもアイコン画像をつけるには、たとえば次のように書いてください。

//list[][ファイル「@<file>{sty/mystyle.sty}」]{
%% 「//important」にアイコン画像をつける
\newenvironment{starterimportant}[1]{%
  \begin{starter@miniblock}[\starter@miniblock@important@imagefile]{#1}%
}{%
  \end{starter@miniblock}%
}
\def\starter@miniblock@important@imagefile{./images/info-icon.png}
//}

デザインそのものを変更するには、たとえば次のようにしてください（どんな表示になるかは自分で確かめてください）。

//list[][ファイル「@<file>{sty/mystyle.sty}」]{
%% 「//memo」のデザインを変更する
\usepackage{ascmac}
\renewenvironment{startermemo}[1]{%
  \addvspace{1.5\baselineskip}% 1.5行分空ける
  \begin{boxnote}%            % 飾り枠で囲む
    \ifempty{#1}\else%        % 引数（タイトル）があれば
      {\centering%            % センタリングして
        \headfont\Large#1\par}% 太字のゴシック体で大きく表示
      \bigskip%               % 縦方向にスペースを空ける
    \fi%
    \setlength{\parindent}{1zw}% 段落の先頭を字下げする
}{%
  \end{boxnote}%              % 飾り枠の終わり
  \addvspace{1.5\baselineskip}% 1.5行分空ける
}
//}



== フォント


==={subsec-fontsize} [PDF] フォントサイズを変更する

本文のフォントのサイズを変更するには、「@<file>{config-starter.yml}」の設定項目「@<code>|fontsize:|」を変更します@<fn>{fn-fy3mx}。

//list[][ファイル「config-starter.yml」]{
  fontsize:  @<b>{9pt}      # 9pt or 10pt
//}

//footnote[fn-fy3mx][以前は「@<file>{config.yml}」の設定項目「@<code>|texdocumentclass:|」を変更していましたが、その必要はなくなりました。]

フォントサイズは、A5サイズなら9pt、B5サイズなら10ptにするのが一般的です。
ただし初心者向けの入門書では少し大きくして、A5サイズなら10pt、B5サイズなら11ptにするのがいいでしょう。

//note[商業誌のフォントサイズと本文幅]{
A5サイズの商業誌で使われているフォントサイズと本文幅を調べました(@<table>{tbl-8jedm})。
参考にしてください。

//tsize[][|lll|]
//table[tbl-8jedm][商業誌のフォントサイズと本文幅][hline=off,fontsize=x-small]{
出版社		書籍名			各種サイズ
====================
オライリー・ジャパン	『リーダブルコード』	A5、9pt、38文字
.		『ゼロから作るDeep Learning』	A5、9pt、38文字

翔泳社		『達人に学ぶSQL徹底指南書 第2版』	A5、9pt、38文字

オーム社	『アジャイル・サムライ』	A5、10pt、36文字

技術評論社	『オブジェクト指向UIデザイン』	A5、9pt、35文字
.		『現場で役立つシステム設計の原則』	A5、10pt、33文字

日経BP社	『独習プログラマー』	A5、10pt、34文字
//}

//}


==={subsec-fontfamily} [PDF] フォントの種類を変更する

本文のフォントを変更するには、「@<file>{config-starter.yml}」の設定項目「@<code>|fontfamily_ja:|」と「@<code>|fontfamily_en:|」を変更します。

//list[][ファイル「config-starter.yml」]{
  ## 本文のフォント（注：実験的）
  ## （Notoフォントが前提なので、Docker環境が必要。MacTeXでは使わないこと）
  fontfamily_ja: @<b>{mincho}   @<balloon>{mincho: 明朝体, gothic: ゴシック体}
  fontfamily_en: @<b>{roman}    @<balloon>{roman: ローマン体, sansserif: サンセリフ体}
  fontweight_ja: @<b>{normal}   @<balloon>{normal: 通常, light: 細字}
  fontweight_en: @<b>{normal}   @<balloon>{normal: 通常, light: 細字}
//}

または、「@<file>{sty/mystyle.sty}」に以下を追加します。

//list[][ファイル「sty/mystyle.sty」]{
%% 英数字のフォントをサンセリフ体に変更
\renewcommand\familydefault{@<b>|\sfdefault|}
%% 日本語フォントをゴシック体に変更
\renewcommand\kanjifamilydefault{@<b>|\gtdefault|}
%% （macOSのみ）日本語フォントを丸ゴシックに変更
%\renewcommand\kanjifamilydefault{@<b>|\mgdefault|}
//}



== プログラムコード


==={subsec-needvspace} [PDF] 説明文直後での改ページを防ぐ

プログラムコードの説明文の直後で改ページされてしまうことがあります。
すると説明文とプログラムコードが別ページに離れてしまうため、読みにくくなります（@<img>{caption_pagebreak}）。

//image[caption_pagebreak][説明文の直後で改ページされることがある][scale=0.7]

Starterではこれを防ぐための工夫をしていますが、それでも発生してしまうことがあります。
もし発生したときは、次の対策のうちどちらを行ってください。

===== 個別対策：「@<code>{//needvspace[]}」を使う

たとえば「@<code>|//needvspace[latex][6zw]|」とすると、現在位置に全角6文字分の高さのスペースがあるかを調べ、なければ改ページします。

//list[][全角6文字分の高さのスペースがなければ改行]{
@<b>{//needvspace[latex][6zw]}
@<nop>{}//list[][フィボナッチ数列]{
def fib(n)
  n <= 1 ? n : fib(n-1) + fib(n-2)
end
@<nop>{}//}
//}

===== 全体対策：「@<code>|caption_needspace:|」の値を増やす

@<file>{config-starter.yml}の「@<code>|caption_needspace:|」がたとえば「@<code>|4.0zh|」であれば、プログラムリストの説明文を表示する前に全角4文字分の高さのスペースがあるかを調べ、なければ改ページします。
よってこの設定値を増やせば、説明文だけが別ページになるのを防げます。

ただしこの設定値は、説明文を持つすべてのプログラムリストに影響します。
設定値を変える場合は注意してください。


==={subsec-ttfont} [PDF] プログラムコードのフォントを変更する

プログラムコードやターミナルのフォントを変更するには、「@<file>{config-starter.yml}」の設定項目「@<code>|program_ttfont:|」と「@<code>|terminal_ttfont:|」を変更します。

//list[][ファイル「config-starter.yml」]{
  ## プログラム用（//list）の等幅フォント
  program_ttfont: @<b>{beramono}
  ## ターミナル用（//terminal、//cmd）の等幅フォント
  terminal_ttfont: @<b>{inconsolata-narrow}
//}

どんなフォントが使えるかは、「@<file>{config-starter.yml}」の中に書いてあります。


=== プログラムコードの枠線

プログラムコードに枠線をつける・つけないを変更するには、次の設定を変更してください。

//list[][ファイル「config-starter.yml」]{
  ## プログラム（//list）を枠で囲むならtrue、囲まないならfalse
  program_border: true
//}

プログラムコードがページをまたぐときは、枠線つきのほうが分かりやすいです。
詳しくは@<secref>{06-bestpractice|subsec-programborder}を見てください。


==={subsec-defaultopts} オプションのデフォルト値

「@<code>|//list|」の第3引数には、さまざまなオプションが指定できます。
これらのオプションは、デフォルト値が「@<file>{config-starter.yml}」で次のように設定されています。
ここで、YAML@<fn>{d15gt}では「@<code>|on, off, ~|」がそれぞれ「@<code>|true, false, null|」と同じ意味になります。

//footnote[d15gt][「YAML」とはデータを構造化して記述する書き方のひとつであり、JSONの親戚みたいなものです。@<file>{config-starter.yml}はYAMLで書かれています。]

//list[][@<file>{config-starter.yml}]{
  ## プログラム（//list）のデフォルトオプション
  ## （注：YAMLでは `on, off, ~` は `true, false, null` と同じ）
  program_default_options:
    fold:        on        # on なら長い行を右端で折り返す
    foldmark:    on        # on なら折り返し記号をつける
    eolmark:     off       # on なら行末に改行記号をつける
    lineno:      ~         # 1 なら行番号をつける
    linenowidth: ~         # 行番号の幅を半角文字数で指定する
    indent:      ~         # インデント幅
    fontsize:    ~         # small/x-small/xx-smal
    lang:        ~         # デフォルトのプログラミング言語名
    #file:       ~         # （使用しない）
    encoding:    utf-8     # ファイルの文字コード
//}

たとえば「@<code>|//list|」にデフォルトで行番号とインデント記号をつけるには、設定を次のように変更します。

//list[][「@<code>|//list|」にデフォルトで行番号とインデント記号をつける]{
  program_default_options:
    @<weak>{#...省略...}
    lineno:      @<b>{1}         # 1 から始まる行番号をつける
    linenowidth: @<b>{2}         # 行番号を2桁で（0なら自動計算）
    indent:      @<b>{4}         # インデント幅を半角空白4文字に
    @<weak>{#...省略...}
//}

このようにデフォルト値を変更すれば、「@<code>|//list|」にオプションを何も指定しなくても、行番号とインデント記号がつくようになります。

なおこのように設定をしたうえで、特定のプログラムコードでだけ行番号やインデント記号をつけたくない場合は、「@<code>|//list[][][lineno=@<b>{off},indent=@<b>{off}]|」のように個別の指定をしてください。

またターミナル画面を表す「@<code>|//terminal|」のオプションも、デフォルト値が@<file>{config-starter.yml}で設定されています。
項目名が「@<code>|terminal_default_options:|」であること以外はプログラムコードの場合と同じです。


==={sec-excluding} [PDF] 折り返し記号や行番号をマウス選択の対象から外す

PDF中のプログラムコードをマウスで選択してコピーすると、折り返し記号や行番号や改行記号もコピーされてしまいます。
これはプログラムコードをコピペするときに不便です。

Starterでは、これらの記号をマウスの選択対象から外すことができます。
そのためには、次のどちらかを設定してください。

 * @<file>{config-starter.yml}の「@<code>|exclude_mouseelect:|」を@<code>|true|にする。
 * 環境変数「@<code>|$STARTER_EXCLUDE_MOUSESELECT|」を「@<code>|on|」に設定する（「@<code>|true|」ではダメ）。

この設定をしてからPDFを生成すると、以下のものがマウスの選択対象にならなくなります@<fn>{y2q8d}。

 * 折り返し記号
 * 行番号
 * 改行記号

なおインデントを表す記号は、文字ではなく図形として縦線を描写しているため、マウスでの選択対象にはなりません。

//footnote[y2q8d][「@<code>|@@<nop>{}<balloon>{}|」で埋め込んだコメント文字列は、マウスコピーの対象外@<bou>{ではありません}。これは意図した仕様です。もしこれも対象外にしたい場合は、相談してください。]

ただし、この機能が有効なのはAcrobat Readerのみです。
macOSのPreview.appでは効かないので注意してください。

またこの設定をオンにすると、@<LaTeX>{}のコンパイル時間が大幅に増えます。
そのため、デフォルトではオフになっています。
リリース時にだけ環境変数「@<code>|$STARTER_EXCLUDE_MOUSESELECT|」を@<code>|on|にするといいでしょう。

//terminal[?][「@<code>|$STARTER_EXCLUDE_MOUSESELECT|」を@<code>|on|にしてPDFを生成]{
$ STARTER_EXCLUDE_MOUSESELECT=on rake pdf
//}



== 見出し


=== 章のタイトルデザインを変更する

章(Chapter)のタイトルデザインを変更するには、「@<file>{config-starter.yml}」の設定項目「@<code>|capter_decoration:|」を変更します。

//list[][ファイル「config-starter.yml」]{
  ## 章 (Chapter) タイトルの装飾
  ## （none: なし、underline: 下線、boldlines: 上下に太線）
  chapter_decoration: @<b>{boldlines}

  ## 章 (Chapter) タイトルの左寄せ/右寄せ/中央揃え
  ## （left: 左寄せ、right: 右寄せ、center: 中央揃え）
  chapter_align: @<b>{center}

  ## 章 (Chapter) タイトルを1行にする（章番号とタイトルとの間で改行しない）
  chapter_oneline: @<b>{false}
//}


==={subsec-sectitle} 節のタイトルデザインを変更する

節(Section)のタイトルデザインを変更するには、「@<file>{config-starter.yml}」の設定項目「@<code>|section_decoration:|」を変更します。

//list[][ファイル「config-starter.yml」]{
  ## 節 (Section) タイトルの装飾
  section_decoration: @<b>{grayback}
//}

#@#指定できる値は「@<code>{config-starter.yml}」の中に書かれています。
どんなデザインが指定できるかは、@<img>{section_decoration_samples}を参照してください。

//image[section_decoration_samples][節タイトルのデザイン][scale=0.99,pos=p,border=on]

//note[節タイトルが長くて2行になる場合]{
もし節タイトルが長くて2行になることがある場合は、「@<code>|circle|」「@<code>|leftline|」「@<code>|numbox|」のどれかを指定するといいでしょう。
それ以外だと、デザインが破綻してしまいます。
//}




==={subsec-paragraphdesign} 段見出しのデザインを変更する

段(Paragraph)見出しや小段(Paragraph)見出しのデザインを変更するには、「@<file>{sty/starter-heading.sty}」から「@<code>|\Paragraph@title|」や「@<code>|\Subparagraph@title|」の定義を取り出し、「@<file>{sty/mystyle.sty}」にコピーしたうえで変更してください。


#@#=== [PDF] 章や節のタイトル上下のスペースを調整する

=== [PDF] 章や節のタイトルを独自にデザインする

章(Chapter)や節(Section)のタイトルのデザインは、「@<file>{sty/starter-heading.sty}」で定義されています。
これらを変更したい場合は、必要な箇所を「@<file>{sty/mystyle.sty}」にコピーしてから変更してください。

またマクロを上書きする場合は、「@<code>{\newcommand}」ではなく「@<code>{\renewcommand}」を使うことに注意してください。


=== [PDF] 章扉をつける

Starterでは、章(Chapter)ごとにタイトルページをつけられます（@<img>{chaptitlepage_sample}）。
これを「章扉」といい、商業誌ではとてもよく見かけます。

//image[chaptitlepage_sample][章扉（章の概要と目次つき）][scale=0.5]

章扉をつけるには、次のようにします。

 * 章タイトル直後に「@<code>|//abstract{ ... //}|」で概要を書く（必須）。
 * そのあとに「@<code>{//makechaptitlepage[toc=on]}」を書く。
 * これをすべての章に対して行う（まえがきやあとがきは除く）。

//list[][章扉をつける]{
@<nop>{}= 章タイトル

@<b>|//abstract{|
...章の概要...
@<b>|//}|

@<b>|//makechaptitlepage[toc=on]|

@<nop>{}== 節タイトル
//}

章扉では、その章に含まれる節(Section)の目次が自動的につきます。
これは読者にとって便利なので、特にページ数の多い本では章ごとのタイトルページをつけることをお勧めします。


=== [PDF] 章扉に背景色をつける

章扉には、デフォルトでは背景色がついていませんが、背景色をつけると見栄えがかなりよくなります。

背景色は@<file>{sty/config-color.sty}において「@<code>{starter@chaptitlepagecolor}」という名前で定義されているので、これを上書き設定すれば変更できます。
設定は@<file>{sty/mystyle.sty}で行うといいでしょう。

//list[][@<file>{sty/mystyle.sty}：章扉の背景色を設定する]{
\definecolor{starter@chaptitlepagecolor}{gray}{0.9}% 明るいグレー
//}

また章扉に背景色を設定した場合は、印刷用PDFの上下左右に3mmずつの「塗り足し」をつけるのが望ましいです。
そのためには、@<file>{config-starter.sty}で「@<code>{bleedsize: 3mm}」を設定してください。
この設定は印刷用PDFでのみ機能し、電子用PDFでは無視されます。
詳しくは@<secref>{subsec-bleed}を参照してください。


==={subsec-newpagepersec} [PDF] 節ごとに改ページする

初心者向けの入門書では、節(Chapter)ごとに改ページするデザインが好まれます。
Starterでこれを行うには、「@<file>{config-starter.yml}」で設定項目「@<code>|section_newpage:|」を「@<code>|true|」に設定します。

//list[][ファイル「config-starter.yml」]{
  ## 節 (Section) ごとに改ページするか
  ## （ただし各章の最初の節は改ページしない）
  section_newpage: @<b>{true}
//}


==={subsec-subsecnum} 項に番号をつける

Re:VIEWやStarterでは、デフォルトでは項(Subsection)に番号がつきません。
項にも番号をつけるには、「@<file>{config.yml}」の設定項目「@<code>|secnolevel:|」を「@<code>|3|」に変更します。

//list[][ファイル「config.yml」]{
# 本文でセクション番号を表示する見出しレベル
#secnolevel: @<b>{2}    @<balloon>{章 (Chapter) と節 (Section) にだけ番号をつける}
secnolevel: @<b>{3}     @<balloon>{項 (Subsection) にも番号をつける}
//}


=== 項を目次に含める

項(Subsection)を目次に出すには、「@<file>{config.yml}」の設定項目「@<code>|toclevel:|」を「@<code>|3|」に変更します。

//list[][ファイル「config.yml」]{
# 目次として抽出する見出しレベル
#toclevel: @<b>{2}      @<balloon>{（部と）章と節までを目次に載せる}
toclevel: @<b>{3}       @<balloon>{（部と）章と節と項を目次に載せる}
//}


==={subsec-parenttitle} [PDF] 項への参照に節タイトルを含める

項(Subsection)に番号がついていない場合、「@<code>|@@<nop>{}<secref>{...}|」で項を参照すると表示が番号なしの項タイトルだけになるので、ユーザはその項を探せません。

たとえば前の項のタイトルは「項を目次に含める」です。もし
//quote{
//noindent
詳しくは「4.5.7 項を目次に含める」を参照してください。
//}
と書かれてあれば、項番号を手がかりにして読者はその項を簡単に探せるでしょう。
しかし、もし項番号がなくて
//quote{
//noindent
詳しくは「項を目次に含める」を参照してください。
//}
//noindent
と書かれてると、手がかりがないので読者はその項を探すのに苦労するでしょう。

このように、本文の中で項を参照しているなら項に番号をつけたほうがいいです。

Starterでは別の解決策として、「@<code>|@@<nop>{}<secref>{...}|」で項(Subsection)を参照したときに親となる節(Section)のタイトルもあわせて表示する機能を用意しています。
たとえばこのように：
//quote{
//noindent
詳しくは「4.5 見出し」の中の「項を目次に含める」を参照してください。
//}

このような表示にするには、「@<file>{config-starter.yml}」の設定項目「@<code>|secref_parenttitle:|」を「@<code>|true|」に設定してください。

//list[][]{
  ## @@<nop>{}<secref>{}において、親の節のタイトルを含めるか？
  secref_parenttitle: true # trueなら親の節のタイトルを含める
//}

なお以前は、この値はデフォルトで「@<code>|true|」になっていました。
しかし「@<code>|@@<nop>{}<secref>{}|」での参照にページ番号がつくこと、また項タイトルにクローバーをつければ項であることがすぐ分かることから、現在ではデフォルトで「@<code>|false|」になっています。


=== 項タイトルの記号を外す

項(Subsection)のタイトル先頭につく記号（クローバー、クラブ）は、「@<code>{config-starter.yml}」でオン・オフできます。

//list[][ファイル「config-starter.yml」]{
  ## 項 (Subsection) タイトルの装飾
  ## （none: なし、symbol: 先頭にクローバー）
  subsection_decoration: @<b>{symbol}
//}


=== [PDF] 項タイトルの記号をクローバーから変更する

項(Subsection)のタイトル先頭につく記号は、「@<code>{sty/starter-heading.sty}」で次のように定義されています。

//list[][ファイル「sty/starter-heading.sty」]{
\newcommand{\starter@subsection@symbol}{@<b>|$\clubsuit$|}% クローバー
//}

これを変更するには、「@<file>{sty/mystyle.sty}」で上書きしましょう。

//list[][ファイル「sty/mystyle.sty」]{
%% 「\newcommand」ではなく「\renewcommand」を使うことに注意
\renewcommand{\starter@subsection@symbol}{@<b>|$\heartsuit$|}% ハート
//}



== 本

=== 本のタイトルや著者名を変更する

本のタイトルや著者名は、「@<file>{config.yml}」で設定できます。

//list[][ファイル「config.yml」]{
# 書名
@<b>{booktitle: |-}
  Re:VIEW Starter
  ユーザーズガイド
@<b>{subtitle: |-}
  便利な機能を一挙解説！

# 著者名。「, 」で区切って複数指定できる
@<b>{aut:}
  - name:    カウプラン機関極東支部
    file-as: カウプランキカンキョクトウシブ
//}

Starterでは、本のタイトルやサブタイトルを複数行で設定できます。
こうすると、大扉（タイトルページ）でも複数行で表示されます。


==={subsec-coverpdf} [PDF] 表紙や大扉や奥付となるPDFファイルを指定する

Starterでは、本の表紙や大扉（タイトルページ）や奥付となるPDFファイルを指定できます。
@<file>{config-starter.yml}で以下の項目を変更してください@<fn>{fn-2l1nn}。

//footnote[fn-2l1nn][これらの設定は、以前は@<file>{config.yml}で行っていましたが、現在は@<file>{config-starter.yml}で行うように変更されました。また@<file>{config.yml}に古い設定が残っているとコンパイルエラーになり、「古い設定が残っているので移行するように」というエラーメッセージが出ます。]

//list[][ファイル「@<file>{config-starter.yml}」]{
  frontcover_pdffile: cover_a5.pdf          @<balloon>{表紙}
  backcover_pdffile:  null                  @<balloon>{裏表紙}
  titlepage_pdffile:  null                  @<balloon>{大扉}
  colophon_pdffile:   null                  @<balloon>{奥付}
  #includepdf_option: "offset=-2.3mm 2.3mm" @<balloon>{位置を微調整する場合}
  includepdf_option:  null                  @<balloon>{通常は無指定でよい}
//}

いくつか注意点があります。

 * PDFファイルは、「@<file>{images/}」フォルダ直下に置いてください。
 * 画像ファイルは使用できません。必ずPDFファイルを使ってください。
 * 1つのPDFファイルにつき1ページだけにしてください。
   もしPDFファイルが複数ページを持つ場合は、「@<code>|cover.pdf<2>|」のように取り込むページ番号を指定してください（実験的機能）。
 * 複数のPDFファイルを指定するには、YAMLの配列を使って「@<code>|[file1.pdf, file2.pdf]|」のように指定します。
   「@<code>|,|」のあとには必ず半角空白を入れてください。
 * もし位置がずれる場合は、「@<code>|coverpdf_option:|」の値を調整してください（以前は微調整が必要でしたが、現在は必要ないはずです）。

なお表紙と裏表紙がつくのは電子用PDFファイルの場合のみであり、印刷用PDFファイルにはつかない（し、つけてはいけない）ので注意してください。
詳しくは@<secref>{02-tutorial|sec-pdftype}を参照してください。
これに対して大扉と奥付は、指定されれば印刷用PDFでも電子用PDFでもつきます。

//note[PNGやJPGの画像をPDFに変換する]{
macOSにてPNGやJPGをPDFにするには、画像をプレビュー.appで開き、メニューから「ファイル > 書き出す... > フォーマット:PDF」を選んでください。

macOS以外の場合は、「画像をPDFに変換」などでGoogle検索すると変換サービスが見つかります。
//}


=== [PDF] 表紙のPDFから塗り足しを除いて取り込む

表紙や裏表紙のPDFファイルを印刷所に入稿するには、通常のA5やB5に上下左右3mmずつを加えたサイズのPDFファイルを使います。
この上下左右3mmの部分を「塗り足し」といいます@<fn>{fn-lmc7a}。

//footnote[fn-lmc7a][塗り足しについては@<secref>{subsec-bleed}も参照してください。]

つまり印刷用の表紙や裏表紙は、塗り足しの分だけ縦横サイズが少し大きいのです。
そのため印刷用の表紙や裏表紙を電子用PDFに取り込むには、塗り足し部分を除いたうえで取り込む必要があります。

StarterではPDFファイル名の後ろに「@<code>|*|」をつけると、塗り足し部分を除いて取り込んでくれます。
PDFのページ番号も一緒に指定する場合は「@<code>|cover.pdf<2>*|」のように指定してください。

//list[][ファイル「@<file>{config-starter.yml}」]{
  frontcover_pdffile: frontcover_a5.pdf@<b>{*}  @<balloon>{塗り足し部分を取り除く}
  backcover_pdffile:  backcover_a5.pdf@<b>{*}   @<balloon>{塗り足し部分を取り除く}
  titlepage_pdffile:  titlepage_a5.pdf    @<balloon>{大扉は塗り足しなし}
  colophon_pdffile:   colophon_a5.pdf     @<balloon>{奥付は塗り足しなし}
//}

より正確には次のような動作をします。

 * PDFファイル名の最後に「@<code>|*|」がついてなければ、用紙サイズに合わせてPDFを拡大・縮小して、中央に配置します。
 * PDFファイル名の最後に「@<code>|*|」がついていると、拡大・縮小はせずに@<bou>{そのままの大きさで中央に配置}します。
   その結果、塗り足し部分だけが用紙からはみ出るので、あたかも塗り足し部分が取り除かれたように見えます。

//note[塗り足しつきで表紙を取り込むと上下に空きが入る理由]{
ファイル名の最後に「@<code>|*|」をつけない場合、用紙サイズに合わせてPDFを拡大または縮小しますが、縦横の比率は変えません。
そのため、PDFが用紙より縦長だと上下を揃えようとして左右に空きが入り、PDFが用紙より横長だと左右を揃えようとして上下に空きが入ります。

塗り足しのついたPDFファイルをそのまま取り込むと上下が少し空くのは、PDFの縦横サイズが塗り足しの分だけ用紙より横長になるからです。
//}


=== [PDF] 大扉のデザインを変更する

大扉（タイトルページ）のPDFファイルを指定しなかった場合は、デフォルトデザインの大扉がつきます。
このデザインは「@<file>{sty/mytitlepage.sty}」で定義されているので、デザインを変更したい場合はこのファイルを編集してください。
編集する前にバックアップを取っておくといいでしょう@<fn>{fn-iaa2p}。

//terminal{
$ @<userinput>{cp sty/mytitlepage.sty sty/mytitlepage.sty.original}
$ @<userinput>{vi sty/mytitlepage.sty}
//}

//footnote[fn-iaa2p][Gitなどでバージョン管理している場合は、バックアップする必要はありません。]


=== [PDF] 奥付のデザインを変更する

奥付のPDFファイルを指定しなかった場合は、デフォルトデザインの奥付がつきます。
このデザインは「@<file>{sty/mycolophon.sty}」で定義されているので、デザインを変更したい場合はこのファイルを編集してください。
編集する前にバックアップを取っておくといいでしょう@<fn>{fn-evcg1}。

//terminal{
$ @<userinput>{cp sty/mycolophon.sty sty/mycolophon.sty.original}
$ @<userinput>{vi sty/mycolophon.sty}
//}

//footnote[fn-evcg1][Gitなどでバージョン管理している場合は、バックアップする必要はありません。]


=== [PDF] 奥付を改ページしない

Starterでは、奥付は自動的に最終ページに配置されます（詳しくは@<secref>{06-bestpractice|subsec-colophonlastpage}を参照してください）。
この自動での配置を止めて手動でコントロールしたい場合は、次のどちらかを行ってください。

 * 「@<file>{sty/mycolopho.sty}」において、7行目付近にある「@<code>|\reviewcolophon|」の先頭に「@<code>|%|」をつけて「@<code>|%\reviewcolophon|」とする。
 * 「@<file>{sty/mystyle.sty}」に、「@<code>|\def\reviewcolophon{}|」という記述を追加する。

たとえば、最終ページの上半分に著者紹介と過去の著作一覧を表示し、下半分に奥付を表示したいとします。
その場合は奥付が自動的に改ページされないよう変更してから、あとがきを次のようにするといいでしょう。

//list[][ファイル「@<file>{contents/99-postface.re}」：あとがき]{
= あとがき
....文章....

//clearpage     @<balloon>{改ページ}
== 著者紹介
....紹介文....

 * 『著作1』
 * 『著作2』
//}


=== [PDF] 奥付に発行者と連絡先を記載する

「@<href>{https://gishohaku.dev, 技書博}」という技術系同人誌イベントでは、奥付に「発行者」と「連絡先」の記載が必要となりました@<fn>{fn-13udq}。
Starterでは、奥付に発行者と連絡先を載せる設定を用意しています。

#@#//footnote[fn-13udq][@<hlink>{https://esa-pages.io/p/sharing/13039/posts/115/7fbe936149a836eac678.html#%E5%A5%A5%E4%BB%98%E3%81%AE%E8%A8%98%E8%BC%89, https://esa-pages.io/p/sharing/13039/posts/115/7fbe936149a836eac678.html#奥付の記載}]
//footnote[fn-13udq][@<hlink>{https://esa-pages.io/p/sharing/13039/posts/115/7fbe936149a836eac678.html#%E5%A5%A5%E4%BB%98%E3%81%AE%E8%A8%98%E8%BC%89}]
#@#//footnote[fn-13udq][@<hlink>{https://esa-pages.io/p/sharing/13039/posts/115/7fbe936149a836eac678.html#%E5%A5%A5%E4%BB%98%E3%81%AE%E8%A8%98%E8%BC%89, @<tt>{https://esa-pages.io/p/sharing/13039/posts/115/7fbe936149a836eac678.html#奥付の記載}}]

//list[][ファイル「@<file>{config.yml}」]{
additional:
  - key:     発行者
    value:   xxxxx    @<balloon>{サークル名ではなく個人名（ペンネーム可）}
  - key:     連絡先
    value:
      - xxxxx@example.com          @<balloon>{メールアドレス（推奨）}
      - https://www.example.com/   @<balloon>{WebサイトURL}
      - "@xxxxx"          @<balloon>{Twitterアカウント（頭に '@' が必要）}
//}

連絡先にはいくつか補足事項があります。

 * 連絡先には複数の値が指定できます。技書博によればメールアドレスがお勧めだそうです。
 * 連絡先にURLが指定されると、自動的にリンクになります。
 * 連絡先にTwitterアカウントを指定するには、先頭に「@<code>|@|」をつけてください。
   またTwitterアカウントも自動的にリンクになります。
 * 発行者や連絡先は、奥付の中では印刷所名の直前に置かれます。
 * PDFの奥付にのみ表示されます。HTMLやePubへは未対応です。

なおこの設定には、発行者や連絡先以外の項目も追加できます。
もし奥付に表示したい項目があれば、ここに追加してください。


=== [PDF] 注意事項の文章を変更する

大扉（タイトルページ）の直後のページには、免責や商標に関する以下のような注意事項が書かれています。

//quote{
//noindent
■免責@<br>{}
本書は情報の提供のみを目的としています。@<br>{}
本書の内容を実行・適用・運用したことで何が起きようとも、それは実行・適用・運用した人自身の責任であり、著者や関係者はいかなる責任も負いません。

//blankline
//noindent
■商標@<br>{}
本書に登場するシステム名や製品名は、関係各社の商標または登録商標です。@<br>{}
また本書では、TM、®、© などのマークは省略しています。
//}

この文言を変更したい場合は、「@<file>{sty/mytitlepage.sty}」を編集してください。


=== [PDF] 注意事項の文章を出さない

大扉（タイトルページ）の裏ページにある注意事項の文章を出さないようにするには、次のどちらかを行ってください。

 * 「@<file>{sty/mytitlepage.sty}」において、「@<code>|\newcommand{\mytitlenextpage}|」を「@<code>|\newcommand{\@mytitlenextpage}|」に変更する。
 * 「@<file>{sty/mystyle.sty}」において、「@<code>|\let\mytitlenextpage=\undefined}|」という記述を追加する。



=={sec-index} 索引


=== [PDF] 用語のグループ化を文字単位にする

索引ページでは、用語が「あ か さ た な は ……」のように行単位でグループ化されます。
これを「あ い う え お か き ……」のように文字単位でグループ化するには、@<file>{config.yml}の「@<code>|makeindex_options: "-q -g"|」から「@<code>{-g}」を取り除いてください。


=== [PDF] 連続したピリオドのかわりに空白を使う

索引ページにて用語とページ番号との間は、デフォルトでは連続したピリオドで埋めています。
これを空白で埋めるよう変更するには、@<file>{sty/indexsty.ist}を編集してください。

//list[][@<file>{sty/indexsty.ist}]{
## 用語とページ番号との間をピリオドで埋める
#delim_0 "\\quad\\dotfill ~"
#delim_1 "\\quad\\dotfill ~"
#delim_2 "\\quad\\dotfill ~"

## 用語とページ番号との間を空白で埋める
delim_0 "\\quad\\hfill"
delim_1 "\\quad\\hfill"
delim_2 "\\quad\\hfill"
//}

なお@<file>{sty/indexsty.ist}の中の設定項目については、@<href>{http://tug.ctan.org/info/mendex-doc/mendex.pdf, mendexコマンドのマニュアル}を参照してください。
mendexコマンド（またはupmendexコマンド）のオプションについても記載されています。


=== [PDF] 用語見出しのデザインを変更する

索引ページの用語見出しは「■あ」「■か」のようになっています。
このデザインは@<file>{sty/starter-misc.sty}の「@<code>|\starterindexgroup|」で設定されています。
変更するには「@<code>|\starterindexgroup|」の定義を@<file>{sty/starter-misc.sty}から@<file>{sty/mystyle.sty}にコピーして、「@<code>|\newcommand|」を「@<code>|\renewcommand|」に変更して中身をカスタマイズしてください。

//list[][@<file>{sty/mystyle.sty}]{
\renewcommand{\starterindexgroup}[1]{%  % 索引グループ
  {%
    \bfseries%                   % 太字
    \gtfamily\sffamily%          % ゴシック体
    ■#1%                        % 例：`■あ`
  }%
}
//}

また@<file>{sty/indexsty.ist}を編集すると、別の@<LaTeX>{}マクロ名を指定できます。


=== [PDF] その他

 * 索引ページにおいて子要素の用語で使う「――」は、@<file>{sty/starter-misc.sty}の「@<code>|\starterindexplaceholder|」で定義されています。
 * 「@<code>|@@<nop>{}<term>{}|」で表示するフォントは、@<file>{sty/starter-misc.sty}の「@<code>|\starterterm|」で定義されています。
   デフォルトではゴシック体にで表示するように定義されています。
 * 用語の転送先を表す「→」を別の記号や文字列に変更するには、@<file>{sty/mystyle.sty}にたとえば「@<code>|\renewcommand{\seename}{\textit{see: }}|」のように書きます。



== Rakeタスク


=== デフォルトタスクを設定する

Starterでは、@<code>|rake|コマンドのデフォルトタスクを環境変数「@<em>{$RAKE_DEFAULT}」で指定できます。

//terminal[][rakeのデフォルトタスクを設定する]{
$ @<userinput>{rake}              @<balloon>{デフォルトではタスク一覧が表示される}
$ @<userinput>{@<b>{export RAKE_DEFAULT=pdf}}  @<balloon>{環境変数を設定}
$ @<userinput>{rake}              @<balloon>{「rake pdf」が実行される}
//}


=== 独自のタスクを追加する

Starterでは、ユーザ独自のRakeタスクを追加するためのファイル「@<file>{lib/tasks/mytasks.rake}」を用意しています。

//list[][ファイル「lib/tasks/mytasks.rake」]{
## 独自のタスクを追加する
desc "ZIPファイルを生成する"
task :zip do
  rm_rf "mybook"
  mkdir "mybook"
  cp_r ["README.md", "mybook.pdf"], "mybook"
  sh "zip -r9 mybook.zip mybook"
end
//}


=== コンパイルの前処理を追加する

Starterでは、任意の処理をコンパイルの前に実行できます。

//list[][ファイル「@<file>{lib/tasks/mytasks.rake}」]{
def my_preparation(config)        # 新しい前処理用関数
  print "...前処理を実行...\n"
end

PREPARES.unshift :my_preparation  # 前処理の先頭に追加
//}

これを使うと、たとえば以下のようなことができます。

 * 原稿ファイルをコピーし書き換える。
 * 複数の原稿ファイルを結合して1つにする。
 * 1つの原稿ファイルを複数に分割する。
