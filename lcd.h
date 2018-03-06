/**
 * @file lcd.h
 * @brief Functions for displaying content on the 4x16 Character LCD Screen
 *
 * @authors 	Ann Gould, Akira DeMoss, Devin Uner, Takao Shibamoto
 * @date    	Dec 7, 2017
 */

#ifndef LCD_H_
#define LCD_H_

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <inc/tm4c123gh6pm.h>
#include "timer.h"

/**
 * Initialize PORTB0:6 to Communicate with LCD
 */
void lcd_init(void);

/**
 * Send Char to LCD
 */

void lcd_putc(char data);

/**
 * Send Character array to LCD
 */
void lcd_puts(char data[]);

/**
 * Clear LCD Screen
 */
void inline lcd_clear(void);

/**
 * Return Cursor to 0,0
 */
void inline lcd_home(void);

/**
 * Goto Line on LCD - 0 Indexed
 */
void lcd_gotoLine(uint8_t lineNum);

/**
 * Set cursor position - top left is 0,0
 */
void lcd_setCursorPos(uint8_t x, uint8_t y);

/// Print a formatted string to the LCD screen
/**
 * Mimics the C library function printf for writing to the LCD screen.  The function is buffered; i.e. if you call
 * lprintf twice with the same string, it will only update the LCD the first time.
 *
 * Google "printf" for documentation on the formatter string.
 *
 * Code from this site was also used: http://www.ozzu.com/cpp-tutorials/tutorial-writing-custom-printf-wrapper-function-t89166.html
 * @author Kerrick Staley & Chad Nelson
 * @date 05/16/2012
 */
void lcd_printf(const char *format, ...);

#endif /* LCD_H_ */
