require "spec_helper"

RSpec.describe ReVIEW::Retrovert do
  it "has a version number" do
    expect(ReVIEW::Retrovert::VERSION).not_to be nil
  end
end

RSpec.describe 'command test', type: :aruba do

  context 'help' do
    before(:each) { run_command('bundle exec review-retrovert help') }
    it { expect(last_command_started).to be_successfully_executed }
  end

  context 'convert mybook' do
    let(:config_yaml) { File.join(File.dirname(__FILE__), '../../testdata/mybook/config.yml') }
    let(:outpath) { File.join(File.dirname(__FILE__), '../../tmp/rspec') }
    before(:each) { run_command("review-retrovert convert --preproc --tabwidth 4 --ird #{config_yaml} #{outpath}") }

    it 'command result' do
      expect(last_command_started).to be_successfully_executed
      expect(last_command_started).to have_output(/.*replace starter inline command.*/)
      expect(last_command_started).to have_output(/.*replace starter block command.*/)
    end
  end

end

RSpec.describe 'convert result' do

  context 'convert result' do
    let(:outpath) { File.join(File.dirname(__FILE__), '../../tmp/rspec') }
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
    let(:inner)  { File.join(outpath, 'contents/r0-inner.re') }
    let(:config) { File.join(outpath, 'config.yml') }
    let(:retrovert_config) { File.join(outpath, 'config-retrovert.yml') }
    let(:custom_sty) { File.join(outpath, 'sty/review-custom.sty') }

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
      expect(text).not_to include('@<userinput>{')
      expect(text).not_to include('@<small>{')
      expect(text).not_to include('@<xsmall>{')
      expect(text).not_to include('@<xxsmall>{')
      expect(text).not_to include('@<large>{')
      expect(text).not_to include('@<xlarge>{')
      expect(text).not_to include('@<xxlarge>{')
      expect(text).not_to include('@<weak>{')
      expect(text).not_to include('@<nop>{')
    end

    it 'inline command replace' do
      expect(File).to exist(file03)
      text = File.open(file03).read()
      expect(text).not_to include('@<secref>{')
      expect(text).to include('@<hd>{')
      expect(text).not_to include('@<file>{')
      expect(text).to include('@<kw>{')
      expect(text).not_to include('@<hlink>{')
      expect(text).to include('@<href>{')
      expect(text).not_to include('@<B>{')
      expect(text).to include('@<strong>{')
    end

    it 'LaTex inline command replace' do
      expect(File).to exist(file05)
      text = File.open(file05).read()
      expect(text).not_to include('@<LaTeX>{}')
      expect(text).to include('LaTeX')
    end

    it 'block command delete' do
      expect(File).to exist(file03)
      text = File.open(file03).read()
      expect(text).not_to match('^\/\/needvspace')
      expect(text).not_to match('^\/\/clearpage')
      expect(text).not_to match('^\/\/flushright')
      expect(text).not_to match('^\/\/centering')
      expect(text).not_to match('^\/\/noindent')
      expect(text).not_to match('^\/\/paragraphend')
    end

    it 'block comaptible command replace with options' do
      expect(File).to exist(file02)
      text = File.open(file02).read()
      expect(text).not_to match(/^\/\/terminal/)
      expect(text).not_to match(/^\/\/cmd\[.*?\]/)
      expect(text).to match(/^\/\/cmd{/)
    end

    it 'block comaptible command replace with options and inner text go outside' do
      expect(File).to exist(file99)
      text = File.open(file99).read()
      expect(text).not_to match(/^\/\/sideimage/)
      expect(text).to match(/^\/\/image\[tw-icon\]\[\s*\]{\R\/\/}/)
    end

    # it 'block command replace exclude options' do
    #   expect(File).to exist(file99)
    #   text = File.open(file99).read()
    #   expect(text).not_to match(/^\/\/sideimage/)
    #   expect(text).to match(/^\/\/image/)
    # end

    it 'block command replace with options' do
      expect(File).to exist(file02)
      text = File.open(file02).read()
      expect(text).not_to match(/^\/\/abstract/)
      expect(text).to match(/^\/\/lead/)
    end

    unless Gem::Version.new(ReVIEW::VERSION) >= Gem::Version.new('5.0.0')
      it 'nested block command' do
        expect(File).to exist(file01)
        text = File.open(file01).read()
        expect(text).not_to match(/^\/\/}\R*^\/\/}/m)

        expect(File).to exist(file03)
        text = File.open(file03).read()
        # expect(text).not_to match(/^\/\/}\R*^\/\/}/m)
        expect(text).to match(/^\/\/table\[tbl-xthfx\]/)
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
      expect(text).not_to include('|@@<b>{}')
      expect(text).not_to include('{@@<b>{}')
      expect(text).not_to include('$@@<b>{}')
    end

    it 'empty id set to' do
      expect(File).to exist(file05)
      text = File.open(file05).read()
      expect(text).not_to match(/^\/\/list\[[^\[\]]*?\]{/)
      expect(text).to match(/^\/\/list\[starter_auto_id_list_0\]\[.*?\]{/)
    end

    it '? id set to' do
      expect(File).to exist(file03)
      text = File.open(file03).read()
      expect(text).not_to match(/^\/\/list\[[^\[\]]*?\]{/)
      expect(text).to match(/^\/\/list\[starter_auto_id_list_0\]\[.*?\]{/)
    end

    it 'noteref' do
      expect(File).to exist(file03)
      text = File.open(file03).read()
      expect(text).not_to include('@<noteref>')
      expect(text).not_to match(/^\/\/note\[.*?\]\[.*?\]{/)
    end

    it 'image border' do
      expect(File).to exist(file03)
      text = File.open(file03).read()
      expect(text).not_to match(/^\/\/image\[[^\]]*?border=.*?/)

      expect(File).to exist(file06)
      text = File.open(file06).read()
      expect(text).not_to match(/^\/\/image\[[^\]]*?border=.*?/)
      end

    it 'list lineno' do
      expect(File).to exist(file03)
      text = File.open(file03).read()
      expect(text).not_to match(/^\/\/list\[[^\]]*?lineno=.*?/)
    end

    it 'fix lack options' do
      expect(File).to exist(file04)
      text = File.open(file04).read()
      expect(text).not_to match(/^\/\/list{$/)
      expect(text).to match(/^\/\/list\[starter_auto_id_list_[0-9]+\]\[\]{/)
    end

    it 'sampleoutputbegin' do
      expect(File).to exist(file06)
      text = File.open(file06).read()
      expect(text).not_to match(/^\/\/sampleoutputbegin\[.*?\]/)
      expect(text).not_to match(/^\/\/sampleoutputend/)
      expect(text).to match(/^#@#\/\/sampleoutputbegin\[.*?\]/)
      expect(text).to match(/^#@#\/\/sampleoutputend/)
    end

    it 'block comment in sampleout' do
      expect(File).to exist(file02)
      text = File.open(file02).read()
      expect(text).not_to match(/^#@#\/\/sampleoutputbegin.*?^#@\++.*^#@-+.*?^#@#\/\/sampleoutputend/m)
    end

    it 'block comment' do
      expect(File).to exist(file03)
      text = File.open(file03).read()
      text.gsub!(/^#@#\/\/sampleoutputbegin.*?^#@#\/\/sampleoutputend/m, '')
      expect(text).not_to match(/^#@\++/)
      expect(text).not_to match(/^#@-+/)
      # expect(text).to match(/^#@#\++\R(^#@#.*)*^#@#-+/m)
    end

    it 'auto url link footnote' do
      expect(File).to exist(file03)
      text = File.open(file03).read()
      expect(text).to include("//footnote[03_syntax_link_auto_footnote0][https://github.com/kmuto/review/blob/master/doc/format.ja.md]")
    end

    it 'preproc' do
      expect(last_command_started).to be_successfully_executed
      expect(last_command_started).to have_output(/INFO.*: preproc/)
    end

    if Gem::Version.new(ReVIEW::VERSION) >= Gem::Version.new('4.0.0')
      it 'deprecated list' do
        expect(File).to exist(file02)
        text = File.open(file02).read()
        expect(text).not_to match(/^:/)
      end
    end

    it 'retrovert config' do
      expect(File).to exist(config)
      text = File.open(config).read()
      expect(text).not_to match(/^chapterlink: .*/)

      expect(File).to exist(retrovert_config)
      text = File.open(retrovert_config).read()
      expect(text).to match(/^chapterlink: null/)
    end

    it 'preproc delete #@mapXXX~#@end' do
      expect(File).to exist(root)
      text = File.open(root).read()
      expect(text).not_to match(/^#[@]mapfile.*/)
      expect(text).not_to match(/^#[@]end$/)
      expect(text).to match(/^== Inner file$/)
    end

    it 'no duplicate mapfile' do
      expect(File).to exist(root)
      expect(File).to exist('tmp/r0-inner.re').not
    end

    it 'br to blankline' do
      expect(File).to exist(root)
      text = File.open(root).read()
      expect(text).not_to match(/^\s*@<br>{}\s*$/)
      # expect(text).to match(/^\s*.*@<br>{}\s*$/)
      expect(text).to match(/^\/\/blankline$/)
    end

    it 'sty' do
      expect(File).to exist('tmp/sty/ird.sty')
      expect(File).to exist(custom_sty)
      text = File.open(custom_sty).read()
      expect(text).to include('\RequirePackage{ird}')
    end

    it 'ext' do
      expect(File).to exist('tmp/review-ext.rb')
    end
  end
end
