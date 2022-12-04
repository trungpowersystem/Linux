#include <linux/module.h>		/* Thu vien nay dinh nghia cac macro nhuw module_init va module_exit */
#include <linux/io.h>			
#include "led.h"			/*__LED_MODULE_H__*/

#define DRIVER_AUTHOR 	"thanhtrung1998dilang@gmail.com"
#define DRIVER_DESC 	"Led module"
//#define DRIVER_VERS	"1.0"

uint32_t __iomem *base_addr;

/* Constructor */
static int __init led_init(void) {
	base_addr = ioremap(GPIO_0_ADDR_BASE, GPIO_0_ADDR_SIZE);
	if(!base_addr)
		return -ENOMEM;
	*(base_addr + GPIO_OE_OFFSET / 4) &= ~LED;
	*(base_addr + GPIO_SETDATAOUT_OFFSET / 4) |= LED;

	pr_info("LED ON\n");
	return 0;
}

/* Destructor */
static void __exit led_exit(void) {
	*(base_addr + GPIO_CLEARDATAOUT_OFFSET / 4) |= LED;
	iounmap(base_addr);
       
	pr_info("Led OFF\n");	       
}

module_init(led_init);
module_exit(led_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
