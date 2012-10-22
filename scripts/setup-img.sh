#!/usr/bin/env sh

losetup -o 512 /dev/loop0 c.img

mkfs.ext2 /dev/loop0

mount -t ext2 /dev/loop0 /mnt/loop

mkdir /mnt/loop/grub
cp /boot/grub/stage* /mnt/loop/grub
cat > /mnt/loop/grub/menu.lst << EOF
title=Pepin
root (hd0,0)
kernel /kernel
boot
EOF

umount /mnt/loop
grub --device-map=/dev/null << EOF
device (hd0) c.img
root (hd0,0)
setup (hd0)
quit
EOF

sudo -k
