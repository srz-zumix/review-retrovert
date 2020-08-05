= 開発の背景

//abstract{
ここでは歴史の記録として、Re:VIEW Starterが開発された背景などを記しておきます。
個人的な忘備録として残すものであり、読まなくても本や同人誌の制作にはまったく支障はありません。
//}


#@#== Re:VIEW Starterについて
#@#
#@#Re:VIEW Starterは、「@<href>{Re:VIEW, https://reviewml.org/}」というドキュメント作成ツールを大幅に機能強化したものです。
#@#
#@#主なポイントを挙げます。
#@#
#@# * プロジェクト作成時に初期設定がGUIで行える
#@# * 見栄えのいいデザインをあらかじめ用意
#@# * インライン命令もブロック命令も入れ子にできる
#@# * 順序つき箇条書きが入れ子にでき、数字以外も使える
#@# * プログラムコード中の長い行を自動的に折り返す（太字も取消線もOK）
#@# * プログラムコードの行番号機能が豊富
#@# * 0とO、1とlが見分けやすいフォントを採用
#@# * 命令体系をシンプルで覚えやすいように整理
#@# * 範囲コメントを利用可能
#@# * いろんなところに気が利いている


==[notoc] 開発の経緯

Re:VIEWはver 2.4の頃、「A5サイズのPDFファイルが生成できない」「フォントサイズも10ptから変更できない」という致命的な問題を抱えていました。
つまりB5サイズでフォントが10ptの本しか作れなかったのです。

この頃はまだ、技術同人誌はB5サイズ10ptで作るのが主流だったので、Re:VIEWのこの制限はあまり問題にはなりませんでした。
しかし同人誌印刷ではB5サイズよりA5サイズのほうが割安なので、一部の人がA5サイズやより小さいフォントサイズでのPDF生成を模索し、そしてRe:VIEWの制限に苦しみました。

たとえば、フォントサイズを小さくしようとして格闘し、結果としてあきらめた人の証言を見てみましょう@<fn>{g6rdf}（@<img>{slide2}）。

//footnote[g6rdf][@<href>{https://www.slideshare.net/KazutoshiKashimoto/nagoya0927-release}のp.21とp.22。]

//image[slide2][フォントやページサイズを変更できなかった人の証言][scale=1.0]

