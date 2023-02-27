#!/bin/bash
c=${PWD##*/}
for i in */docker-compose.yml; do
  d="$(dirname "$i")"
  cd "$d"
  p="$(echo "$c-$d" | tr [A-Z] [a-z])"
  docker compose -p "$p" $@ &
  cd ..
done
wait
