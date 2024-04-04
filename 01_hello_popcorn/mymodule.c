#include <linux/module.h>
#include <linux/init.h>

/*META INFORMATION*/
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ram Selvaraj");
MODULE_DESCRIPTION("A hello world from the LKM(Linux Kernel Module)");

/**
  * @breif This function is called when the module is loaded into the kernel
 */

static int __init my_init(void){
  printk("Hello, Popcorn!\n");
  return 0;
}


/**
 * @brief This function is called, when the module is removed from the kernel
 */

static void __exit my_exit(void){
  printk("Goodbye, Popcorn!\n");
}

module_init(my_init);
module_exit(my_exit);
