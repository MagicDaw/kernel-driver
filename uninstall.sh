#! /bin/sh 

sudo dmesg -C

sudo rmmod "mem-kdawid.ko"

make clean

# print loaded modules (just for debug)
lsmod

# print debug from driver
sudo dmesg

