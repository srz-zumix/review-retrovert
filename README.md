[![Gem Version](https://badge.fury.io/rb/review-retrovert.svg)](https://badge.fury.io/rb/review-retrovert)
[![Retrovert](https://github.com/srz-zumix/review-retrovert/actions/workflows/retrovert.yml/badge.svg?branch=master)](https://github.com/srz-zumix/review-retrovert/actions/workflows/retrovert.yml)
[![Docker Pulls](https://img.shields.io/docker/pulls/srzzumix/review-retrovert)](https://hub.docker.com/r/srzzumix/review-retrovert)

# ReVIEW::Retrovert

[Re:VIEW Starter](https://kauplan.org/reviewstarter/) Project convert to [Re:VIEW](https://reviewml.org/ja/) 3.X/4.X/5.X

## Installation

Add this line to your application's Gemfile:

```ruby
gem 'review-retrovert'
```

And then execute:

    $ bundle install

Or install it yourself as:

    $ gem install review-retrovert
    
## Use Docker

```
docker run -v "$(pwd):/work" -w /work srzzumix/review-retrovert convert target/config.yml outdir
```

## Commands

```sh
Commands:
  review-retrovert convert {review_starter_configfile} {outdir}  # convert Re:VIEW Starter project to Re:VIEW project
  review-retrovert help [COMMAND]                                # Describe available commands or one specific command
  review-retrovert version                                       # show version
```

### Convert

#### e.g.

```sh
review-retrovert convert /path/to/dir/review-starter/config.yml <output directory>
```

#### Options

```sh
sage:
  review-retrovert convert {review_starter_configfile} {outdir}

Options:
      [-f], [--force]                              # Force output
      [--strict], [--no-strict]                    # Only process files registered in the catalog
      [--preproc], [--no-preproc]                  # Execute preproc after conversion
      [--tabwidth=N]                               # Preproc tabwidth option value
                                                   # Default: 0
      [--table-br-replace=TABLE-BR-REPLACE]        # @<br>{} in table replace string (Default: empty)
      [--table-empty-replace=TABLE-EMPTY-REPLACE]  # empty cell(.) in table replace string (Default full-width space)
                                                   # Default: 　
      [--ird], [--no-ird]                          # for IRD
      [--no-image]                                 # donot copy image

convert Re:VIEW Starter project to Re:VIEW project
```

#### retrovert config

If the retrovert key is present in config.yml, the subordinate elements will take effect after convert.

If you have a setting that you want to enable only after retrovert, use inherit as shown below.

* config-retrovert.yml

```yml
retrovert:
  chapterlink: null
```

* config-base.yml

```yml
chapterlink: true
```

* config.yml

```yml
inherit: ["config-base.yml", "config-starter.yml", "config-retrovert.yml"]

#chapterlink: true
```

## Experimental

### IRD sty

--ird オプションを付けると IRD 組版に近いレイアウトにするために ird.sty と reveiw-ext.rb をプロジェクトに追加します。
こちらは実験的機能です。

## Development

After checking out the repo, run `bin/setup` to install dependencies. Then, run `rake spec` to run the tests. You can also run `bin/console` for an interactive prompt that will allow you to experiment.

To install this gem onto your local machine, run `bundle exec rake install`. To release a new version, update the version number in `version.rb`, and then run `bundle exec rake release`, which will create a git tag for the version, push git commits and tags, and push the `.gem` file to [rubygems.org](https://rubygems.org).

## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/srz-zumix/review-retrovert.

## Develop

docker run -it --rm -v $(pwd)/:/work -w /work vvakame/review:5.0 bash

## License

The gem is available as open source under the terms of the [MIT License](https://opensource.org/licenses/MIT).
