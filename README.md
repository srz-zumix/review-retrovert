[![Gem Version](https://badge.fury.io/rb/review-retrovert.svg)](https://badge.fury.io/rb/review-retrovert)
[![Build Status](https://travis-ci.com/srz-zumix/review-retrovert.svg?token=ArNHjRjvfZfyqQUCbXSt&branch=master)](https://travis-ci.com/srz-zumix/review-retrovert)
[![Docker Cloud Build Status](https://img.shields.io/docker/cloud/build/srzzumix/review-retrovert.svg)](https://hub.docker.com/r/srzzumix/review-retrovert/)

# ReVIEW::Retrovert

[Re:VIEW Starter](https://kauplan.org/reviewstarter/) Project convert to [Re:VIEW](https://reviewml.org/ja/) 3.X

## Installation

Add this line to your application's Gemfile:

```ruby
gem 'review-retrovert'
```

And then execute:

    $ bundle install

Or install it yourself as:

    $ gem install review-retrovert

## Usage

```sh
review-retrovert convert /path/to/dir/review-starter/config.yml <output directory>
```

## Development

After checking out the repo, run `bin/setup` to install dependencies. Then, run `rake spec` to run the tests. You can also run `bin/console` for an interactive prompt that will allow you to experiment.

To install this gem onto your local machine, run `bundle exec rake install`. To release a new version, update the version number in `version.rb`, and then run `bundle exec rake release`, which will create a git tag for the version, push git commits and tags, and push the `.gem` file to [rubygems.org](https://rubygems.org).

## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/srz-zumix/review-retrovert.

## Develop

docker run -it --rm -v $(pwd)/:/work -w /work vvakame/review:3.2 bash

## License

The gem is available as open source under the terms of the [MIT License](https://opensource.org/licenses/MIT).
