/*
 * UART.h
 *
 * Created: 8/8/2023 7:05:53 PM
 *  Author: assem
 */ 


#ifndef UART_H_
#define UART_H_

typedef volatile unsigned char vuint8_t;

/* ==========Includes=========*/
#include <avr/io.h>

/* ============== APIs Supported by "MCAL EXTI DRIVER" =========== */
extern void UART_Init();
extern void UART_Send(char);
extern char UART_Receive();

#endif /* UART_H_ */