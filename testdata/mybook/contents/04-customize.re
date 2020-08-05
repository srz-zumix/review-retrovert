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

たとえば次の例では、新しいブロック命令「@<code>|//blockquote{ ... //}|」を追加しています。

//list[][ファイル「review-ext.rb」]{
module ReVIEW

  ## ブロック命令「//blockquote」を宣言（引数は0〜1個）
  @<b>{Compiler.defblock :blockquote, 0..1}

  ## LaTeX用の定義
  @<b>{class LATEXBuilder}
    ## 入れ子を許す場合
    @<b>{def on_blockquote(arg=nil)}
      if arg.present?
        puts "\\noindent"
        puts escape(arg)
      end
      puts "\\begin{quotation}"
      yield
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
    @<b>{def on_blockquote(arg=nil)}
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

//tsize[|latex||ccl|]
//table[tbl-rlsli][本文幅の推奨値（タブレット向けを除く）]{
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
\addtolength{\textheight}{@<b>|2Cvs|}   % 本文の高さを2行分増やす
//}

通常は、このような変更は必要ないはずです。


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

Re:VIEWやStarterでは、「@<code>|//note|」以外にも「@<code>|//info|」や「@<code>|//warning|」が使えます（詳しくは@{03-syntax|subsec-miniblock}を見てください）。

これらのデザインを変更するには、「@<file>{sty/mystyle.sty}」にたとえば次のように書いてください。

