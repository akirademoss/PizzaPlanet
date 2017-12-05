#include <stdio.h>
#include <inc/tm4c123gh6pm.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <Timer.h>
#include <lcd.h>

#ifndef IR_H_
#define IR_H_

#include <stdint.h>

void adc_init(void);

unsigned ADC_read(char channel);

float ir_getDistance(void);

#endif /* IR_H_ */
