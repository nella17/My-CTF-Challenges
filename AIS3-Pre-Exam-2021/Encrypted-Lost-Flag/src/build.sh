#!/bin/bash
set -eux

gcc matrix.c generate.c -o generate
./generate

gcc matrix.c solve.c -o solve
./solve

gcc matrix.c chall.c -o chall \
  -O2 -DNDEBUG -fdata-sections -ffunction-sections -Wl,--gc-sections
strip chall
gcc replaced/matrix.c replaced/chall.c -o chall-unstrip \
  -O2 -DNDEBUG -fdata-sections -ffunction-sections -Wl,--gc-sections

cp chall ../dist
cp chall-unstrip ../dist
