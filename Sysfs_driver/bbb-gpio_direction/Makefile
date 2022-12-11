#Hello world kernel module
KERNEL = ~/bb-kernel/lib/modules/4.19.94/build
CROSS = ~/Desktop/Homework/Toolchain/gcc-linaro-6.5.0-2018.12-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-
obj-m += bbb-sysfs.o

all:
	make ARCH=arm CROSS_COMPILE=${CROSS} -C ${KERNEL} M=$(PWD) modules
clean:
	make -C ${KERNEL} M=$(PWD) clean

