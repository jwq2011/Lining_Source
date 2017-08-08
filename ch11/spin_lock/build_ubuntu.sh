# build_ubuntu.sh
source /root/drivers/common.sh
make   -C  $UBUNTU_KERNEL_PATH  M=$PWD
gcc -static  -o test_rw_lock $PWD/test_rw_lock.c
testing=$(lsmod | grep  "spin_lock")
if [ "$testing" != "" ]; then
    rmmod spin_lock
fi

testing=$(lsmod | grep  "rw_lock")
if [ "$testing" != "" ]; then
    rmmod rw_lock
fi

testing=$(lsmod | grep  "seq_lock")
if [ "$testing" != "" ]; then
    rmmod seq_lock
fi


insmod $PWD/spin_lock.ko
insmod $PWD/rw_lock.ko lock_type=$lock_type
insmod $PWD/seq_lock.ko

