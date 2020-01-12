PWD = $(shell pwd)
KERNELDIR = /home/minaduki/Desktop/Beaglebone_Proj/src
ARCH_TYPE = arm
PREFIX = arm-linux-gnueabihf-
obj-m = led.o
APP = ledctrl
APP_SRC = ledctrl.c

default: $(APP)
	$(MAKE) CROSS_COMPILE=$(PREFIX) ARCH=$(ARCH_TYPE) -C $(KERNELDIR) SUBDIRS=$(PWD) modules

$(APP): $(APP_SRC)
	$(PREFIX)gcc -o $@ $^

clean:
	$(MAKE) CROSS_COMPILE=$(PREFIX) ARCH=$(ARCH_TYPE) -C $(KERNELDIR) SUBDIRS=$(PWD) clean
	rm $(APP)