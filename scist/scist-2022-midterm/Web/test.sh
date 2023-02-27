#!/bin/bash
read HOST
export HOST
export BACK=$HOST
for i in */exploit*
do
  cd "$(dirname $i)"
  echo $i
  ./$(basename $i)
  echo
  cd ..
done
