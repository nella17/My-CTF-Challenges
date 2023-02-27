const express = require('express')
const bodyParser = require('body-parser')
const _ = require('lodash')

const { FLAG = 'FLAG_NOT_EXIST' } = process.env

const app = express();
app.use(bodyParser.json())

app.get('/', function(req, res) {
  res.sendFile('index.html', { root: __dirname })
})

app.get('/leak/:path', function(req, res) {
  res.sendFile(req.params.path, { root: __dirname })
})

app.post('/gen', function(req, res) {
  console.log(req.body)
  const { template, options, variable } = req.body
  let result = null
  try {
    result = _.template(template, options)(variable)
  } catch {
    result = 'qq'
  }
  res.send({ result })
})

app.listen(80);
