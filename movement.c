/**
 * @file movement.c
 * @brief Commands for moving the CyBot
 *
 * @authors 	Ann Gould, Akira DeMoss, Devin Uner, Takao Shibamoto
 * @date    	Dec 7, 2017
 */

#include "movement.h"
#include "lcd.h"
#include "Timer.h"
#include "uart.h"
#include "string.h"


/**
 * Simple movement function (+N) is forward motion (-N) is backward motion
 *
 * @param sensor        Allocates the bot's sensor data
 * @param centimeters   Distance to move the bot in centimeters
 * @param velocity_mag  Magnitude of velocity for the bot to travel
 */
void move(oi_t *sensor, int centimeters, int velocity_mag)
{
    oi_setWheels((centimeters > 0) ? velocity_mag : -1*velocity_mag, (centimeters > 0) ? velocity_mag : -1*velocity_mag);
    int sum = 0;
        while (abs(sum)<abs(centimeters*10))
        {
            oi_update(sensor);
            sum += sensor->distance;
        }
        oi_setWheels(0, 0); // stop
}

/**
 * Simple turn function (+N) is counter-clockwise (-N) is clockwise
 *
 * @param sensor	 Allocates the bot's sensor data
 * @param degrees	 Amount to turn the bot in degrees
 */
void turn(oi_t *sensor, int degrees)
{
    lcd_init();
    /// char msg[81] = "";
    oi_setWheels((degrees > 0) ? 100 : -100, (degrees > 0) ? -100 : 100);
    int sum = 0;
    while(abs(sum)<abs(degrees))
    {
        oi_update(sensor);
        sum += sensor->angle;
    }
    oi_setWheels(0, 0); // stop
}

/**
 * Moves the bot forward or backward N centimeter
 * e.g. "collision_avoidance(sensor, N);" --> if N = 10 moves forward 15cm.  if N = -10 moves backward 10cm
 * Integrated pothole avoidance and white boundary line avoidance
 * When hits a pothole or white boundary line moves backward the distance traveled before it hit the object
 *
 * @param sensor	 	Allocates the bot's sensor data
 * @param centimeters   Distance to move the bot in centimeters
 */

void auto_reroute(oi_t *sensor, int centimeters){
     ///include lcd_init() for print testing
     lcd_init();
     oi_setWheels((centimeters > 0) ? 100 : -100, (centimeters > 0) ? 100 : -100);
     char msg[81] = "none";
     int sum = 0;

    ///This variable is the distance left in the forward (x) direction after the CyBot has hit a bump, pothole or white boundary line
    int x = 0;
    int milimeters = centimeters*10;
        while (abs(sum)<abs(milimeters))
        {
            oi_update(sensor);
            sum += sensor->distance;

            x = (sum/10);

            if(sensor->bumpLeft == 1)
            {
                move(sensor,x * -1,250);
                sum = abs(milimeters);
                sprintf(msg, "{\"class\":1,\"type\": \"bump-left\", \"distance\": %d}\n", x);
                send_string(msg);
                lcd_printf(msg);
            }

            else if(sensor->bumpRight == 1)
            {
                move(sensor,x * -1,250);
                sum = abs(milimeters);
                sprintf(msg, "{\"class\":1,\"type\": \"bump-right\", \"distance\": %d}\n", x);
                send_string(msg);
                lcd_printf(msg);
            }

            ///cliff
            else if(sensor-> cliffFrontRightSignal < 800)
            {
                move(sensor, x * -1, 250);
                sprintf(msg, "{\"class\":1,\"type\": \"cliff-right\", \"distance\": %d}\n", x);
                send_string(msg);
                lcd_printf(msg);
                sum = abs(milimeters);
            }

            else if(sensor-> cliffRightSignal < 800)
            {
                move(sensor, x * -1, 250);
                sprintf(msg, "{\"class\":1,\"type\": \"cliff-right\", \"distance\": %d}\n", x);
                send_string(msg);
                lcd_printf(msg);
                sum = abs(milimeters);
            }

            else if(sensor-> cliffFrontLeftSignal < 800)
            {
                move(sensor, x * -1, 250);
                sprintf(msg, "{\"class\":1,\"type\": \"cliff-left\", \"distance\": %d}\n", x);
                send_string(msg);
                lcd_printf(msg);
                sum = abs(milimeters);
            }

            else if(sensor-> cliffLeftSignal < 800)
            {
                move(sensor, x * -1, 250);
                sprintf(msg, "{\"class\":1,\"type\": \"cliff-left\", \"distance\": %d}\n", x);
                send_string(msg);
                lcd_printf(msg);
                sum = abs(milimeters);
            }

            ///white line
            else if((sensor->cliffFrontRight) || ((sensor->cliffFrontRightSignal) > 2750))
            {
                move(sensor, x * -1, 250);
                char msg[81] = "";
                sprintf(msg, "{\"class\":1,\"type\": \"white-line\", \"distance\": %d}\n", x);
                send_string(msg);
                lcd_printf(msg);
                sum = abs(milimeters);
            }

            else if((sensor->cliffRight) || ((sensor->cliffRightSignal) > 2750))
            {
                move(sensor, x * -1, 250);
                char msg[81] = "";
                sprintf(msg, "{\"class\":1,\"type\": \"white-line\", \"distance\": %d}\n", x);
                send_string(msg);
                lcd_printf(msg);
                sum = abs(milimeters);
            }

            else if((sensor->cliffFrontLeft) || ((sensor->cliffFrontLeftSignal) > 2750)){
                move(sensor, x * -1, 250);
                char msg[81] = "";
                sprintf(msg, "{\"class\":1,\"type\": \"white-line\", \"distance\": %d}\n", x);
                send_string(msg);
                lcd_printf(msg);
                sum = abs(milimeters);
            }

            else if((sensor->cliffLeft) || ((sensor->cliffLeftSignal) >2750))
            {
                move(sensor, x * -1, 250);
                char msg[81] = "";
                sprintf(msg, "{\"class\":1,\"type\": \"white-line\", \"distance\": %d}\n", x);
                send_string(msg);
                lcd_printf(msg);
                sum = abs(milimeters);
            }

        }

        if(strcmp(msg, "none") == 0){
            sprintf(msg, "{\"class\":0, \"type\": \"move_forward\", \"distance\": %d}\n", x);
            send_string(msg);
        }
        oi_setWheels(0, 0); /// stop
    }

