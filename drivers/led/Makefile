PWD = $(shell pwd)
KERNELDIR = /home/minaduki/Desktop/Beaglebone_Proj/src
ARCH_TYPE = arm
PERFIX = arm-linux-gnueabihf-
obj-m = led.o

default:
	$(MAKE) CROSS_COMPILE=$(PERFIX) ARCH=$(ARCH_TYPE) -C $(KERNELDIR) SUBDIRS=$(PWD) modules

clean:
	$(MAKE) CROSS_COMPILE=$(PERFIX) ARCH=$(ARCH_TYPE) -C $(KERNELDIR) SUBDIRS=$(PWD) clean