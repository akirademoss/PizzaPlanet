/**
 * @file servo.c
 * @brief File containing functions for controlling the servo motor
 *
 * @authors 	Ann Gould, Akira DeMoss, Devin Uner, Takao Shibamoto
 * @date    	Dec 7, 2017
 */

#include "button.h"
#include "timer.h"
#include "lcd.h"
#include "servo.h"


unsigned pulse_period=320000;

///This function initializes the motor and timers
/**
 * Initialize GPIO PORT B, configure pin 6 for digital enable, 
 * configure alternative function through AFSEL and PCTL [Table 2.6],
 * configures appropriate timers
 */
void servo_init(){
    SYSCTL_RCGCGPIO_R|=0x02;

    GPIO_PORTB_DEN_R|=0b00100000;
    GPIO_PORTB_DIR_R|=0x20;
    GPIO_PORTB_AFSEL_R|=0x20;
    GPIO_PORTB_PCTL_R|=0x00700000;

    SYSCTL_RCGCTIMER_R|=0x02;
    TIMER1_CTL_R&=0xFFFFFEFF;
    TIMER1_TBMR_R|=0x0A;
    TIMER1_CFG_R|=TIMER_CFG_16_BIT;
    TIMER1_TBILR_R=pulse_period & 0xFFFF;
    TIMER1_TBPR_R=pulse_period>>16;
    TIMER1_TBMATCHR_R=(pulse_period-24000)&0xFFFF;
    TIMER1_TBPMR_R=(pulse_period-24000)>>16;
    TIMER1_CTL_R|=(0x0100);
}

/**
 * Moves servo to a specified degree between 0 and 180 degrees.
 * @param deg 
 */
void servo_t(unsigned deg){
    unsigned pulse_width;
    int matchr;
    float sum;
    float degs;
    degs=((double)deg)/180;
    sum= 1+degs;
    ///Cybot 5
    pulse_width=((deg*.0000095)+.000645)*16000000;
    matchr=pulse_period-pulse_width;
    TIMER1_TBMATCHR_R=matchr;
    TIMER1_TBPMR_R=matchr>>16;
}


