/**
 * @file scan.h
 * @brief File containing functions for controlling object detection with IR sensor and Ping
 *
 * @authors 	Ann Gould, Akira DeMoss, Devin Uner, Takao Shibamoto
 * @date    	Dec 7, 2017
 */

#ifndef SCAN_H_
#define SCAN_H_

/// Constant for converting prevent radians and degrees
#define PI 3.14159265

/**
 * Global variables to be used across all functions
 * buffer is the character string sent over UART
 */
char buffer[80];

#include <stdint.h>

#include <inc/tm4c123gh6pm.h>



/// Resets all the variables for consistent scan readings
/**
 * Resets all the variables for consistent scan readings
 */
void scan_reset();

/// Scans from 0 degrees to 180 degrees and returns over UART objects detected and their approximate location.
/**
 * Scans 180 degree arc and marks detected objects
 */
void scan_action();


#endif /* SCAN_H_ */

