help: ## show help
	@grep -E '^[a-zA-Z][a-zA-Z0-9_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sed -e 's/^GNUmakefile://' | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-20s\033[0m %s\n", $$1, $$2}'

init:
	bundle install --binstubs

review3:
	docker build . -t review-3-retrovert -f docker/review.Dockerfile --build-arg REVIEW_VERSION=3.2
	docker run -it --rm -w /work review-3-retrovert bash

test:
	RUBYLIB=lib ./exe/review-retrovert convert --preproc --tabwidth 4 testdata/mybook/config.yml -f tmp/debug

test-ird:
	RUBYLIB=lib ./exe/review-retrovert convert --preproc --tabwidth 4 --ird testdata/mybook/config.yml -f tmp/debug

test-ut:
	RUBYLIB=lib ./exe/review-retrovert convert --preproc --tabwidth 4 --delegate-config testdata/mybook/ut-config.yml -f tmp/debug

REVIEW_VERSION:=latest

debug-build:
	docker run --rm -v "${PWD}/tmp/debug":/work -w /work vvakame/review:${REVIEW_VERSION} rake preproc pdf
	# docker run --rm -v "${PWD}":/work -w /work vvakame/review rake preproc pdf

testdata-pdf:
	docker run --rm -v ${PWD}/testdata/mybook:/work -w /work kauplan/review2.5 rake pdf

testdata-ut-pdf:
	# rm -rf ./testdata/mybook/mybook-ut-pdf
	docker run --rm -v ${PWD}/testdata/mybook:/work -w /work -e config=ut-config.yml kauplan/review2.5 rake pdf
