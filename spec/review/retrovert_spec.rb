require "spec_helper"

outpath = File.join(File.dirname(__FILE__), '../../tmp/rspec')

RSpec.describe ReVIEW::Retrovert do
  it "has a version number" do
    expect(ReVIEW::Retrovert::VERSION).not_to be nil
  end
end

RSpec.describe 'command test', type: :aruba do
  let(:config_yaml) { File.join(File.dirname(__FILE__), '../../testdata/mybook/config.yml') }

  context 'help' do
    before(:each) { run_command('bundle exec review-retrovert help') }
    it { expect(last_command_started).to be_successfully_executed }
  end

  context 'convert mybook' do
    before(:each) do
      Aruba.configure { |c| c.exit_timeout = 30 }
    end
    before(:each) { run_command("review-retrovert convert --preproc --tabwidth 4 --ird -f #{config_yaml} #{outpath}") }
    it 'result' do
      expect(last_command_started).to be_successfully_executed
      expect(last_command_started).to have_output(/.*replace starter inline command.*/)
      expect(last_command_started).to have_output(/.*replace starter block command.*/)
    end
  end

  context 'convert no preproc' do
    before(:each) { run_command("review-retrovert convert --tabwidth 4 #{config_yaml} tmp") }
    it 'result' do
      expect(last_command_started).to be_successfully_executed
      expect(last_command_started).not_to have_output(/INFO.*: preproc/)
    end
  end

end

