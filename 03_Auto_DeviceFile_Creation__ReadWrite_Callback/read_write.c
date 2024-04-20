#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>


/*META INFORMATION*/
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ram Selvaraj");
MODULE_DESCRIPTION("Register a Device, and implement some callback functions");

/* Buffer for data */
static char buffer[255];
static int buffer_pointer;

// Variables for device and device class
static dev_t caramel_dev_nr;
static struct class *caramel_class;
static struct cdev caramel_device;

#define DRIVER_NAME "carameldriver"
#define DRIVER_CLASS "caramel_driver_class"

/*
 * @brief Read and Write Callback functions
 */

static ssize_t driver_read(struct file *File, char *user_buffer, size_t count, loff_t *offs){
  int to_copy, not_copied, delta;

  // Get amount of data to to copy 
  to_copy = min(count, buffer_pointer); //suppose the buffer_pointer is sitting ahead of the what the actual count.

  // Copy data to user
  not_copied = copy_to_user(user_buffer, buffer, to_copy);

  // Calculate data
  delta = to_copy - not_copied;

  return delta;
}

/** @brief Write data to buffer
 */
//same as read function, but here the user buffer is the source, not the destination, so make it const
static ssize_t driver_write(struct file *File, const char *user_buffer, size_t count, loff_t *offs){
  int to_copy, not_copied, delta;

  // Get amount of data to to copy 
  to_copy = min(count, buffer_pointer); //suppose the buffer_pointer is sitting ahead of the what the actual count.

  // Copy data to user
  not_copied = copy_from_user(buffer, user_buffer, to_copy);
  buffer_pointer = to_copy;
  // Calculate data
  delta = to_copy - not_copied;

  return delta;
}



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
  .read = driver_read,
  .write = driver_write
}; 
/**
  * @brief This function is called when the module is loaded into the kernel
 */

#define MYMAJOR 30

static int __init my_init(void){
  printk("Hello, Popcorn, I am caramel.\n");
  //Allocate a device number
  if (alloc_chrdev_region(&caramel_dev_nr, 0, 1, DRIVER_NAME) < 0){
    printk("Device number could not be allocated");
    return -1;
  }
  printk("read_write - Device number Major: %d, Minor: %d was registered!\n", caramel_dev_nr >> 20, caramel_dev_nr && 0xfffff);

  // Create device class
  if((caramel_class = class_create(THIS_MODULE, DRIVER_CLASS)) == NULL) {
    printk("Device class can not be created!\n");
    goto ClassError;
  }

  // Create Device File
  if(device_create(caramel_class, NULL, caramel_dev_nr, NULL, DRIVER_NAME) == NULL){
    printk("Can not create device file!\n");
    goto FileError;
  }

  //Initialize device file
  cdev_init(&caramel_device, &fops);

  //Registering device to kernel
  if(cdev_add(&caramel_device, caramel_dev_nr, 1) != 1){
    printk("Registering of device to kernel failed!\n");
    goto AddError;
  }
  return 0;
AddError:
  device_destroy(caramel_class, caramel_dev_nr);
FileError:
  class_destroy(caramel_class);
ClassError:
  unregister_chrdev(caramel_dev_nr, DRIVER_NAME);
  return -1;
}



/**
 * @brief This function is called, when the module is removed from the kernel
 */

static void __exit my_exit(void){
  cdev_del(&caramel_device);
  device_destroy(caramel_class, caramel_dev_nr);
  class_destroy(caramel_class);
  unregister_chrdev(caramel_dev_nr, DRIVER_NAME);
  
  printk("Goodbye Popcorn! Regards, caramel.\n");
  unregister_chrdev(MYMAJOR,"caramel_dev_nr");
}

module_init(my_init);
module_exit(my_exit);
