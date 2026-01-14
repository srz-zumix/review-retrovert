require_relative 'lib/review/retrovert/version'

Gem::Specification.new do |spec|
  spec.name          = "review-retrovert"
  spec.version       = ReVIEW::Retrovert::VERSION
  spec.authors       = ["srz_zumix"]
  spec.email         = ["zumix.cpp@gmail.com"]

  spec.summary       = %q{Re:VIEW Starter to Re:VIEW}
  spec.description   = %q{Re:VIEW Starter to Re:VIEW}
  spec.homepage      = "https://github.com/srz-zumix/review-retrovert"
  spec.license       = "MIT"
  if RUBY_VERSION >= '2.6.0'
      spec.required_ruby_version = Gem::Requirement.new(">= 2.6.0")
  else
      spec.required_ruby_version = Gem::Requirement.new(">= 2.3.0")
  end

  # spec.metadata["allowed_push_host"] = "http://mygemserver.com"

  spec.metadata["homepage_uri"] = spec.homepage
  spec.metadata["source_code_uri"] = "https://github.com/srz-zumix/review-retrovert"
  spec.metadata["changelog_uri"] = "https://github.com/srz-zumix/review-retrovert"

  # Specify which files should be added to the gem when it is released.
  # Explicitly list files to avoid git/Docker environment dependencies
  spec.files         = Dir.chdir(File.expand_path('..', __FILE__)) do
    Dir['lib/**/*'] +
    Dir['exe/*'] +
    ['README.md', 'LICENSE', 'CHANGELOG.md', 'Rakefile']
  end.select { |f| File.file?(f) }
  spec.bindir        = "exe"
  spec.executables   = spec.files.grep(%r{^exe/}) { |f| File.basename(f) }
  spec.require_paths = ["lib"]

  # thor 1.3+ requires Ruby >= 2.6.0
  if RUBY_VERSION >= '2.6.0'
    spec.add_dependency "thor"
  else
    spec.add_dependency "thor", "~> 1.2.2"
  end
  # Required for Ruby 3.4+ where these gems are no longer default gems
  # Necessary for compatibility with review versions 5.4 and earlier
  spec.add_dependency "rexml"
  spec.add_dependency "csv"
  spec.add_dependency "nkf"
  spec.add_development_dependency "rspec", ['~> 3.0']
  spec.add_development_dependency "rake", ['~> 12.0']
  spec.add_development_dependency 'aruba', ['~> 1.0.2']
  spec.add_development_dependency "ruby-debug-ide"
  #spec.add_development_dependency "debase"
  spec.add_runtime_dependency "review", ['>= 3.0.0']
end
