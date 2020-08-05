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
    before(:each) { run_command("review-retrovert convert #{config_yaml} tmp") }

    it 'command result' do
      expect(last_command_started).to be_successfully_executed
      expect(last_command_started).to have_output(/.*replace starter inline command.*/)
      expect(last_command_started).to have_output(/.*replace starter block command.*/)
    end

    it 'inline command delete' do
      expect('tmp/03-syntax.re').to be_an_existing_file
      text = File.open(File.join(aruba.current_directory, 'tmp/03-syntax.re')).read()
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
      expect('tmp/03-syntax.re').to be_an_existing_file
      text = File.open(File.join(aruba.current_directory, 'tmp/03-syntax.re')).read()
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
      expect('tmp/05-faq.re').to be_an_existing_file
      text = File.open(File.join(aruba.current_directory, 'tmp/05-faq.re')).read()
      expect(text).not_to include('@<LaTeX>{}')
      expect(text).to include('LaTeX')
    end

    it 'block comaptible command replace with options' do
      expect('tmp/02-tutorial.re').to be_an_existing_file
      text = File.open(File.join(aruba.current_directory, 'tmp/02-tutorial.re')).read()
      expect(text).not_to match(/^\/\/cmd\[.*?\]\[.*?\]/)
    end

    it 'block command replace exclude options' do
      expect('tmp/99-postface.re').to be_an_existing_file
      text = File.open(File.join(aruba.current_directory, 'tmp/99-postface.re')).read()
      expect(text).not_to match(/^\/\/sideimage/)
      expect(text).to match(/^\/\/image/)
    end

    it 'block command replace with options' do
      expect('tmp/02-tutorial.re').to be_an_existing_file
      text = File.open(File.join(aruba.current_directory, 'tmp/02-tutorial.re')).read()
      expect(text).not_to match(/^\/\/abstract/)
      expect(text).to match(/^\/\/lead/)
      expect(text).not_to match(/^\/\/terminal/)
      expect(text).to match(/^\/\/cmd/)
    end

    it 'sampleoutputbegin' do
      expect('tmp/06-bestpractice.re').to be_an_existing_file
      text = File.open(File.join(aruba.current_directory, 'tmp/06-bestpractice.re')).read()
      expect(text).not_to match(/^\/\/sampleoutputbegin\[.*?\]/)
      expect(text).not_to include('sampleoutputend')
    end

  end
end
