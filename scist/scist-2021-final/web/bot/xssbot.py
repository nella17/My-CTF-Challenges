#!/usr/bin/env python3
# modify from https://github.com/splitline/My-CTF-Challenges/tree/master/ais3-pre-exam/2021/Web/xss-me/deploy/bot
import time
from os import getenv

from selenium.webdriver import Chrome
from selenium.webdriver.chrome.options import Options

TIMEOUT = 3
HOST = getenv("HOST") or "http://app"
ADMIN_USERNAME = getenv('ADMIN_USERNAME') or 'admin'
ADMIN_PASSWORD = getenv('ADMIN_PASSWORD') or 'PASSWORD'

def browse(url):
    options = Options()
    options.headless = True
    options.add_argument('--no-sandbox') # https://stackoverflow.com/a/45846909
    options.add_argument('--disable-dev-shm-usage') # https://stackoverflow.com/a/50642913
    chrome = Chrome(options=options)
    # https://stackoverflow.com/a/47695227
    chrome.set_page_load_timeout(TIMEOUT)
    chrome.set_script_timeout(TIMEOUT)

    try:
        # login
        chrome.get(HOST)
        chrome.find_element('name', 'username').send_keys(ADMIN_USERNAME)
        chrome.find_element('name', 'password').send_keys(ADMIN_PASSWORD)
        chrome.find_element('name', 'submit').click()

        # visit
        chrome.get(HOST + '/bot')
        chrome.get(url)

        time.sleep(TIMEOUT)
    except:
        pass

    chrome.quit()
