#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>

static DECLARE_COMPLETION(test_completion); 
//  初始化Linux驱动
static int __init bad_driver_init(void)
{
    printk("bad_driver_init_success\n");
    return 0;  
}

// 卸载Linux驱动
static void __exit bad_driver_exit(void)
{ 
    //  输出日志信息
    printk("bad_driver_exit_success\n");
    
    wait_for_completion(&test_completion);  

}

//  注册初始化Linux驱动的函数
module_init(bad_driver_init); 
//  注册卸载Linux驱动的函数
module_exit(bad_driver_exit);

MODULE_AUTHOR("lining");
MODULE_DESCRIPTION("bad driver2");
MODULE_LICENSE("GPL");
