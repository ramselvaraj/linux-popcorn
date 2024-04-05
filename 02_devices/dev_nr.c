#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>

/*META INFORMATION*/
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ram Selvaraj");
MODULE_DESCRIPTION("Register a Device, and implement some callback functions");

/**
 * @brief This funciton is called when the device file is opened
 */
static int device_open(struct inode *device_file, struct file *instance){
  printk("caramel device - open was called\n");
  return 0;
}

/**
 * @brief This funciton is called when the device file is closed
 */
static int device_close(struct inode *device_file, struct file *instance){
  printk("caramel device - close was called\n");
  return 0;
}

/**
 * @brief This struct handles the device open and close callbacks
 * */
static struct file_operations fops = {
  .owner = THIS_MODULE,
  .open = device_open,
  .release = device_close,
}; 
/**
  * @brief This function is called when the module is loaded into the kernel
 */

#define MYMAJOR 30

static int __init my_init(void){
  printk("Hello, Popcorn, I am caramel.\n");
  /* register device number */
  int retval;
  retval = register_chrdev(MYMAJOR, "caramel_dev_nr", &fops);
  if(retval == 0){
    printk("caramel dev_nr - registered Device number Major: %d, Minor: %d\n", MYMAJOR, 0); 
  }
  else if(retval > 0){
      printk("caramel dev_nr - registered Device number Major: %d, Minor, %d\n", retval>>20, retval&0xfffff);
  }
  else{
    printk("Could not register device number\n");
    return -1;
  }
  return 0;
}


/**
 * @brief This function is called, when the module is removed from the kernel
 */

static void __exit my_exit(void){
  printk("Goodbye Popcorn! Regards, caramel.\n");
  unregister_chrdev(MYMAJOR,"caramel_dev_nr");
}

module_init(my_init);
module_exit(my_exit);
