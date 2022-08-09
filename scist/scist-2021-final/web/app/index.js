// SCIST{flag2_p4th_triv3r5a1}

const express = require('express')
const expressLogging = require('express-logging')
const logger = require('logops')
const fs = require('fs')
const path = require('path')
const cookieParser = require('cookie-parser')
const crypto = require('crypto')
const child_process = require('child_process')

const sha256sum = s => crypto.createHash('sha256').update(s).digest('hex')
const { FLAG1, ADMIN_USERNAME, ADMIN_PASSWORD_HASH } = process.env
const port = 80

const app = express()
app.use(expressLogging(logger))
app.use(cookieParser())
app.use(express.urlencoded({ extended: true }))

const db = Object.create(null)
db[ADMIN_USERNAME] = {
  password: ADMIN_PASSWORD_HASH
}
const shared_db = Object.create(null)

const fail = (res, msg) => res.json({ done: false, msg })
const success = (res, o = {}) => res.json({ done: true, ...o })

const checkLogin = ({ username, password } = {}) => {
  return username in db && db[username].password === sha256sum(password)
}

const requireLogin = (req, res, next) => {
  return checkLogin(req.cookies) ? next() : fail(res, 'Login Required')
}

const requireAdmin = (req, res, next) => {
  return req.cookies.is_admin == 'true' ? next() : fail(res, 'Not admin :(')
}

const reject = (req, res, next) => {
  return req.cookies.bot || req.cookies.username === ADMIN_USERNAME ? fail(res) : next()
}

const exec = cmd => child_process.execSync(cmd, {
  encoding: 'utf8',
  timeout: 3000,
  env: {},
  uid: 65534,
  gid: 65534,
})

app.get('/bot', (req, res) => {
  res.cookie('bot', true, { httpOnly: true })
  success(res)
})

app.get('/verify', (req, res) => checkLogin(req.cookies) ? success(res) : fail(res))

app.get('/logout.html', (req, res) => {
  res.clearCookie('username')
  res.clearCookie('password')
  res.clearCookie('is_admin')
  res.redirect('/login.html')
})

app.post('/login', (req, res) => {
  const { username, password } = req.body
  if (username in db) {
    if (!checkLogin(req.body))
      return fail(res, 'Login Fail')
  } else {
    db[username] = {
      password: sha256sum(password),
      note: ''
    }
  }
  res.cookie('username', username)
  res.cookie('password', password)
  res.cookie('is_admin', username === ADMIN_USERNAME)
  success(res)
})

app.get('/flag1', requireAdmin, (req, res) => {
  success(res, { FLAG1 })
})

app.get('/read', requireLogin, (req, res) => {
  success(res, db[req.cookies.username])
})

app.post('/save', requireLogin, reject, (req, res) => {
  db[req.cookies.username].note = req.body.note
  success(res)
})

app.get('/share', (req, res) => {
  const note = shared_db[req.query.key]
  success(res, { note })
})

app.post('/share', requireLogin, reject, (req, res) => {
  const { username } = req.cookies
  const { note } = db[username]
  const key = username + sha256sum(note)
  shared_db[key] = note
  success(res, { key })
})

app.post('/report', requireLogin, reject, (req, res) => {
  const { url } = req.body
  console.log(req.cookies.username, url)
  if (url.includes("'")) return fail("Bad hacker :(")
  const msg = exec(`python3 /send.py '${url}'`)
  success(res, { msg })
})

app.get(/^\/.*$/, (req, res) => {
  let fn = './public' + req.path.replaceAll('../', '')
  if (!fs.existsSync(fn)) fn = './public/index.html'
  res.sendFile(fn, { root: __dirname })
})

app.listen(port, () => {
  console.log(`Example app listening on port ${port}`)
})
