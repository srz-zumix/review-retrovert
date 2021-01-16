require "spec_helper"

RSpec.describe ReVIEW::Retrovert do
  it "has a version number" do
    expect(ReVIEW::Retrovert::VERSION).not_to be nil
  end
end

RSpec.describe 'convert', type: :aruba do

  context 'help' do
    before(:each) { run_command('bundle exec review-retrovert help') }
    it { expect(last_command_started).to be_successfully_executed }
  end

  context 'convert mybook' do
    let(:config_yaml) { File.join(File.dirname(__FILE__), '../../testdata/mybook/config.yml') }
    let(:file00) { 'tmp/00-preface.re' }
    let(:file01) { 'tmp/01-install.re' }
    let(:file02) { 'tmp/02-tutorial.re' }
    let(:file03) { 'tmp/03-syntax.re' }
    let(:file04) { 'tmp/04-customize.re' }
    let(:file05) { 'tmp/05-faq.re' }
    let(:file06) { 'tmp/06-bestpractice.re' }
    let(:file91) { 'tmp/91-compare.re' }
    let(:file92) { 'tmp/92-filelist.re' }
    let(:file93) { 'tmp/93-background.re' }
    let(:file99) { 'tmp/99-postface.re' }
    let(:root)  { 'tmp/r0-root.re' }
    let(:inner) { 'tmp/contents/r0-inner.re' }
    let(:config) { 'tmp/config.yml' }
    let(:retrovert_config) { 'tmp/config-retrovert.yml' }
    before(:each) { run_command("review-retrovert convert --preproc --tabwidth 4 #{config_yaml} tmp") }

    it 'command result' do
      expect(last_command_started).to be_successfully_executed
      expect(last_command_started).to have_output(/.*replace starter inline command.*/)
      expect(last_command_started).to have_output(/.*replace starter block command.*/)
    end

    it 'file exist' do
      expect(file00).to be_an_existing_file
      expect(file01).to be_an_existing_file
      expect(file02).to be_an_existing_file
      expect(file03).to be_an_existing_file
      expect(file04).to be_an_existing_file
      expect(file05).to be_an_existing_file
      expect(file06).to be_an_existing_file
      expect(file91).to be_an_existing_file
      expect(file92).to be_an_existing_file
      expect(file93).to be_an_existing_file
      expect(file99).to be_an_existing_file
    end

    it 'inline command delete' do
      expect(file03).to be_an_existing_file
      text = File.open(File.join(aruba.current_directory, file03)).read()
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
      expect(file03).to be_an_existing_file
      text = File.open(File.join(aruba.current_directory, file03)).read()
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
      expect(file05).to be_an_existing_file
      text = File.open(File.join(aruba.current_directory, file05)).read()
      expect(text).not_to include('@<LaTeX>{}')
      expect(text).to include('LaTeX')
    end

    it 'block command delete' do
      expect(file03).to be_an_existing_file
      text = File.open(File.join(aruba.current_directory, file03)).read()
      expect(text).not_to match('^\/\/needvspace')
      expect(text).not_to match('^\/\/clearpage')
      expect(text).not_to match('^\/\/flushright')
      expect(text).not_to match('^\/\/centering')
      expect(text).not_to match('^\/\/noindent')
      expect(text).not_to match('^\/\/paragraphend')
    end

    it 'block comaptible command replace with options' do
      expect(file02).to be_an_existing_file
      text = File.open(File.join(aruba.current_directory, file02)).read()
      expect(text).not_to match(/^\/\/terminal/)
      expect(text).not_to match(/^\/\/cmd\[.*?\]/)
      expect(text).to match(/^\/\/cmd{/)
    end

    it 'block comaptible command replace with options and inner text go outside' do
      expect(file99).to be_an_existing_file
      text = File.open(File.join(aruba.current_directory, file99)).read()
      expect(text).not_to match(/^\/\/sideimage/)
      expect(text).to match(/^\/\/image\[tw-icon\]\[\s*\]{\R\/\/}/)
    end

    # it 'block command replace exclude options' do
    #   expect(file99).to be_an_existing_file
    #   text = File.open(File.join(aruba.current_directory, file99)).read()
    #   expect(text).not_to match(/^\/\/sideimage/)
    #   expect(text).to match(/^\/\/image/)
    # end

    it 'block command replace with options' do
      expect(file02).to be_an_existing_file
      text = File.open(File.join(aruba.current_directory, file02)).read()
      expect(text).not_to match(/^\/\/abstract/)
      expect(text).to match(/^\/\/lead/)
    end

    unless Gem::Version.new(ReVIEW::VERSION) >= Gem::Version.new('5.0.0')
      it 'nested block command' do
        expect(file01).to be_an_existing_file
        text = File.open(File.join(aruba.current_directory, file01)).read()
        expect(text).not_to match(/^\/\/}\R*^\/\/}/m)

        expect(file03).to be_an_existing_file
        text = File.open(File.join(aruba.current_directory, file03)).read()
        # expect(text).not_to match(/^\/\/}\R*^\/\/}/m)
        expect(text).to match(/^\/\/table\[tbl-xthfx\]/)
      end
    end

    # it 'nested block command exclude {}' do
    #   expect(file06).to be_an_existing_file
    #   text = File.open(File.join(aruba.current_directory, file06)).read()
    #   expect(text).not_to match(/^#@#\/\/footnote/)
    # end

    it 'nested inline command' do
      expect(file01).to be_an_existing_file
      text = File.open(File.join(aruba.current_directory, file01)).read()
      expect(text).not_to include('|@@<b>{}')
      expect(text).not_to include('{@@<b>{}')
      expect(text).not_to include('$@@<b>{}')
    end

    it 'empty id set to' do
      expect(file05).to be_an_existing_file
      text = File.open(File.join(aruba.current_directory, file05)).read()
      expect(text).not_to match(/^\/\/list\[[^\[\]]*?\]{/)
      expect(text).to match(/^\/\/list\[starter_auto_id_list_0\]\[.*?\]{/)
    end

    it '? id set to' do
      expect(file03).to be_an_existing_file
      text = File.open(File.join(aruba.current_directory, file03)).read()
      expect(text).not_to match(/^\/\/list\[[^\[\]]*?\]{/)
      expect(text).to match(/^\/\/list\[starter_auto_id_list_0\]\[.*?\]{/)
    end

    it 'noteref' do
      expect(file03).to be_an_existing_file
      text = File.open(File.join(aruba.current_directory, file03)).read()
      expect(text).not_to include('@<noteref>')
      expect(text).not_to match(/^\/\/note\[.*?\]\[.*?\]{/)
    end

    it 'image border' do
      expect(file03).to be_an_existing_file
      text = File.open(File.join(aruba.current_directory, file03)).read()
      expect(text).not_to match(/^\/\/image\[[^\]]*?border=.*?/)

      expect(file06).to be_an_existing_file
      text = File.open(File.join(aruba.current_directory, file06)).read()
      expect(text).not_to match(/^\/\/image\[[^\]]*?border=.*?/)
      end

    it 'list lineno' do
      expect(file03).to be_an_existing_file
      text = File.open(File.join(aruba.current_directory, file03)).read()
      expect(text).not_to match(/^\/\/list\[[^\]]*?lineno=.*?/)
    end

    it 'fix lack options' do
      expect(file04).to be_an_existing_file
      text = File.open(File.join(aruba.current_directory, file04)).read()
      expect(text).not_to match(/^\/\/list{$/)
      expect(text).to match(/^\/\/list\[starter_auto_id_list_[0-9]+\]\[\]{/)
    end

    it 'sampleoutputbegin' do
      expect(file06).to be_an_existing_file
      text = File.open(File.join(aruba.current_directory, file06)).read()
      expect(text).not_to match(/^\/\/sampleoutputbegin\[.*?\]/)
      expect(text).not_to match(/^\/\/sampleoutputend/)
      expect(text).to match(/^#@#\/\/sampleoutputbegin\[.*?\]/)
      expect(text).to match(/^#@#\/\/sampleoutputend/)
    end

    it 'block comment in sampleout' do
      expect(file02).to be_an_existing_file
      text = File.open(File.join(aruba.current_directory, file02)).read()
      expect(text).not_to match(/^#@#\/\/sampleoutputbegin.*?^#@\++.*^#@-+.*?^#@#\/\/sampleoutputend/m)
    end

    it 'block comment' do
      expect(file03).to be_an_existing_file
      text = File.open(File.join(aruba.current_directory, file03)).read()
      text.gsub!(/^#@#\/\/sampleoutputbegin.*?^#@#\/\/sampleoutputend/m, '')
      expect(text).not_to match(/^#@\++/)
      expect(text).not_to match(/^#@-+/)
      expect(text).to match(/^#@#\++\R(^#@#.*)*^#@#-+/m)
    end

    it 'auto url link footnote' do
      expect(file03).to be_an_existing_file
      text = File.open(File.join(aruba.current_directory, file03)).read()
      expect(text).to include("//footnote[03_syntax_link_auto_footnote0][https://github.com/kmuto/review/blob/master/doc/format.ja.md]")
    end

    it 'preproc' do
      expect(last_command_started).to be_successfully_executed
      expect(last_command_started).to have_output(/INFO.*: preproc/)
    end

    if Gem::Version.new(ReVIEW::VERSION) >= Gem::Version.new('4.0.0')
      it 'deprecated list' do
        expect(file02).to be_an_existing_file
        text = File.open(File.join(aruba.current_directory, file02)).read()
        expect(text).not_to match(/^:/)
      end
    end

    it 'retrovert config' do
      expect(config).to be_an_existing_file
      text = File.open(File.join(aruba.current_directory, config)).read()
      expect(text).not_to match(/^chapterlink: .*/)

      expect(retrovert_config).to be_an_existing_file
      text = File.open(File.join(aruba.current_directory, retrovert_config)).read()
      expect(text).to match(/^chapterlink: null/)
    end

    it 'preproc delete #@mapXXX~#@end' do
      expect(root).to be_an_existing_file
      text = File.open(File.join(aruba.current_directory, root)).read()
      expect(text).not_to match(/^#[@]mapfile.*/)
      expect(text).not_to match(/^#[@]end$/)
      expect(text).to match(/^== Inner file$/)
    end

    it 'no duplicate mapfile' do
      expect(root).to be_an_existing_file
      expect('tmp/r0-inner.re').not_to be_an_existing_file
    end

    it 'br to blankline' do
      expect(root).to be_an_existing_file
      text = File.open(File.join(aruba.current_directory, root)).read()
      expect(text).not_to match(/^\s*@<br>{}\s*$/)
      expect(text).to match(/^\s*.*@<br>{}\s*$/)
      expect(text).to match(/^\/\/blankline$/)
    end
  end
end
