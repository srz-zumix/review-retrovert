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

    it 'block command delete' do
      expect(File).to exist(file03)
      text = File.open(file03).read()
      expect(text).not_to be_match('^\/\/needvspace')
      expect(text).not_to be_match('^\/\/clearpage')
      expect(text).not_to be_match('^\/\/flushright')
      expect(text).not_to be_match('^\/\/centering')
      expect(text).not_to be_match('^\/\/noindent')
      expect(text).not_to be_match('^\/\/paragraphend')
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

    it '? id set to' do
      expect(File).to exist(file03)
      text = File.open(file03).read()
      expect(text).not_to be_match(/^\/\/list\[[^\[\]]*?\]{/)
      expect(text).to     be_match(/^\/\/list\[starter_auto_id_list_0\]\[.*?\]{/)
    end

    it 'noteref' do
      expect(File).to exist(file03)
      text = File.open(file03).read()
      expect(text).not_to be_include('@<noteref>')
      expect(text).not_to be_match(/^\/\/note\[.*?\]\[.*?\]{/)
    end

    it 'image border' do
      expect(File).to exist(file03)
      text = File.open(file03).read()
      expect(text).not_to be_match(/^\/\/image\[[^\]]*?border=.*?/)

      expect(File).to exist(file06)
      text = File.open(file06).read()
      expect(text).not_to be_match(/^\/\/image\[[^\]]*?border=.*?/)
      end

    it 'list lineno' do
      expect(File).to exist(file03)
      text = File.open(file03).read()
      expect(text).not_to be_match(/^\/\/list\[[^\]]*?lineno=.*?/)
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

    it 'block comment' do
      expect(File).to exist(file03)
      text = File.open(file03).read()
      text.gsub!(/^#@#\/\/sampleoutputbegin.*?^#@#\/\/sampleoutputend/m, '')
      expect(text).not_to be_match(/^#@\++/)
      expect(text).not_to be_match(/^#@-+/)
      inner = text.match(/^#@#\++\R(.*)^#@#-+/m)[1]
      expect(inner).to     be_match(/(^#@#.*\R)*/m)
    end

    it 'auto url link footnote' do
      expect(File).to exist(file03)
      text = File.open(file03).read()
      expect(text).to be_include "//footnote[03_syntax_link_auto_footnote1][https://github.com/kmuto/review/blob/master/doc/format.ja.md]"
    end

    it 'talklist' do
      expect(File).to exist(file03)
      text = File.open(file03).read()
      expect(text).not_to be_match(/^\/\/talklist\[.*\]/)
      expect(text).not_to be_match(/^\/\/talk\[.*\]/)
    end

    it 'desclist' do
      expect(File).to exist(file03)
      text = File.open(file03).read()
      expect(text).not_to be_match(/^\/\/desclist\[.*\]/)
      expect(text).not_to be_match(/^\/\/desc\[.*\]/)
    end

    it 'chapterauthor' do
      expect(File).to exist(file03)
      text = File.open(file03).read()
      expect(text).to     be_match(/.\/\/chapterauthor\[.*\]/)
      expect(text).not_to be_match(/^\/\/chapterauthor\[.*\]/)
    end

    it 'par' do
      expect(File).to exist(file03)
      text = File.open(file03).read()
      expect(text).not_to be_include('@<par>{}')
      expect(text).not_to be_include('@<par>$$')
      expect(text).not_to be_include('@<par>||')
      expect(text).not_to be_include('@<par>{i}')
      expect(text).not_to be_include('@<par>$i$')
      expect(text).not_to be_include('@<par>|i|')
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
