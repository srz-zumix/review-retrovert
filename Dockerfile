ARG REVIEW_VERSION=latest
FROM vvakame/review:${REVIEW_VERSION}

RUN gem install review-retrovert

ENTRYPOINT [ "review-retrovert" ]
