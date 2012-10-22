#!/usr/bin/env sh

mount -t ext2 /dev/loop0 /mnt/loop

cp $1 /mnt/loop/kernel

umount /dev/loop0

sudo -k
