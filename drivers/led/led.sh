#! /bin/sh

insmod led.ko
mknod /dev/led c 245 0
