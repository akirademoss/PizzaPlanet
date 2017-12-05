/*
 * WiFi.c
 *
 *  Created on: Sep 25, 2016
 *      Author: ericm
 *  Updates: dmlarson
 *
 * To use WiFi.c
 */

#include <WiFi.h>
#include <uart.h>
#include <lcd.h>

/**
 * starts WiFi bridge
 * @param password a null terminated string to be used as wireless password
 * @return 0 on success, -1 failure
 */
void WiFi_start() {
    //enable port B on pins 2
    GPIO_PORTB_PCTL_R |= 0x100;

    //set pin 2 to digital
    GPIO_PORTB_DEN_R |= BIT2;

    //set pin 2 output
    GPIO_PORTB_DIR_R |= BIT2;

    // enter command
    GPIO_PORTB_DATA_R |= BIT2;

    uart_sendChar(0x0);
    send_string("Z12345678");
    uart_sendChar(0x0);

    char response = uart_receive();

    // exit command
    GPIO_PORTB_DATA_R &= ~BIT2;

    if (response != 0) {
        // an error occured
        lcd_puts("\nWIFI ERROR\n");
    }
}

void wifi_stop() {
    // enter command
    GPIO_PORTB_DATA_R |= BIT2;
    uart_sendChar(0x0);
    char response = uart_receive();
    // exit command
    GPIO_PORTB_DATA_R &= ~BIT2;

    if (response != 0) {
        // an error occured
        lcd_puts("\nWIFI ERROR\n");
    }
}
