/**
 * @file uart.h
 * @brief File containing functions for controlling the sonar sensor
 *
 * @authors 	Ann Gould, Akira DeMoss, Devin Uner, Takao Shibamoto
 * @date    	Dec 7, 2017
 */


#ifndef UART_H_
#define UART_H_

/**
 * Initializes uart communication protocol
 */
void UART_init(void);

/**
 *Blocking call to receive over uart1 returns char with data
 *@return data:   A char that is received over uart1
 */
char uart_receive(void);

/**
 * Blocking call that sends 1 char over UART 1
 * @param data:   A char that is sent over UART1
 */
void uart_sendChar(char data);

/**
 * Blocking call that sends string over UART 1
 * @param str[]   A char array that is sent over UART1
 */
void send_string(char str[]);



#endif /* UART_H_ */
