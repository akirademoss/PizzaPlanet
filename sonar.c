/**
 * @file sonar.c
 * @brief File containing functions for controlling the sonar sensor
 *
 * @authors 	Ann Gould, Akira DeMoss, Devin Uner, Takao Shibamoto
 * @date    	Dec 7, 2017
 */

#include "sonar.h"
#include "timer.h"
#include "lcd.h"

#define BIT0        0x01
#define BIT1        0x02
#define BIT2        0x04
#define BIT3        0x08
#define BIT4        0x10
#define BIT5        0x20
#define BIT6        0x40
#define BIT7        0x80


volatile enum {LOW, HIGH, DONE} state;
/// start time of the return pulse
volatile unsigned rising_time; 
/// end time of the return pulse
volatile unsigned falling_time; 
volatile unsigned event_time;


/**
 * Initialize the timers
 */
void ping_init(void) {

    ///enable clock to GPIO, R1 = port B
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;
    GPIO_PORTB_PCTL_R |= 0x7000;
    GPIO_PORTB_DEN_R |= BIT3; /// set PB3 to digital
    GPIO_PORTB_DIR_R |= BIT3; /// set PB3 as output

    SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R3; /// Turn on clock to TIMER3

    ///Configure the timer for input capture mode
    TIMER3_CTL_R &= ~TIMER_CTL_TBEN; ///disable timer3B to allow us to change settings
    TIMER3_CFG_R |= TIMER_CFG_16_BIT; ///set to 16 bit timer

    TIMER3_TBMR_R |= 0x17; ///set for capture mode, edge-time mode, and count up

    /// set trigger on both edges in timer3b
    TIMER3_CTL_R |= TIMER_CTL_TBEVENT_BOTH;

    TIMER3_TBILR_R = ~(int)0; /// set upper bound

    TIMER3_IMR_R |= TIMER_IMR_CBEIM; ///enable TIMER3B capture mode interrupt mask


    ///initialize local interrupts
    NVIC_EN1_R |= 0x10; /// interrupt number 36
    ///go to page 105 and find the corresponding interrupt numbers for TIMER3B
    ///then set those bits in the correct interrupt set EN register (p. 142)

    /// Register interrupt to handler function
    IntRegister(INT_TIMER3B, TIMER3B_Handler);
    IntMasterEnable(); ///intialize global interrupts

    /// enable timer3b
    TIMER3_CTL_R |= TIMER_CTL_TBEN;
}

/**
 * start and read the ping sensor once, return distance in mm
 *
 *@return time2dist		Returns the pulse width
 */
unsigned ping_read() {
    send_pulse(); // send the starting pulse to PING
    state = LOW;

    /// Calculate the width of the pulse; convert to centimeters
    return time2dist(falling_time-rising_time);
}

/**
 * ping sensor related to ISR
 */
void TIMER3B_Handler(void) {
    event_time = TIMER3_TBR_R;

    /// read current event time
    if (state == LOW){
        state = HIGH;
        rising_time = event_time;
    } else if (state == HIGH){
        state = DONE;
        falling_time = event_time;
    }

    TIMER3_ICR_R = TIMER_ICR_CBECINT;
}

/**
 * send out a pulse on PB3
 */
void send_pulse() {
    GPIO_PORTB_AFSEL_R &= ~BIT3; /// disable alternate functions on PB3
    GPIO_PORTB_DIR_R |= BIT3; /// set PB3 as output
    GPIO_PORTB_DATA_R |= BIT3; /// set PB3 to high
    /// wait at least 5 microseconds based on data sheet
    timer_waitMicros(5);
    GPIO_PORTB_DATA_R &= ~BIT3; /// set PB3 to low
    GPIO_PORTB_DIR_R &= ~BIT3; /// set PB3 as input
    GPIO_PORTB_AFSEL_R |= BIT3; /// enable alternate functions on PB3
}

/**
 * convert time in clock counts to single-trip distance in mm
 *
 * @return  Returns distance in mm
 */
unsigned time2dist(unsigned time) {
    const int SOUND_SPEED = 34000;
    const int CLOCK_RATE = 16;
    return ((time/CLOCK_RATE)*SOUND_SPEED/2)/1000000;
}

