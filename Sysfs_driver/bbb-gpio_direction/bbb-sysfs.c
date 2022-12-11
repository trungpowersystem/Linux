/***********************************************************************************
 * @brief	GPIO sysfs driver (interger-bassed)
 *
 * @author	thanhtrung1998dilang@gmail.com
 * ********************************************************************************/

#include <linux/module.h>	/* This module defines macro such as module_init, module_exit */
#include <linux/fs.h>		/* This module defines macro such as alocate major/ minor number */
#include <linux/device.h>	/* This module defines macro such as class_create/ device create */
#include <linux/cdev.h>		/* This module defines functions sush as kmalloc */
#include <linux/slab.h>		/* This module defines functions such as cdev_init/cdev_add */
#include <linux/uaccess.h>	/* This module defines functions such as copy_to_user/ copy from user */

#define DRIVER_AUTHOR	"thanhtrung1998dilang@gmail.com"
#define	DRIVER_DESC	"GPIO sysfs driver (interger-bassed)"

struct m_foo_dev {
	struct kobject *kobj_ref;
} mdev;

/***************** Function prototypes *****************/
static int	__init hello_world_init(void);
static void	__exit hello_world_exit(void);

/******************* Sysfs functiosn *******************/
static ssize_t sysfs_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static ssize_t sysfs_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count);

struct kobj_attribute m_attr = __ATTR(direction, 0660, sysfs_show, sysfs_store);

/* This function will be called when we read the sysfs file */
static ssize_t sysfs_show(struct kobject *kobj, struct kobj_attribute *attr, char *buff) {
	pr_info("Sysfs read ... \n");
	return 0;
}

/* This fucntion will be called when we write the sysfs file */
static ssize_t sysfs_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count) {
	pr_info("Sysfs write ... \n");
	return 0;
}

static int	__init hello_world_init(void) { 	/* Constructor */
	/* 01. It will create a directory under /sys */
	mdev.kobj_ref = kobject_create_and_add("bbb_gpios", NULL);

	/* 02. Creating sys entry under /sys/bbb_gpios */
	if (sysfs_create_file(mdev.kobj_ref, &m_attr.attr)) {
		pr_err("Cannot create sysfs file");
		goto rm_kobj;
	}

	pr_info("Hello! Initialize successfully!\n");
	return 0;

rm_kobj:
	kobject_put(mdev.kobj_ref);
	return -1;
}

static void	__exit hello_world_exit(void) {		/* Destructor */
	sysfs_remove_file(mdev.kobj_ref, &m_attr.attr); /* 02 */
	kobject_put(mdev.kobj_ref);			/* 01 */
	
	pr_info("Good bye\n");
}

module_init(hello_world_init);
module_exit(hello_world_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_VERSION("1.0");

