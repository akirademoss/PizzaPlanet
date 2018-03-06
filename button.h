/**
 * @file button.h
 * @brief This file contains button functions used to incrementally test our code
 *
 * @authors 	Ann Gould, Akira DeMoss, Devin Uner, Takao Shibamoto
 * @date    	Dec 7, 2017
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include <stdint.h>

#include <inc/tm4c123gh6pm.h>

/**
 * Initializes PORTE and configure bits 5-0 to be used as inputs.
 */
void button_init();

/**
 * returns a 6-bit bit field, representing the push buttons. A 1 means the corresponding button is pressed.
 * @return unit8_t:   Returns the button status
 */
uint8_t button_checkButtons();
 
/**
 * Returns the position of the leftmost button being pushed.
 * @return uint8_t:   The position of the leftmost button being pushed. A 6 is the leftmost button, 1 is the rightmost button.  0 indicates no button being pressed
 */
uint8_t button_getButton();

/**
 *Blocking call
 * @return button:   Highest value button being pressed, waits until at least one button is pressed
 */
uint8_t button_getButtonBlocking();


int8_t button_getButtonChange();

int8_t button_getButtonChangeBlocking();


#endif /* BUTTON_H_ */
