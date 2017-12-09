/**
 * @file sonar.h
 * @brief File containing functions for controlling the sonar sensor
 *
 * @authors 	Ann Gould, Akira DeMoss, Devin Uner, Takao Shibamoto
 * @date    	Dec 7, 2017
 */



#ifndef SONAR_H_

#define SONAR_H_
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <inc/tm4c123gh6pm.h>
#include "timer.h"

#include "lcd.h"
#include <stdbool.h>
#include "driverlib/interrupt.h"

/**
 * Initialize the timers
 */
void ping_init();

/**
 * start and read the ping sensor once, return distance in mm
 *
 *@return time2dist		Returns the pulse width
 */
unsigned ping_read();

/**
 * ping sensor related to ISR
 */
void TIMER3B_Handler(void);

/**
 * send out a pulse on PB3
 */
void send_pulse();

/**
 * convert time in clock counts to single-trip distance in mm
 *
 * @return  Returns distance in mm
 */
unsigned time2dist(unsigned);


#endif /* SONAR_H_ */
