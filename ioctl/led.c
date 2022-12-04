#include <linux/module.h>		/* Thu vien nay dinh nghia cac macro nhu module_init va module_exit */
#include <linux/io.h>			/* Thu vien nay dinh nghia cac macro nhu ioremap, iounmap */
#include <linux/fs.h>			/* Thu vien nay dinh nghia major/minor number */
#include <linux/device.h>		/* Thu vien nay dinh nghia cac function class_create/ device_create */
#include <linux/cdev.h>			/* Thu vien nay dinh nghia cac function cdev_init/ cdev_add */
#include <linux/slab.h>			/* Thu vien nay dinh nghia cac function cdev_init/ cdev_add */
#include "led.h"			/*__LED_MODULE_H__*/

#define DRIVER_AUTHOR 	"thanhtrung1998dilang@gmail.com"
#define DRIVER_DESC 	"Led module with ioctl"
#define DRIVER_VERS	"1.0"

#define LED_ON		_IOW('a', '1', int32_t *)
#define LED_OFF		_IOW('a', '0', int32_t *)

uint32_t __iomem *base_addr;

struct m_foo_dev {
	dev_t dev_num;
	struct class *m_class;
	struct cdev m_cdev;
} mdev;

/*	Function prototype	*/
static int __init led_init(void);
static void __exit led_exit(void);
static long m_ioctl(struct file *file, unsigned int cmd, unsigned long arg);

static struct file_operations fops = {
	.owner			= THIS_MODULE,
	.unlocked_ioctl	= m_ioctl,
};

static long m_ioctl(struct file *file, unsigned int cmd, unsigned long arg) {
	switch(cmd) {
		case LED_ON:
			pr_info("LED ON\n");
			*(base_addr + GPIO_SETDATAOUT_OFFSET / 4) |= LED;
			break;
		case LED_OFF:
			pr_info("LED OFF\n");
			*(base_addr + GPIO_CLEARDATAOUT_OFFSET / 4) |= LED;
			break;
		default:
			pr_info("Default\n");
			break;
	}
	return 0;
}

static int __init led_init(void) {      //Constructor
        //1. Alocating device number (cat /proc/devices)
	base_addr = ioremap(GPIO_0_ADDR_BASE, GPIO_0_ADDR_SIZE);
	*(base_addr + GPIO_OE_OFFSET / 4) &= ~LED;
        if (alloc_chrdev_region(&mdev.dev_num, 0, 1, "m-cdev") < 0) {
                pr_err("Failed to alloc chrdev region\n");
                return -1;
        }
        pr_info("Major = %d Minor = %d\n", MAJOR(mdev.dev_num), MINOR(mdev.dev_num));

        //2.1 Creating cdev structure
        cdev_init(&mdev.m_cdev, &fops);

        //2.2 Add charater device to the system
        if ((cdev_add(&mdev.m_cdev, mdev.dev_num, 1)) < 0) {
                pr_err("Cannot add the device to the system\n");
                goto rm_device_numb;
        }

        //3. Creating struct class
        if ((mdev.m_class = class_create(THIS_MODULE, "m_class")) == NULL) {
                pr_err("Cannot create the struct class for my device\n");
                goto rm_device_numb;
        }

        //4. Creating device
        if ((device_create(mdev.m_class, NULL, mdev.dev_num, NULL, "m_device")) == NULL) {
                pr_err("Cannot create my device\n");
                goto rm_class;
	}

        pr_info("Led kernel module with ioctl\n");
        return 0;
rm_class:
        class_destroy(mdev.m_class);
rm_device_numb:
        unregister_chrdev_region(mdev.dev_num, 1);
        return -1;
}

static void __exit led_exit(void) {             //Destructor
	iounmap(base_addr);
        device_destroy(mdev.m_class, mdev.dev_num);     //04
        class_destroy(mdev.m_class);                    //03
        cdev_del(&mdev.m_cdev);                         //02
        unregister_chrdev_region(mdev.dev_num, 1);      //01
        pr_info("Goodbye\n");
}

module_init(led_init);
module_exit(led_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
	