//list[][ファイル「@<file>{sty/mystyle.sty}」]{
%% 「//warning」のデザインを変更する
\renewenvironment{starterwarning}[1]{%
  \addvspace{1.0\baselineskip}% 1行分空ける
  \begin{oframed}%            % 枠線で囲む
    \ifempty{#1}\else%        % 引数（タイトル）があれば
      \noindent%              % 字下げせずに
      {\headfont\large%       % 太字のゴシック体で大きめに表示
        《警告》#1}%          % 先頭に 《警告》 をつける
      \par\smallskip%         % 縦方向に少しスペースを空ける
    \fi%
}{%
  \end{oframed}%              % 枠線による囲みの終わり
  \addvspace{1.0\baselineskip}% 1行分空ける
}
//}

次はもっと派手なデザインのサンプルです。
どんなデザインかは自分で確かめてください。

//list[][ファイル「@<file>{sty/mystyle.sty}」]{
%% 「//info」のデザインを変更する
\usepackage{ascmac}
\renewenvironment{starterinfo}[1]{%
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

//table[tbl-8jedm][商業誌のフォントサイズと本文幅]{
書籍名@<xsmall>{（出版社）}	各種サイズ
--------------------
@<xsmall>{『リーダブルコード』}@<xxsmall>{（オライリー・ジャパン）}	@<xsmall>{A5、9pt、38文字}
@<xsmall>{『ゼロから作るDeep Learning』}@<xxsmall>{（オライリー・ジャパン）}	@<xsmall>{A5、9pt、38文字}
@<xsmall>{『達人に学ぶSQL徹底指南書 第2版』}@<xxsmall>{（翔泳社）}	@<xsmall>{A5、9pt、38文字}
@<xsmall>{『アジャイル・サムライ』}@<xxsmall>{（オーム社）}		@<xsmall>{A5、10pt、36文字}
@<xsmall>{『オブジェクト指向UIデザイン』}@<xxsmall>{（技術評論社）}	@<xsmall>{A5、9pt、35文字}
@<xsmall>{『現場で役立つシステム設計の原則』}@<xxsmall>{（技術評論社）}		@<xsmall>{A5、10pt、33文字}
@<xsmall>{『独習プログラマー』}@<xxsmall>{（日経BP社）}		@<xsmall>{A5、10pt、34文字}
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

@<file>{config-starter.yml}の「@<code>|caption_needspace:|」がたとえば「@<code>|4.6zh|」であれば、プログラムリストの説明文を表示する前に全角4.6文字分の高さのスペースがあるかを調べ、なければ改ページします。
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

プログラムコードに枠線をつける・つけないを設定するには、次の設定を変更してください。

//list[][ファイル「config-starter.yml」]{
  ## プログラム（//list）を枠で囲むならtrue、囲まないならfalse
  program_border: true
//}

プログラムコードがページをまたいだときは、枠線があったほうが分かりやすいです。
詳しくは@<secref>{06-bestpractice|subsec-programborder}を見てください。



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

指定できる値は「@<code>{config-starter.yml}」の中に書かれています。


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


==={subsec-newpagepersec} [PDF] 節ごとに改ページする

初心者向けの入門書では、節(Chapter)ごとに改ページするデザインが好まれます。
Starterでこれを行うには、「@<file>{confit-starter.sty}」で設定項目「@<code>|section_newpage:|」を「@<code>|true|」に設定します。

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
#secnolevel: @<b>{2}     # 章 (Chapter) と節 (Section) にだけ番号をつける
secnolevel: @<b>{3}      # 項 (Subsection) にも番号をつける
//}


=== 項を目次に含める

項(Subsection)を目次に出すには、「@<file>{config.yml}」の設定項目「@<code>|toclevel:|」を「@<code>|3|」に変更します。

//list[][ファイル「config.yml」]{
# 目次として抽出する見出しレベル
#toclevel: @<b>{2}       # （部と）章と節までを目次に載せる
toclevel: @<b>{3}        # （部と）章と節と項を目次に載せる
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

項(Subsection)のタイトル先頭につく記号は、「@<code>{sty/starter.sty}」で次のように定義されています。

//list[][ファイル「sty/starter.sty」]{
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
((*booktitle: |-*))
  Re:VIEW Starter
  ユーザーズガイド
((*subtitle: |-*))
  便利な機能を一挙解説！

# 著者名。「, 」で区切って複数指定できる
((*aut:*))
  - name:    カウプラン機関極東支部
    file-as: カウプランキカンキョクトウシブ
//}

Starterでは、本のタイトルやサブタイトルを複数行で設定できます。
こうすると、大扉（タイトルページ）でも複数行で表示されます。


==={subsec-coverpdf} [PDF] 表紙を指定する

大扉（タイトルページ）ではなく、本の表紙を指定するには、「@<file>{config.yml}」の最後のほうにある設定項目「@<code>|coverpdf_files:|」にPDFファイル名を指定します。

//list[][ファイル「config.yml」]{
  coverpdf_files: @<b>{[cover_a5.pdf]}         @<balloon>{表紙}
  backcoverpdf_files: []                 @<balloon>{裏表紙}
  coverpdf_option: "offset=-0.0mm 0.0mm" @<balloon>{位置を微調整}
//}

ポイントは次の通りです。

 * 画像ファイルは使用できません。必ずPDFファイルを使ってください。
 * PDFファイルは、「@<file>{images/}」フォルダ直下に置いてください。
 * 複数のPDFファイルを指定するには、「@<code>|[file1.pdf, file2.pdf]|」のように指定します。
   「@<code>|,|」のあとには必ず半角空白を入れてください。
 * 裏表紙があれば「@<code>|backcoverpdf_files:|」に指定ます。
 * 位置がずれる@<fn>{fn-oq6uz}場合は、「@<code>|coverpdf_option:|」の値を調整してください。

//footnote[fn-oq6uz][@<LaTeX>{}に詳しい人向け：取り込んだPDFファイルの位置がずれるのは、フォントサイズが10pt@<bou>{ではない}ときです。このとき@<file>{jsbook.cls}では@<code>{\mag}の値を@<code>{1.0}以外に変更するので、それが@<file>{pdfpages}パッケージに影響します。一時的に@<code>{\mag}を@<code>{1.0}にしてPDFファイルを取り込む方法は分かりませんでした。]

なお表紙がつくのは、電子用PDFファイルの場合のみです。
印刷用PDFファイルにはつかない（し、つけてはいけない）ので注意してください。
詳しくは@<secref>{02-tutorial|sec-pdftype}を参照してください。

//note[PNGやJPGの画像をPDFに変換する]{
macOSにてPNGやJPGをPDFにするには、画像をプレビュー.appで開き、メニューから「ファイル > 書き出す... > フォーマット:PDF」を選んでください。

macOS以外の場合は、「画像をPDFに変換」などでGoogle検索すると変換サービスが見つかります。
//}



=== [PDF] 大扉のデザインを変更する

大扉（タイトルページ）のデザインは、「@<file>{sty/mytitlepage.sty}」で定義されています。
大扉のデザインを変更すには、このファイルを変更してください。
変更する前に、バックアップを取っておくといいでしょう@<fn>{fn-iaa2p}。

//terminal{
$ @<userinput>{cp sty/mytitlepage.sty sty/mytitlepage.sty.original}
$ @<userinput>{vi sty/mytitlepage.sty}
//}

//footnote[fn-iaa2p][もちろん、Gitでバージョン管理している場合はバックアップする必要はありません。]


=== [PDF] 注意書きの文章を変更する

大扉（タイトルページ）の裏のページには、免責事項や商標に関する注意書きが書かれています。
この文言を変更したい場合は、「@<file>{sty/titlepage.sty}」を編集してください。

#@#//quote{
#@#■免責
#@#本書は情報の提供のみを目的としています。
#@#本書の内容を実行・適用・運用したことで何が起きようとも、それは実行・適用・運用した人自身の責任であり、著者や関係者はいかなる責任も負いません。
#@#
#@#■商標
#@#本書に登場するシステム名や製品名は、関係各社の商標または登録商標です。
#@#また本書では、TM、®、© などのマークは省略しています。
#@#//}


=== [PDF] 奥付のデザインを変更する

奥付のデザインは、「@<file>{sty/mycolophon.sty}」で定義されています。
奥付のデザインを変更するには、このファイルを変更してください。
変更する前に、バックアップを取っておくといいでしょう@<fn>{fn-evcg1}。

//terminal{
$ @<userinput>{cp sty/mytitlepage.sty sty/mytitlepage.sty.original}
$ @<userinput>{vi sty/mytitlepage.sty}
//}

//footnote[fn-evcg1][もちろん、Gitでバージョン管理している場合はバックアップする必要はありません。]



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
