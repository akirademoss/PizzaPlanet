/**
 * @file button.c
 * @brief This file contains button functions used to incrementally test our code
 *
 * @authors 	Ann Gould, Akira DeMoss, Devin Uner, Takao Shibamoto
 * @date    	Dec 7, 2017
 */

///The buttons are on PORTE 0:5
#include "button.h"

#define BIT0		0x01
#define BIT1		0x02
#define BIT2		0x04
#define BIT3		0x08
#define BIT4		0x10
#define BIT5		0x20
#define BIT6		0x40
#define BIT7		0x80

#define BUTTON_PORT		GPIO_PORTE_DATA_R

///must be set yourself in button_getButton()
uint8_t _prevButton; 

/**
 * Initialize PORTE and configure bits 5-0 to be used as inputs.
 */
void button_init() {
	static uint8_t initialized = 0;

	///Check if already initialized
	if(initialized)
		return;

	///Turn on PORTE system clock
	SYSCTL_RCGCGPIO_R |= BIT4;

	///Set the buttons to inputs and enable
	GPIO_PORTE_DIR_R &= ~(BIT6 - 1); //Clear bits 5:0
	GPIO_PORTE_DEN_R |= (BIT6 - 1);

	initialized = 1;
}

/**
 * returns a 6-bit bit field, representing the push buttons. A 1 means the corresponding button is pressed.
 * @return unit8_t:   Returns the button status
 */
uint8_t button_checkButtons() {
	///Return the button status
	return (~BUTTON_PORT) & (BIT6 - 1); 
}

/**
 * Returns the position of the leftmost button being pushed.
 * @return uint8_t:   The position of the leftmost button being pushed. A 6 is the leftmost button, 1 is the rightmost button.  0 indicates no button being pressed
 */
uint8_t button_getButton() {

    if(BUTTON_PORT % 2 == 0){
        return 1;
    }
    if(BUTTON_PORT/2 % 2== 0){
            return 2;
        }
    if(BUTTON_PORT/4 % 2 == 0){
           return 3;
       }
       if(BUTTON_PORT/8 % 2== 0){
               return 4;
           } if(BUTTON_PORT/16 % 2 == 0){
               return 5;
           }
           if(BUTTON_PORT/32 % 2== 0){
                   return 6;
               }

	
	return 0; 
}

/**
 *Blocking call
 *
 * @return button:   Highest value button being pressed, waits until at least one button is pressed
 */
uint8_t button_getButtonBlocking() {
	uint8_t button;

	///Wait for button to be pressed
	while( (button = button_getButton()) == 0 );

	return button;
}

int8_t button_getButtonChange() {
	///_prevButton can be set in button_getButton if you want to use this function.
	uint8_t lastButton = _prevButton; 
	int8_t curButton = button_getButton();

	if(curButton != lastButton) {
		return curButton;
	}
	else {
		return -1;
	}
}


int8_t button_getButtonChangeBlocking() {
	int8_t button;

	while( (button = button_getButtonChange()) == -1);

	return button;
}
