/*
#include <stdint.h>
#include "lcd.h"
#include "Timer.h"
#include "button.h"
#include "WiFi.h"
#include "uart.h"
#include "open_interface.h"
#include "movement.h"

void UART_init(void);
//void UART_Transmit(char sdata);
char UART_Receive(void);
char uart_receive(void);

//30923764.5 0x1D7DBF4
//prelab 2: 8 & 44



//Blocking call to receive over uart1
//returns char with data
//int last = 0;
int main(void)
{
    oi_t *sensor = oi_alloc();
    oi_init(sensor);
    oi_shutoff_init();
    GPIOF_Handler();
    lcd_init();
    UART_init();
    button_init();

    char dispBuff[] = "testingg";
    char *distPtr;
    distPtr = dispBuff;

    lcd_printf(distPtr);

    //auto_reroute(sensor,15);

    //This is a test for the signal threshhold
    while(1)
    {
        char msg[81] = "";
        oi_update(sensor);
        int threshhold = sensor->cliffFrontRightSignal;
        if((sensor->cliffFrontRight) || ((sensor->cliffFrontRightSignal) > 0))
        {
            sprintf(msg, "Cliff on front right side! %i \n\r", threshhold);
            lcd_printf(msg);
          }
     }




//Ann Devin Code
    char buffer[21];
    int i = 0;
    int j = 0;


    char pass[] = "annIsCool123";
    char command;
    WiFi_start(pass);
    while(1){
        command = uart_receive();
        if(command != '\r'){
            lcd_printf("the char is: %c\n the index is %d", command, i);
            buffer[i] = command;

            //Moves the bot forward or backward N centimeters
            //e.g. "collision_avoidance(sensor, N);" --> if N = 15 moves forward 15cm.  if N = -15 moves backward 15cm
            //Integrated CRATER avoidance and WHITE LINE avoidance
            //When hits a CRATER or WHITE LINE moves backward 5cm and turns + or - 90 degrees
            if(command == 'm')
            {
                auto_reroute(sensor,15);
            }
            //rotate 90 degrees clockwise
            if(command == 'r')
            {
                turn(sensor, -90);
            }
            //rotate 45 degrees clockwise
            if(command == 's')
            {
                turn(sensor, -45);
            }
            //rotate 90 degrees counter clockwise
            if(command == 't')
            {
                turn(sensor, 90);
            }
            //rotate 45 degrees counter clockwise
            if(command == 'u')
            {
                turn(sensor, 45);
            }
/*
        } else {
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
*/
