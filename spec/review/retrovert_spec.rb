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
    end
  end
end
