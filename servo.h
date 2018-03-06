/**
 * @file servo.h
 * @brief File containing functions for controlling the servo motor
 *
 * @authors 	Ann Gould, Akira DeMoss, Devin Uner, Takao Shibamoto
 * @date    	Dec 7, 2017
 */

#ifndef SERVO_H_
#define SERVO_H_


///This function initializes the motor and timers
/**
 * Initialize GPIO PORT B, configure pin 6 for digital enable, 
 * configure alternative function through AFSEL and PCTL [Table 2.6],
 * configures appropriate timers
 */
void motor_init();

/**
 * Moves servo to a specified degree between 0 and 180 degrees.
 * @param deg 
 */
void servo_t(unsigned deg);

#endif /* SERVO_H_ */
