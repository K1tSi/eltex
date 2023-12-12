#include <linux/module.h>    // included for all kernel modules
#include <linux/kernel.h>    // included for KERN_INFO
#include <linux/init.h>      // included for __init and __exit macros

MODULE_LICENSE("LFM");
MODULE_AUTHOR("Nikitak");
MODULE_DESCRIPTION("A Simple Hi_World module");

static int __init hi_init(void)
{
    printk(KERN_INFO "Hi_world! How r u?\n");
    return 0;    // Non-zero return means that the module couldn't be loaded.
}

static void __exit hi_cleanup(void)
{
    printk(KERN_INFO "Cleaning up module.\n");
}

module_init(hi_init);
module_exit(hi_cleanup);