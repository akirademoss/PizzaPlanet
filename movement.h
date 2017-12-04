/*
 * movement.h
 *
 *  Created on: Sep 7, 2017
 *      Author: demoss
 */

#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include "open_interface.h"
#include "lcd.h"

void move(oi_t *sensor, int centimeters, int velocity_mag);
void turn(oi_t *sensor, int degrees);
void auto_reroute(oi_t *sensor, int centimeters);
void square(oi_t *sensor);

#endif /* MOVEMENT_H_ */

