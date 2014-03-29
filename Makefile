obj-m := x7.o
KERNDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

all: x7.c
	make -C $(KERNDIR) SUBDIRS=$(PWD) modules
test: x7.ko
	sudo insmod $<
	sudo rmmod $<
	sleep 2
	dmesg | tail
clean:
	$(RM) *.o *.ko *.mod.c *.order *.symvers
.PHONY: clean
