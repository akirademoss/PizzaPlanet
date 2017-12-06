#include <stdint.h>
#include <stdio.h>
#include <inc/tm4c123gh6pm.h>
#include <lcd.h>
#include <Timer.h>
#include <button.h>
#include <WiFi.h>
#include <uart.h>
#include <open_interface.h>
#include <movement.h>
#include <string.h>
#include <math.h>
#include <servo.h>
#include <ping.h>
#include <IR.h>
#include <scan.h>



void UART_init(void);
char UART_Receive(void);
char uart_receive(void);


// IMPORTANT: THIS IS CALIBRATED FOR CYBOT #2!!!!!!!!!!!
// NOTE - the wifi password is the following: Z12345678
// (TODO) - Final remaining logic includes evaluating object widths for mapping // playing with scan functions // tweaking // any scan logic
// (TODO) - calibrate angle for CyBot 2
// (TODO) - Map distance in a 2-D coordinate grid (e.g. declare 3 global variables in main; double totalAngle = N, double totalDistX = N, and double totalDistY = N),
// then update functions in movement.c to return changes in each (note: may need to perform basic trig calculations)  and update distance each time the CyBot moves

//Calibration for CyBot #2

//Blocking call to receive over uart1
//returns char with data
//int last = 0;
main(void)
{
    oi_t *sensor = oi_alloc();
    oi_init(sensor);
    oi_shutoff_init();
    GPIOF_Handler();
    lcd_init();
    UART_init();
    button_init();
    WiFi_start();
    adc_init();
    servo_init();
    ping_init();

    /* ir calibration
    while(1){
        timer_waitMillis(100);
        ir_getDistance();
    }
    */

    //auto_reroute(sensor, 50);

    //NOTE - uncomment this to test scanner
    while(1){
        //timer_waitMillis(1000);
        scan_action();
    }

    //Ann Devin Code
    char buffer[21];
    int i = 0;
    int j = 0;


    char command;
    while(1){
        command = uart_receive();
        if(command != '\r'){
            lcd_printf("the char is: %c\n the index is %d", command, i);
            buffer[i] = command;

            if(command == 'w')
            {
                auto_reroute(sensor,15);
            }
            //rotate 90 degrees clockwise
            if(command == 'f')
            {
                turn(sensor, -90);
            }
            //rotate 45 degrees clockwise
            if(command == 'd')
            {
                turn(sensor, -45);
            }
            //rotate 90 degrees counter clockwise
            if(command == 'a')
            {
                turn(sensor, 90);
            }
            //rotate 45 degrees counter clockwise
            if(command == 's')
            {
                turn(sensor, 45);
            }
            //move backwards 5cm
            if(command == 'b')
            {
                move(sensor,-5,250);
            }
            //scan with ping and IR
            if(command == 'p')
            {
                scan_action();
            }
        }

    }
}

