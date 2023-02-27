require 'pdfkit'
require 'sinatra'

set :bind, '0.0.0.0'
set :port, 80
set :public_folder, __dir__

get '/' do
  erb :index
end

get '/pdf' do
  puts params
  content_type :pdf
  PDFKit.new(params['url']).to_pdf
end
