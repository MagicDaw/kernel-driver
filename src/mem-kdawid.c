/**
 * This is my simple kernel driver (module)
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/kdev_t.h>
#include <linux/cdev.h>
#include "mem-definitions.h"

MODULE_LICENSE("GPL");

/**
 * Function from <asm/io.h> to be used
 * static inline phys_addr_t virt_to_phys(volatile void *address)
 */

int openCallback(struct inode *ind, struct file *fp)
{
    // TODO
    return 0;
}

long ioctlCallback(struct file *fp, unsigned int fa,  long unsigned int sa)
{
    // TODO
    return 0;
}

struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = openCallback,
    .unlocked_ioctl = ioctlCallback
};

//int devMajor;	// device major number
dev_t dev;
struct class *devClassPtr;
struct device *devicePtr;
struct cdev cdev1;

void cleanup(void)
{
	//if (0 < devMajor) {
		if (!IS_ERR_OR_NULL(devClassPtr)) {
			cdev_del(&cdev1);
			device_destroy(devClassPtr, dev);
			class_destroy(devClassPtr);
		}
	//unregister_chrdev(devMajor, "mem-kdawid");
	unregister_chrdev_region(dev, 1);
	//}
}

int start(void)
{
	printk(KERN_INFO "Initializing mem-kdawid kernel module\n");

	// devMajor = register_chrdev(0, "mem-kdawid", &fops); (this is older way... which dont work for me :)
    if (alloc_chrdev_region(&dev, 0, 1, "mem-kdawid")) {
        printk(KERN_INFO "Device region allocation failed\n");
		return -1;
    }

	printk(KERN_INFO "Device succesfully registered\n");
	devClassPtr = class_create(THIS_MODULE, "test-dev");
    
	if (IS_ERR_OR_NULL(devClassPtr)) {
		printk(KERN_INFO "Failed to create device class\n");
		cleanup();
		return -2;
	}

	printk(KERN_INFO "Device class created\n");
	devicePtr = device_create(devClassPtr, NULL, dev, NULL, "mem-kdawid");

	if (NULL == devicePtr) {
		printk(KERN_INFO "Creating device failed\n");
		cleanup();
		return -3;	
	}

	printk(KERN_INFO "Device created\n");
	cdev_init(&cdev1, &fops);		
	printk(KERN_INFO "Cdev initialized\n");
	cdev1.owner = THIS_MODULE;	
	cdev_add(&cdev1, dev, 1);
	printk(KERN_INFO "Cdev added\n");
	return 0;
}

void stop(void)
{
	printk(KERN_INFO "Exiting mem-kdawid kernel module\n");
	cleanup();
    printk(KERN_INFO "Cleanup complete\n");
}

module_init(start);
module_exit(stop);