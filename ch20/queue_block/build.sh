source /root/drivers/common.sh
select_target_noemulator
if [ $selected_target == 1 ]; then
    source ./build_ubuntu.sh
elif [ $selected_target == 2 ]; then
    source ./build_s3c6410.sh
fi
