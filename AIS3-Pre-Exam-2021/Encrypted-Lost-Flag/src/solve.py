from sage.all import *
from os import path
config = open(path.join(path.dirname(__file__),'config.c')).read()
for line in config.strip().split('\n'):
    x,y = line.split(' = ')
    n = x.split()[-1]
    if '"' in y: y = 'b'+y
    exec(f'{n} = {y}')

mod = 0x101
s2m = lambda s: matrix(GF(mod), size, size, s)

banner_m     = s2m(banner)
banner_enc_m = s2m(banner_enc)
flag_enc_m   = s2m(flag_enc)

flag_m = flag_enc_m * banner_enc_m.inverse() * banner_m
flag = ''.join(map(chr,vector(flag_m)))
print(flag)
