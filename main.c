/**
 * @file main.c
 * @brief Commands for operating the CyBot
 *
 * @authors 	Ann Gould, Akira DeMoss, Devin Uner, Takao Shibamoto
 * @date    	Dec 7, 2017
 */



#include <stdint.h>
#include "lcd.h"
#include "Timer.h"
#include "button.h"
#include "WiFi.h"
#include "uart.h"
#include "movement.h"
#include "music.h"
#include "open_interface.h"
#include "scan.h"
#include "adc_init.h"
#include "servo.h"
#include "sonar.h"


void UART_init(void);
char UART_Receive(void);
char uart_receive(void);

/**
 *Commands for our CyBot
 */
void command(void)
{

    oi_t *sensor = oi_alloc();
    oi_init(sensor);
    oi_shutoff_init();
    GPIOF_Handler();
    load_songs();
    char buffer[21];
    int i = 0;
    int j = 0;
    lcd_init();
    UART_init();
    button_init();
    init_ADC();
    servo_init();
    ping_init();

    char temp;
    char msg[300];
    char pass[] = "annIsCool";
    WiFi_start(pass);

    while(1){
        temp = uart_receive();
        if(temp != '\r'){
            lcd_printf("the char is: %c\n the index is %d", temp, i);
            buffer[i] = temp;
            if(temp == 'u'){
                auto_reroute(sensor, 10);/// movement data sent in the auto_reroute function
            }
            if(temp =='r'){
              turn(sensor, -22.5);
              sprintf(msg, "{\"class\":0,\"type\": \"turn-right\"}\n");
              send_string(msg);
            }
            if(temp == 'l'){
               turn(sensor, 22.5);
               sprintf(msg, "{\"class\":0,\"type\": \"turn-left\"}\n");
               send_string(msg);

            }
            if(temp == 'd'){
                move(sensor, -10, 100);
                sprintf(msg, "{\"class\":0,\"type\": \"move-down\", \"distance\": 10}\n");
                send_string(msg);
            }
            if(temp=='s'){
                scan_action();
                sprintf(msg, "{\"class\":0,\"type\": \"scan\"}\n");
                send_string(msg);
            }
            if(temp == 'n'){
                oi_play_song(0);
                sprintf(msg, "{\"class\":0,\"type\": \"play-song\"}\n");
                send_string(msg);
            }
        }

        else {
            buffer[i] = '\0';
            i = 0;
            lcd_printf("%s\n", buffer);
            uart_sendChar('\n');
            uart_sendChar('\r');
            for(j = 0; j < 20; j++){
               uart_sendChar(buffer[j]);
             }

        }


    }
    return 0;
}

