ARG REVIEW_VERSION=lastest
FROM vvakame/review:$REVIEW_VERSION
ARG REVIEW_VERSION

WORKDIR /work
COPY . .
ENV BUNDLE_GEMFILE=Gemfile-$REVIEW_VERSION
RUN cp Gemfile Gemfile-$REVIEW_VERSION && \
    echo "gem \"review\", \"$REVIEW_VERSION\"" >> Gemfile-$REVIEW_VERSION && \
    bundle install
