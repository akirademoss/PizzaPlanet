/*
 * WiFi.h
 *
 *  Created on: Sep 25, 2016
 *      Author: ericm
 */

#ifndef WIFI_H_
#define WIFI_H_

#include <stdint.h>
#include <string.h>
#include <inc/tm4c123gh6pm.h>
#include <uart.h>
#include <timer.h>

void WiFi_start();

int WiFi_stop();

#endif /* WIFI_H_ */
