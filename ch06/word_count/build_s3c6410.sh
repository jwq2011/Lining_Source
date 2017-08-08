# build_s3c6410.sh
source /root/drivers/common.sh
make  -C $S3C6410_KERNEL_PATH  M=${PWD}
find_devices 
if [ "$selected_device" == "" ]; then 
    exit
else
    adb -s $selected_device push ${PWD}/word_count.ko /data/local
    testing=$(adb -s $selected_device shell lsmod | grep  "word_count")
    if [ "$testing" != "" ]; then
	adb -s $selected_device shell rmmod word_count
    fi
    adb -s $selected_device shell "insmod /data/local/word_count.ko"
    adb -s $selected_device shell  "chmod 777 /dev/wordcount"

fi

