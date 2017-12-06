/*
 * servo.c
 *
 *  Created on: Dec 5, 2017
 *      Author: demoss
 */

#include <servo.h>

#include <timer.h>
#include <lcd.h>
#include <button.h>
#include <Wifi.h>
#include <uart.h>
#include <math.h>
#include <driverlib/interrupt.h>


/// Time servo will wait between movements
uint32_t servo_wait = 50; // wait time in ms


/// Initialize the timers
/**
 *
 */
void timer1B_init(void) {

    unsigned pulse_period = 320000;
    unsigned mid_width = 0;

    SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R1; // Turn on clock to TIMER1B
    TIMER1_CTL_R &= ~TIMER_CTL_TBEN; //disable TIMER1B
    TIMER1_CFG_R |= TIMER_CFG_16_BIT; //set to 16bit
    TIMER1_TBMR_R |= TIMER_TBMR_TBMR_PERIOD|TIMER_TBMR_TBAMS; //set to periodic and alternate mode
    TIMER1_TBPR_R = (pulse_period >> 16) & 0xFF; //set timer prescaler
    TIMER1_TBILR_R = pulse_period & 0xFFFF; //set period
    TIMER1_TBPMR_R = (296000 >> 16) & 0xFF; // set match prescaler
    TIMER1_TBMATCHR_R = (pulse_period - mid_width) & 0xFFFF; // set timer value for initial intpt

    // enable timer1b
    TIMER1_CTL_R |= TIMER_CTL_TBEN;
}

/// Initialize the servo motor
/**
 *
 */
void motor_init(){
    SYSCTL_RCGCGPIO_R |= 0x2;

    GPIO_PORTB_AFSEL_R |= BIT5;
    GPIO_PORTB_DEN_R |= BIT5;
    GPIO_PORTB_DIR_R |= BIT5;

    GPIO_PORTB_PCTL_R |= 0x700000;
}

/// Moves servo to a specified degree between 0 and 180 degrees.
/**
 *
 */
unsigned move_servo(unsigned degree){
    int counter = (double)(degree+50.20922)/0.006172; // cybot 8
    TIMER1_TBMATCHR_R = (0x4E200 - counter) & 0xFFFF;
    TIMER1_TBPMR_R = (0x4E200 - counter) >> 16;
    return counter;
}

/// Initializes the servo components
/**
 *
 */
void servo_init(void) {
    motor_init();
    button_init();
    timer1B_init();
}


