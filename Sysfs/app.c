/****************************************************************
 * @brief	User space application to test gpio - sysfs
 *
 * @author	thanhtrung1998dilang@gmail.com
 ***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "gpio.h"

#define LED	( 31 )

int main() {
	printf("**************************\n");
	printf("**********Sysfs***********\n");

	GPIOExport(LED);
	GPIODirection(LED, OUT);
	GPIOWrite(LED, HIGH);

	return 0;
}
