/**
 * @file movement.h
 * @brief Commands for moving the CyBot
 *
 * @authors 	Ann Gould, Akira DeMoss, Devin Uner, Takao Shibamoto
 * @date    	Dec 7, 2017
 */

#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include <open_interface.h>
#include <lcd.h>

/**
 * Simple movement function (+N) is forward motion (-N) is backward motion
 *
 * @param sensor        Allocates the bot's sensor data
 * @param centimeters   Distance to move the bot in centimeters
 * @param velocity_mag  Magnitude of velocity for the bot to travel
 */
void move(oi_t *sensor, int centimeters, int velocity_mag);

/**
 * Simple turn function (+N) is counter-clockwise (-N) is clockwise
 *
 * @param sensor	 Allocates the bot's sensor data
 * @param degrees	 Amount to turn the bot in degrees
 */
void turn(oi_t *sensor, int degrees);

/**
 * Moves the bot forward or backward N centimeter
 * e.g. "collision_avoidance(sensor, N);" --> if N = 10 moves forward 15cm.  if N = -10 moves backward 10cm
 * Integrated pothole avoidance and white boundary line avoidance
 * When hits a pothole or white boundary line moves backward the distance traveled before it hit the object
 *
 * @param sensor	 	Allocates the bot's sensor data
 * @param centimeters   Distance to move the bot in centimeters
 */
void auto_reroute(oi_t *sensor, int centimeters);


#endif /* MOVEMENT_H_ */
