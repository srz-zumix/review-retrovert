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
  spec.required_ruby_version = Gem::Requirement.new(">= 2.3.0")

  # spec.metadata["allowed_push_host"] = "http://mygemserver.com"

  spec.metadata["homepage_uri"] = spec.homepage
  spec.metadata["source_code_uri"] = "https://github.com/srz-zumix/review-retrovert"
  spec.metadata["changelog_uri"] = "https://github.com/srz-zumix/review-retrovert"

  # Specify which files should be added to the gem when it is released.
  # The `git ls-files -z` loads the files in the RubyGem that have been added into git.
  spec.files         = Dir.chdir(File.expand_path('..', __FILE__)) do
    `git ls-files -z`.split("\x0").reject { |f| f.match(%r{^(test|spec|features)/}) }
  end
  spec.bindir        = "exe"
  spec.executables   = spec.files.grep(%r{^exe/}) { |f| File.basename(f) }
  spec.require_paths = ["lib"]

  spec.add_dependency "thor"
  spec.add_development_dependency "rspec", ['~> 3.0']
  spec.add_development_dependency "rake", ['~> 12.0']
  spec.add_development_dependency 'aruba', ['~> 1.0.2']
  spec.add_development_dependency "ruby-debug-ide"
#   spec.add_development_dependency "debase"
  spec.add_runtime_dependency "review", ['>= 3.0.0']
end
