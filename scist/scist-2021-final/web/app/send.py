from sys import argv
url = argv[1]

import re
if not re.match('^https?://.+', url):
    print('url must startwith http:// or https://')
else:
    from redis import Redis
    from rq import Queue
    queue = Queue(connection=Redis('bot'))
    queue.enqueue('xssbot.browse', url)
    print(f'bot will visit "{url}" soon')
