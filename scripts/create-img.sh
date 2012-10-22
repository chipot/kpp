#!/usr/bin/env sh

bximage << EOF
hd
flat
2
c.img
EOF

fdisk c.img << EOF
x
c
4
h
16
s
63
r
n
p
1


a
1
w
EOF
