/**
 * @file WiFi.h
 *
 *  Created on: Sep 25, 2016
 *      Author: ericm
 *  Updates: dmlarson
 *
 */

#ifndef WIFI_H_
#define WIFI_H_

#include <stdint.h>
#include <string.h>
#include <inc/tm4c123gh6pm.h>
///#error change the include statement below to point to your own header file
#include "uart.h"
#include "timer.h"

/**
 * starts WiFi bridge
 * @param password a null terminated string to be used as wireless password
 * @return 0 on success, -1 failure
 */
int WiFi_start(char *password);

int WiFi_stop();

uint8_t _sendCommand(uint8_t command, uint8_t* param, uint8_t len);

#endif /* WIFI_H_ */
