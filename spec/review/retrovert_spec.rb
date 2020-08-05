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
    before(:each) { run_command("review-retrovert convert #{config_yaml} tmp") }

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

    it 'block comaptible command replace with options' do
      expect(file02).to be_an_existing_file
      text = File.open(File.join(aruba.current_directory, file02)).read()
      expect(text).not_to match(/^\/\/terminal/)
      expect(text).not_to match(/^\/\/cmd\[.*?\]\[.*?\]/)
    end

    it 'block comaptible command replace with options and inner text go outside' do
      expect(file99).to be_an_existing_file
      text = File.open(File.join(aruba.current_directory, file99)).read()
      expect(text).not_to match(/^\/\/sideimage/)
      expect(text).to match(/^\/\/image\[tw-icon\]{\R\/\/}/)
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

    it 'sampleoutputbegin' do
      expect(file06).to be_an_existing_file
      text = File.open(File.join(aruba.current_directory, file06)).read()
      expect(text).not_to match(/^\/\/sampleoutputbegin\[.*?\]/)
      expect(text).not_to include('sampleoutputend')
    end

  end
end
