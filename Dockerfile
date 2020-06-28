FROM vvakame/review:3.2

# RUN gem install review-retrovert
RUN rake install

ENTRYPOINT [ "review-retrovert" ]
