ccflags-y := -I$(PWD)/inc
ifneq ($(KERNELRELEASE),)
# kbuild part of makefile
obj-m := hello7_1.o hello7_2.o
ccflags-y += -g -DDEBUG
else
# normal makefile
KDIR ?= /lib/modules/`uname -r`/build
default:
	$(MAKE) -C $(KDIR) M=$$PWD
	cp hello7_1.ko hello7_1.ko.unstripped
	cp hello7_2.ko hello7_2.ko.unstripped
	$(CROSS_COMPILE)strip -g hello7_1.ko
	$(CROSS_COMPILE)strip -g hello7_2.ko
clean:
	$(MAKE) -C $(KDIR) M=$$PWD clean
%.s %.i: %.c
	$(MAKE) -C $(KDIR) M=$$PWD $@
endif