RSpec.describe 'convert result' do

  let(:file00) { File.join(outpath, '00-preface.re') }
  let(:file01) { File.join(outpath, '01-install.re') }
  let(:file02) { File.join(outpath, '02-tutorial.re') }
  let(:file03) { File.join(outpath, '03-syntax.re') }
  let(:file04) { File.join(outpath, '04-customize.re') }
  let(:file05) { File.join(outpath, '05-faq.re') }
  let(:file06) { File.join(outpath, '06-bestpractice.re') }
  let(:file91) { File.join(outpath, '91-compare.re') }
  let(:file92) { File.join(outpath, '92-filelist.re') }
  let(:file93) { File.join(outpath, '93-background.re') }
  let(:file99) { File.join(outpath, '99-postface.re') }
  let(:root)   { File.join(outpath, 'r0-root.re') }
  let(:inner)  { File.join(outpath, 'r0-inner.re') }
  let(:config) { File.join(outpath, 'config.yml') }
  let(:retrovert_config) { File.join(outpath, 'config-retrovert.yml') }
  let(:custom_sty) { File.join(outpath, 'sty/review-custom.sty') }
  let(:ird_sty)    { File.join(outpath, 'sty/ird.sty') }
  let(:review_ext) { File.join(outpath, 'review-ext.rb') }

  context 'config result' do

    context 'config' do
      subject(:config_text) { File.open(config).read() }

      it 'chapterlink' do
        expect(config_text).not_to be_match(/^chapterlink: .*/)
      end

      it 'words_file' do
        expect(config_text).to be_match(/^words_file:\s*.*\.csv.*/)
      end

    end

    context 'retrovert config' do
      subject(:config_text) { File.open(retrovert_config).read() }

      it 'chapterlink' do
        expect(config_text).to be_match(/^chapterlink: null/)
      end

    end

  end

  context 'contents result' do

    it 'file exist' do
      expect(File).to exist(file00)
      expect(File).to exist(file01)
      expect(File).to exist(file02)
      expect(File).to exist(file03)
      expect(File).to exist(file04)
      expect(File).to exist(file05)
      expect(File).to exist(file06)
      expect(File).to exist(file91)
      expect(File).to exist(file92)
      expect(File).to exist(file93)
      expect(File).to exist(file99)
    end

    it 'inline command delete' do
      expect(File).to exist(file03)
      text = File.open(file03).read()
      expect(text).not_to be_include('@<userinput>{')
      expect(text).not_to be_include('@<small>{')
      expect(text).not_to be_include('@<xsmall>{')
      expect(text).not_to be_include('@<xxsmall>{')
      expect(text).not_to be_include('@<large>{')
      expect(text).not_to be_include('@<xlarge>{')
      expect(text).not_to be_include('@<xxlarge>{')
      expect(text).not_to be_include('@<weak>{')
      expect(text).not_to be_include('@<nop>{')
    end

    it 'inline command replace' do
      expect(File).to exist(file03)
      text = File.open(file03).read()
      expect(text).not_to be_include('@<secref>{')
      expect(text).to     be_include('@<hd>{')
      expect(text).not_to be_include('@<file>{')
      expect(text).to     be_include('@<kw>{')
      expect(text).not_to be_include('@<hlink>{')
      expect(text).to     be_include('@<href>{')
      expect(text).not_to be_include('@<B>{')
      expect(text).to     be_include('@<strong>{')
    end

    it 'LaTex inline command replace' do
      expect(File).to exist(file05)
      text = File.open(file05).read()
      expect(text).not_to be_include('@<LaTeX>{}')
      expect(text).to     be_include('LaTeX')
    end

    it 'block comaptible command replace with options' do
      expect(File).to exist(file02)
      text = File.open(file02).read()
      expect(text).not_to be_match(/^\/\/terminal/)
      expect(text).not_to be_match(/^\/\/cmd\[.*?\]/)
      expect(text).to     be_match(/^\/\/cmd{/)
    end

    it 'block comaptible command replace with options and inner text go outside' do
      expect(File).to exist(file99)
      text = File.open(file99).read()
      expect(text).not_to be_match(/^\/\/sideimage/)
      expect(text).to     be_match(/^\/\/image\[tw-icon\]\[\s*\]{\R\/\/}/)
    end

    # it 'block command replace exclude options' do
    #   expect(File).to exist(file99)
    #   text = File.open(file99).read()
    #   expect(text).not_to be_match(/^\/\/sideimage/)
    #   expect(text).to     be_match(/^\/\/image/)
    # end

    it 'block command replace with options' do
      expect(File).to exist(file02)
      text = File.open(file02).read()
      expect(text).not_to be_match(/^\/\/abstract/)
      expect(text).to     be_match(/^\/\/lead/)
    end

    unless Gem::Version.new(ReVIEW::VERSION) >= Gem::Version.new('5.0.0')
      it 'nested block command' do
        expect(File).to exist(file01)
        text = File.open(file01).read()
        expect(text).not_to be_match(/^\/\/}\R*^\/\/}/m)

        expect(File).to exist(file03)
        text = File.open(file03).read()
        # expect(text).not_to be_match(/^\/\/}\R*^\/\/}/m)
        expect(text).to     be_match(/^\/\/table\[tbl-xthfx\]/)
      end
    end

    # it 'nested block command exclude {}' do
    #   expect(File).to exist(file06)
    #   text = File.open(file06).read()
    #   expect(text).not_to match(/^#@#\/\/footnote/)
    # end

    it 'nested inline command' do
      expect(File).to exist(file01)
      text = File.open(file01).read()
      expect(text).not_to be_include('|@@<b>{}')
      expect(text).not_to be_include('|@@<b>$$')
      expect(text).not_to be_include('|@@<b>||')
      expect(text).not_to be_include('{@@<b>{}')
      expect(text).not_to be_include('{@@<b>$$')
      expect(text).not_to be_include('{@@<b>||')
      expect(text).not_to be_include('$@@<b>{}')
      expect(text).not_to be_include('$@@<b>$$')
      expect(text).not_to be_include('$@@<b>||')
    end

    it 'empty id set to' do
      expect(File).to exist(file05)
      text = File.open(file05).read()
      expect(text).not_to be_match(/^\/\/list\[[^\[\]]*?\]{/)
      expect(text).to     be_match(/^\/\/list\[starter_auto_id_list_0\]\[.*?\]{/)
    end

    it 'fix lack options' do
      expect(File).to exist(file04)
      text = File.open(file04).read()
      expect(text).not_to be_match(/^\/\/list{$/)
      expect(text).to     be_match(/^\/\/list\[starter_auto_id_list_[0-9]+\]\[\]{/)
    end

    it 'sampleoutputbegin' do
      expect(File).to exist(file06)
      text = File.open(file06).read()
      expect(text).not_to be_match(/^\/\/sampleoutputbegin\[.*?\]/)
      expect(text).not_to be_match(/^\/\/sampleoutputend/)
      expect(text).to     be_match(/^#@#\/\/sampleoutputbegin\[.*?\]/)
      expect(text).to     be_match(/^#@#\/\/sampleoutputend/)
    end

    it 'block comment in sampleout' do
      expect(File).to exist(file02)
      text = File.open(file02).read()
      expect(text).not_to be_match(/^#@#\/\/sampleoutputbegin.*?^#@\++.*^#@-+.*?^#@#\/\/sampleoutputend/m)
    end

    context 'syntax' do
      subject(:text) { File.open(file03).read() }

      context 'block command delete' do
        it 'vspace' do
          expect(text).not_to be_match(/^\/\/vspace/)
        end
        it 'needvspace' do
          expect(text).not_to be_match(/^\/\/needvspace/)
        end
        it 'clearpage' do
          expect(text).not_to be_match(/^\/\/clearpage/)
        end
        it 'flushright' do
          expect(text).not_to be_match(/^\/\/flushright/)
        end
        it 'centering' do
          expect(text).not_to be_match(/^\/\/centering/)
        end
        it 'noindent' do
          expect(text).not_to be_match(/^\/\/noindent/)
        end
        it 'paragraphend' do
          expect(text).not_to be_match(/^\/\/paragraphend/)
        end
      end

      context 'starter list expand to emlist' do
        it 'talklist' do
          expect(text).not_to be_match(/^\/\/talklist\[.*\]/)
          expect(text).not_to be_match(/^\/\/talk\[.*\]/)
          expect(text).not_to be_match(/^\/\/t\[.*\]/)
          expect(text).to     be_match(/^不可能なことを言い立てるのは貴官の方だ。それも安全な場所から動かずにな。/)
        end

        it 'talk_shortcuts' do
          expect(text).not_to be_match(/^\/\/indepimage\[b1\]/)
          expect(text).not_to be_match(/^\/\/indepimage\[g1\]/)
        end

        it 'desclist' do
          expect(text).not_to be_match(/^\/\/desclist\[.*\]/)
          expect(text).not_to be_match(/^\/\/desc\[.*\]/)
          expect(text).to     be_match(/^20XX年XX月XX日/)
          if Gem::Version.new(ReVIEW::VERSION) >= Gem::Version.new('5.0.0')
            expect(text).to     be_match(/^\/\/emlist\[.*?(.*?\[.*?\\\].*?)*.*?\]{/)
          end
        end
        it 'emlist not nested' do
          m = text.match(/^\/\/emlist.*?{(.*?)^\/\/}/m)
          if m
            inner = m[1]
            expect(inner).not_to be_match(/^\/\/.*?{.*?^\/\/}/m)
          end
        end
      end

      context 'image' do
        it 'border' do
          expect(text).not_to be_match(/^\/\/image\[.*?border=.*?/)
        end
        it 'width' do
          expect(text).not_to be_match(/^\/\/image\[.*?width=.*?/)
          expect(text).to     be_match(/^\/\/image\[.*?scale=.*?/)
        end
      end

      it '? id set to' do
        expect(text).not_to be_match(/^\/\/table\[[^\[\]]*?\]{/)
        expect(text).not_to be_match(/^\/\/list\[[^\[\]]*?\]{/)
        expect(text).to     be_match(/^\/\/list\[starter_auto_id_list_0\]\[.*?\]{/)
      end

      it 'noteref' do
        expect(text).not_to be_include('@<noteref>')
        expect(text).not_to be_match(/^\/\/note\[.*?\]\[.*?\]{/)
      end

      it 'list lineno' do
        expect(text).not_to be_match(/^\/\/list\[[^\]]*?lineno=.*?/)
      end

      it 'block comment' do
        text.gsub!(/^#@#\/\/sampleoutputbegin.*?^#@#\/\/sampleoutputend/m, '')
        expect(text).not_to be_match(/^#@\++/)
        expect(text).not_to be_match(/^#@-+/)
        inner = text.match(/^#@#\++\R(.*)^#@#-+/m)[1]
        expect(inner).to     be_match(/(^#@#.*\R)*/m)
      end

      it 'auto url link footnote' do
        expect(text).to be_include "//footnote[03_syntax_link_auto_footnote1][https://github.com/kmuto/review/blob/master/doc/format.ja.md]"
      end

      context 'exclude starter option' do
        it 'table' do
          expect(text).not_to be_match(/^\/\/table\[.*?\]\[.*?\]\[.*?\].*/)
        end
        it 'tsize' do
          expect(text).not_to be_match(/^\/\/tsize\[.*?\]\[.*?\].*/)
          expect(text).not_to be_include("//tsize[|*|")
          expect(text).to     be_include("//tsize[||")
          expect(text).to     be_include("//tsize[|latex||l|p{70mm}|]")
        end
        it 'image' do
          expect(text).not_to be_match(/\/\/image\[.*?,\s*\]/)
        end
        it 'imgtable' do
          expect(text).not_to be_match(/^\/\/imgtable\[.*?\]\[.*?\]\[.*?\].*/)
        end
      end

      it 'output block command' do
        expect(text).not_to be_match(/^\/\/output\[.*\]/)
      end

      it 'chapterauthor' do
        expect(text).to     be_match(/.\/\/chapterauthor\[.*\]/)
        expect(text).not_to be_match(/^\/\/chapterauthor\[.*\]/)
      end

      it 'qq' do
        expect(text).not_to be_match(/@<qq>\$.*?\$/)
        expect(text).not_to be_match(/@<qq>\|.*?\|/)
        expect(text).not_to be_match(/@<qq>{.*?}/)
      end

      it 'B' do
        expect(text).not_to be_match(/@<B>\$.*?\$/)
        expect(text).not_to be_match(/@<B>\|.*?\|/)
        expect(text).not_to be_match(/@<B>{.*?}/)
      end

      it 'noop' do
        expect(text).to     be_match(/@<b>({}|\|\||\$\$)/)
        expect(text).not_to include("must_be_replace_nop")
      end

      it 'par' do
        expect(text).not_to be_include('@<par>{}')
        expect(text).not_to be_include('@<par>$$')
        expect(text).not_to be_include('@<par>||')
        expect(text).not_to be_include('@<par>{i}')
        expect(text).not_to be_include('@<par>$i$')
        expect(text).not_to be_include('@<par>|i|')
      end

      it 'program' do
        expect(text).not_to be_match(/\/\/program\[.*?\]/)
      end

      it 'term' do
        expect(text).not_to be_match(/@<term>{.*?}/)
        expect(text).to     be_match(/@<idx>{.*?}/)
      end

      it 'termnoidx' do
        expect(text).not_to be_match(/@<termnoidx>{.*?}/)
        # expect(text).to     be_match(/@<hidx>{.*?}/)
      end

      it 'W' do
        expect(text).not_to be_match(/@<W>{.*?}/)
        expect(text).to     be_match(/@<wb>{.*?}/)
      end

      it 'csv table' do
        text.scan(/^\/\/table\[tbl-csv[0-9]*\](\[.*?\])*{\R(.*?)^\/\/}/m) { |m|
          expect(m[1]).not_to include(',')
        }
      end
  end

    if Gem::Version.new(ReVIEW::VERSION) >= Gem::Version.new('4.0.0')
      it 'deprecated list' do
        expect(File).to exist(file02)
        text = File.open(file02).read()
        expect(text).not_to be_match(/^:/)
      end
    end

    it 'preproc delete #@mapXXX~#@end' do
      expect(File).to exist(root)
      text = File.open(root).read()
      expect(text).not_to be_match(/^#[@]mapfile.*/)
      expect(text).not_to be_match(/^#[@]end$/)
      expect(text).to     be_match(/^== Inner file$/)
    end

    it 'no duplicate mapfile' do
      expect(File).to exist(root)
      expect(File).not_to exist(inner)
    end

    it 'br to blankline' do
      expect(File).to exist(root)
      text = File.open(root).read()
      expect(text).not_to be_match(/^\s*@<br>{}\s*$/)
      # expect(text).to match(/^\s*.*@<br>{}\s*$/)
      expect(text).to     be_match(/^\/\/blankline$/)
    end

    it 'sty' do
      expect(File).to exist(ird_sty)
      expect(File).to exist(custom_sty)
      text = File.open(custom_sty).read()
      expect(text).to include('\RequirePackage{ird}')
    end

    it 'ext' do
      expect(File).to exist(review_ext)
    end
  end
end
