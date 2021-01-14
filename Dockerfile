FROM vvakame/review:5.0

RUN gem install review-retrovert

ENTRYPOINT [ "review-retrovert" ]