この問題は、「@<em>{geometry.sty}」というスタイルファイルをオプションなしで読み込んでいることが原因です@<fn>{fn-ly58b}。
具体的は修正方法は@<href>{https://qiita.com/kauplan/items/01dee0249802711d30a6, Qiitaの記事}に書いています。
読めば分かりますが、かなり面倒です。

//footnote[fn-ly58b][簡単に書いてますけど、原因が@<em>{geometry.sty}であることを突き止めるのには多くの時間がかかり、正月休みが潰れました。今でも恨んでます。この苦労を知らずに「Re:VIEWでは昔からA5のPDFが簡単に生成できた」と言い張る歴史修正者にはケツバットの刑を与えてやりたいくらいです。]

この不具合はバグ報告したものの、開発陣の反応は芳しくなく、すぐには修正されなさそうでした@<fn>{fn-mxd28}。
当時は「技術書典」という同人イベントの開催が迫っていたので、これは困りました。
仕方ないのでRe:VIEW側での修正に期待せず、誰でも簡単にA5サイズの同人誌が作れるための別の方法を考えることにしました。

//footnote[fn-mxd28][実際、Re:VIEW Ver 2の間は修正されず、修正されたのはVer 3になってからでした。当然、技術書典には間に合いませんでした。]

そうした経緯で誕生したのが、Re:VIEW Starterです。
Starterでは初期設定がGUIでできる簡単さが売りのひとつですが、もともとはA5サイズ9ptの同人誌を簡単に作れることが開発動機だったのです。


==[notoc] 開発の転機

Starterは、当初はRe:VIEWとの違いが大きくならないよう、GUIで設定した状態のプロジェクトをダウンロードできるだけに留めていました。
つまりユーザが手作業で設定するのを、GUIで簡単に設定できるようにしただけでした。

しかしRe:VIEWは、ドキュメント作成ツールとしての基本機能が足りておらず、そのうえ開発速度が遅くて技術書典といったイベントには新機能追加が間に合いません。
またバグ報告をしても「仕様だ」と回答されたり、互換性を理由に却下されたり（けど他の人が報告すると取り入れられたり）といったことが積み重なって、ある日を境にStarterで独自の機能を追加することを決心しました。

そこからは少しずつRe:VIEWの機能を上書きし、足りない機能を追加していきました。

現在のStarterでは、Re:VIEWのソースコードを広範囲に上書きしています@<fn>{fn-8309s}。
特にパーサの大部分はStarter側で上書きしています。
このおかげで、インライン命令やブロック命令を入れ子対応にしたり、箇条書きの機能を大きく拡張したりできています。

Re:VIEWとのかい離はずいぶんと大きくなりました。

//footnote[fn-8309s][実はRe:VIEWのソースコードを広範囲に上書きしているせいで、ベースとなるRe:VIEWのバージョンを2.5から上げられていません。しかしRe:VIEWの開発速度が遅く目ぼしい新機能は追加されてないので、デメリットはありません。]


==[notoc] 開発の障害

Starterを開発するうえで大きな障害になったのが、@<LaTeX>{}と、Re:VIEWのコード品質です。

「@<LaTeX>{}」はフリーの組版ソフトウェアであり、Re:VIEWやStarterがPDFファイルを生成するときに内部で使っています。
@<LaTeX>{}は出力結果がとてもきれいですが、使いこなすには相当な知識が必要です。

特に@<LaTeX>{}のデバッグは困難を極めます。
エラーメッセージがろくに役立たないせいでエラーを見ても原因が分からない、どう修正すればいいかも分からない、直ったとしてもなぜ直ったのか分からない、分からないことだらけです。
この文章を読んでいる人にアドバイスできることがあるとすれば、「@<LaTeX>{}には関わるな！」です。

またRe:VIEWのコード品質の悪さも、大きな障害となりました。
ソースコードを読んでも何を意図しているのか理解しづらい、コードの重複があちこちにある、パーサで行うべきことをBuilderクラスで行っている、…など、基礎レベルでのリファクタリングがされていません。
信じたくはないでしょうが、同じような感想を持った人が他にもいたので紹介します。

//noindent
@<href>{https://np-complete.gitbook.io/c86-kancolle-api/atogaki}:
//quote{
っと上の文章を書いてから2時間ほどRe:VIEWのコードと格闘していたんですが、なんですかこのクソコードは・・・
これはマジでちょっとビビるレベルのクソコードですよ。
夏コミが無事に終わったら冬に向けてRe:VIEWにプルリク送りまくるしかないと思いました。
//}

「クソコード」は言い過ぎですが、そう言いたくなる気持ちはとてもよく分かります。

また、パースしたあとに構文木を作っていないのは、Re:VIEWの重大な設計ミスといえるでしょう。
Re:VIEWやMarkdownのようなドキュメント作成ツールでは、一般的に次のような設計にします。

 1. パーサが入力テキストを解析して、構文木を作る。
 2. 構文木をたどって必要な改変を行う。
 3. Visitorパターンを使って、構文木をHTMLや@<LaTeX>{}のコードに変換する。

このような設計であれば、機能追加は容易です。
特に、HTMLや@<LaTeX>{}のコードを生成するより@<bou>{前}にすべての入力テキストがパース済みなので、たとえ入力テキストの@<bou>{最後}に書かれたコマンドであろうと、それを認識して@<bou>{先頭}のコードを柔軟に変更できます。

しかしRe:VIEWは構文木を作らず、パースしながらHTMLや@<LaTeX>{}のコードに変換するため、しなくてもいいはずのハックが必要となることがあります。

Starterは将来的にRe:VIEWのパーサをすべて上書きして、構文木を生成するタイプのパーサに置き換えることになるでしょう。


==[notoc] 開発方針の違い

Re:VIEWとStarterでは、開発方針に大きな違いがあります。

===[notoc] 開発速度

Re:VIEWでは、リリースが年3回と決まっています。
またリリース時期も（過去を見る限り）2月末、6月末、10月末に固定されています。
そのため「次の技術書典までにこの新機能が必要だ」と思っても、固定されたリリース時期にならないと新機能はリリースされません。
言い方を変えると、ユーザが必要とする開発速度についてこれていません。

Starterは主に、技術書典をはじめとした同人イベントに合わせて新機能が開発されます。
また2〜3週間ごとにリリースされるので、新機能の追加とバグ修正が急ピッチで進みます。
つまり、ユーザが必要とする速度で開発されています。

===[notoc] 機能選定

Re:VIEWは商業誌での利用実績が多いこともあって、「@<href>{https://www.w3.org/TR/jlreq/ja/, 日本語組版処理の要件}」への対応が重視されます。
そのため@<href>{jlreqクラスファイル, https://github.com/abenori/jlreq}が標準でサポートされており、少なくない開発リソースがその対応に割かれています。
そのせいか、「範囲コメントを実装する」「インライン命令やブロック命令を入れ子に対応させる」「順序つき箇条書きで数字以外を使えるようにする」などの基本機能が、未だに実装されていません。

しかし「日本語組版処理の要件」は、読んでみると分かりますが、重箱の隅をつつくような内容がほとんどです。
プロユースでは必要なのかもしれませんが、同人誌では「禁則処理がきちんとできていれば充分」というユーザがほとんどでしょう。
開発リソースをそんな細かいところに割くよりも、もっとユーザが必要とする機能の開発に割くべきです。

Starterでは日本語組版の細かい要件は気にせず、ユーザが必要とする機能を重点的に開発しています。
たとえば、範囲コメントを実装したり、インライン命令やブロック命令を入れ子に対応させたり、順序つき箇条書きでアルファベットも使えるようにしたり、章や節のタイトルを見栄えのいいデザインにしたりといった、ユーザにとって必要な機能を優先して開発しています@<fn>{fn-jnik5}。

//footnote[fn-jnik5][ここに挙げた機能のうち、見た目のデザインを変更するのは（@<LaTeX>{}の知識さえあれば）ユーザでも変更できますし、実際にTechboosterテンプレートでは見た目のデザインを変更しています。しかしそれ以外の機能はRe:VIEWのソースコードを変更しなければ実現できず、ユーザが簡単に行えることではありません。]

===[notoc] バグ対応

今まで、Re:VIEWには約20個ぐらいのバグ報告やPull Requestを出しました。
取り入れられたものも多いですが、理不尽な理由で拒絶されたものも多いです
。

===== 明らかなバグを仕様だと言い張る

たとえば、Re:VIEWでは箇条書きの項目が複数行だと勝手に結合されるというバグがあります。

//list[][サンプル]{
 * AA AA
   BB BB
   CC CC
//}



//sampleoutputbegin[表示結果]

 * AA AABB BBCC CC

//sampleoutputend



「AABB」や「BBCC」のように英単語が結合されていますよね？
どう見てもRe:VIEWのバグなのですが、@<hlink>{https://github.com/kmuto/review/issues/1312, 報告}しても「これは仕様だ」と言い張るんです。
しかも「なぜそのような書き方をするんだ？一行に書けばいいではないか」と言われる始末。
かなり意味不明な対応をされました。

Starterではこのバグは修正しています（当然です）。

===== 提案を却下しておきながら次のバージョンで釈明なく取り入れる

Re:VIEW 2.xでは、@<LaTeX>{}スタイルファイルが「@<file>{sty/reviewmacro.sty}」しかなく、カスタマイズするにはこのファイルを編集するのが一般的でした。
しかしこの方法には問題があります。

 * 「@<file>{sty/reviewmacro.sty}」を直接編集すると、Re:VIEWのバージョンアップをするときに困る。
 * 自分でスタイルファイルを追加できるが、そのためには設定ファイルの項目を変更する必要があり、初心者には敷居が高い（どの項目をどう変更すればいいか知らないため）。

そこで、あらかじめ空のスタイルファイルを用意し、ユーザのカスタマイズはそのファイルの中で行うことを@<hlink>{https://github.com/kmuto/review/issues/917, 提案}しました。
Starterでいうと「@<file>{sty/mystyle.sty}」のことですね。
実装は簡単だし、問題の解決策としてとても妥当な方法です。

しかしこの提案は、あーだこーだと理由をつけられて却下されました（これに限らず、初心者への敷居を下げるための提案は却下されることが多い印象です）。
仕方ないので、Starterでは初期の頃から独自に空のスタイルファイルを提供していました。

ところが、なんとRe:VIEW 3.0でこの機能が取り込まれていたのです！
「提案が通ったならそれでいいじゃないか」と心ないことを言う人もいるでしょうけど、いろいろ理由をつけて提案を却下しておきながら、何の釈明もなくしれーっと取り込むのは、却下されたほうとしてはたまったものではありません。
不満が残るのは当たり前です。

===== 仲のいい人とそうでない人とで露骨に態度を変える

昔のRe:VIEWでは、「@<code>|//list|」においてキャプション（説明文）を指定しなくても言語指定をすると、本文とプログラムリストの間が大きく空いてしまうというバグがありました。
たとえばこのように書くと：

//list[][サンプル]{
@<b>|//list[][][ruby]|{
def fib(n)
  return n <= 1 ? n : fib(n-1) : fib(n-2)
end
/@<nop>$$/}
//}



//noindent
@<img>{bug913}の下のように表示されていました。

//image[bug913][本文とプログラムリストの間が大きく空いてしまう（下）][scale=0.7,border=on]

この現象は、空文字列がキャプションとして使われるため、その分の空行が空いてしまうことが原因です。
そこで、キャプションが空文字列のときは表示しないようにする修正を@<hlink>{https://github.com/kmuto/review/pull/913, 報告}しました。

しかしこのバグ報告も、後方互換性のために却下されました。
「出力結果が変わってしまうような変更は、たとえバグ修正だとしても、メジャーバージョンアップ以外では受けつけられない」というのが理由でした。
こんな明白なバグの互換性なんかいらないはずだと思ったので、粘って交渉したのですが、互換性を理由に頑なに拒まれました。

ところが、開発者と仲のいい別の人が「やはりバグではないか？」とコメントした途端、メジャーバージョンアップでもないのに修正されました。
見事な手のひら返しです。

「出力結果が変わってしまう変更は、たとえバグ修正でも（メジャーバージョンアップ以外では）受けつけられない。それが組版ソフトだ」という理由でさんざん拒絶しておいて、いざ別の人が言及するとすぐに修正する。
出力結果が変わってしまう修正だというのに！

大事な点なので強調しますが、@<B>{出力結果が変わる変更はダメと言って拒絶しておきながら、別の人が「やはりバグでは？」と言うと出力結果が変わる変更でもあっさり行うという、露骨な態度の違い}。
よく平気でこんなことできるなと逆に感心しました。

//blankline

こんなことが積み重なったので、もうバグ報告も機能提案もしないことにしました。
Re:VIEWのコードは品質が良くないので、ソースコードを読んでいると細かいバグがちょこちょこ見つかりますが、もうシラネ。

またRe:VIEWのリリースノートを見ると、Starterの機能がRe:VIEWの新機能として取り込まれているのを見かけます。
つまり、@<B>{Re:VIEWに新機能提案しても通らないけど、Starterに機能を実装するとRe:VIEWに取り込まれる可能性が高い}ということです。
こちらはバグ報告や提案が変な理由で却下されてストレスが溜まることから解放されるし、Re:VIEW側はStarterが先行実装した機能を選んで取り込めばいいし、Win-Winで、これでいいのだ。


==[notoc] 今後の開発

 * Starterは、将来的にRe:VIEWのソースコードをすべて上書きするでしょう。
   @<B>{大事なのはユーザが書いた原稿であって、Re:VIEWでもStarterでもありません}。
   たとえRe:VIEWのソースコードをすべて捨てたとしても、ユーザの原稿は使えるようになるはずです。

 * 設定は、今は設定ファイルを手作業で変更していますが、これはGUIによる設定に置き換わるでしょう。
   そのため設定ファイルの互換性はなくなる可能性が高いです。

 * PDF生成のための組版ツールとして、@<LaTeX>{}以外にBibliostyleをサポートしたいと考えています。
   ただしBibliostyleプロジェクトが独自のドキュメント作成ツールを開発中なので、Bibliostyleを必要とする人はそちらを使うだろうから、Starterでの優先順位は高くなくてもいいかなと思っています。

 * 同人イベントがオンラインに移行することから、PDFよりePubの需要が高くなるでしょう。
   今のStarterはePub対応が弱いので、強化する必要があります。

 * 印刷物での配布が減るので、カラー化がいっそう進むでしょう。
   Starterはコードハイライトができないので、対応を急ぐ必要があります。

 * Visual Studio Codeでの執筆を支援するプラグインが必要とされるでしょう。
   そのための本を買ったけど、積ん読のままです。

 * Markdownファイルの対応は、パーサを書き換えたあとで検討します。

 * 諸般の事情によりGitリポジトリを公開していないので、公開できるよう準備を進めます。