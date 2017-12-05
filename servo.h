/*
 * servo.h
 *
 *  Created on: Dec 5, 2017
 *      Author: demoss
 */

#ifndef SERVO_H_
#define SERVO_H_

void timer_1B_init(void);

void motor_init();
unsigned move_servo(unsigned);
void servo_init(void);

#endif /* SERVO_H_ */
