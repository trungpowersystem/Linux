#ifndef GPIO_H
#define GPIO_H

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>
#include <time.h>
#include <errno.h>

#define IN	( 0 ) //GPIO direction as input
#define OUT	( 1 ) //GPIO direction as output

#define LOW	( 0 ) //GPIO value low
#define HIGH	( 1 ) //GPIO value high

#define BUFFER_MAX	( 4 )
#define DIRECTION_MAX	( 35 )

#define VALUE_MAX 	( 30 )

/********************************************************
 *	Function prototype
 *******************************************************/

/**
 ** @brief Export GPIO pin
 ** @param[in] pin_: gpio pin number
 ** @return 0 if success
 ** 	  -1 otherwise
 **/
int32_t GPIOExport (int32_t pin_);
	
/**
 ** @brief Set GPIO direction
 ** @param[in] pin_ : gpio pin number
 ** @param[in] dir_ : pin direction (IN or OUT)
 ** @return 0 if success
 **	   -1 otherwise
 **/
int32_t GPIODirection (int32_t pin_, int32_t dir_);

/**
 ** @brief Write value on GPIO pin
 ** @param[in] pin_ : gpio pin number
 ** @param[in[ value_ : gpio pin value (HIGH OR LOW)
 ** return 0 if success
 **	  -1 otherwise
 **/
int32_t GPIOWrite (int32_t pin_, int32_t value_);
#endif


