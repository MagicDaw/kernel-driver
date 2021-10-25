#! /bin/sh 

CWD=`pwd`
UNAMER=`uname -r`
echo "Your machine is: ${UNAMER}"		# 4.19.0-18-amd64
echo "/usr/src/linux-headers-${UNAMER}/arch/x86"

# cleanup old executables
if [ -f "mem-kdawid.ko" ]; then
	rm -f mem-kdawid.ko
fi

if [ -f "test" ]; then
	rm -f test
fi

cd src
echo "building kernel driver..."
make

echo "building tester..."
#gcc -I/usr/src/linux-headers-4.19.0-18-common/include/ test.c -o test
gcc test.c -o test

# build kernel object (not working)
#gcc -DMODULE -D__KERNEL__ -isystem "/lib/modules/${UNAMER}/build/include" -I"/usr/src/linux-headers-${UNAMER}/arch/x86/include" -c kernel_driver.c -o mem-kdawid.ko

# copy executables to upper directory
mv mem-kdawid.ko ../
mv test ../

cd ${CWD}
sudo dmesg -C

# install kernel object
sudo insmod "${CWD}/mem-kdawid.ko"

# print loaded modules (just for debug)
#lsmod

sudo dmesg

echo "Done"
