FROM ruby

WORKDIR /app
COPY Gemfile* ./
RUN apt update && apt install -y wkhtmltopdf && bundle install

COPY ./ ./

USER daemon
CMD ruby app.rb
