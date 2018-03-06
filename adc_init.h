/**
 * @file adc_init.h
 * @brief This file contains all functions related to our IR sensor
 *
 * @authors 	Ann Gould, Akira DeMoss, Devin Uner, Takao Shibamoto
 * @date    	Dec 7, 2017
 */

#ifndef ADC_INIT_H_
#define ADC_INIT_H_

/**
  *Setup ADC for GPIO pin 4 port B, ADC module 0 on port D to enable IR sensor functionality
  */
void init_ADC();

/**
 * Returns the distance of an object from the IR sensor
 * Calibration for CyBot #5
 * @return distance:	  Distance an object is relative to the IR sensor (accurate within 2cm over a range from 9 to 80cm)
 */
int ir_stuff();


#endif /* ADC_INIT_H_ */
