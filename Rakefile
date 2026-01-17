require "bundler/gem_tasks"
require "rspec/core/rake_task"

RSpec::Core::RakeTask.new(:spec)

task :default => :spec

desc "Run bundle install and stage Gemfile.lock"
task :post_tagpr do
  sh "bundle install"
  sh "git add Gemfile.lock"
end

# Override the source_control_push task to skip git push
# This is useful when releasing from CI where the tag is already pushed
Rake::Task["release:source_control_push"].clear
namespace :release do
  task :source_control_push do
    # Do nothing - tag is already pushed by CI
  end
end

