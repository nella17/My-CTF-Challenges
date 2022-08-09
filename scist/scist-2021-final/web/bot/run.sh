#!/usr/bin/env bash
# modify from https://github.com/splitline/My-CTF-Challenges/tree/master/ais3-pre-exam/2021/Web/xss-me/deploy/bot
redis-server --protected-mode no &
for _ in {1..4}; do
  rq worker &
done
sleep infinity
