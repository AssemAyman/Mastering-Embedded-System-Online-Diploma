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
#include <avr/interrupt.h>

/*============ Enable/Disable UART Interrupts====*/
#define UART_RX_Interrupt_Enable()	UCSRB |= 1<< RXCIE
#define UART_RX_Interrupt_Disable()	UCSRB &= ~(1<< RXCIE)

#define UART_TX_Interrupt_Enable()	UCSRB |= 1<< TXCIE
#define UART_TX_Interrupt_Disable()	UCSRB &= ~(1<< TXCIE)

/* ============== APIs Supported by "MCAL EXTI DRIVER" =========== */
extern void UART_Init();
extern void UART_Send(char);
extern char UART_Receive();
extern void UART_Send_String(char*);
extern void UART_Receive_String(char*);
extern char UART_Receive_PerodicCheck(char*);
extern void UART_Send_String_Asynch(char*);
extern void UART_Receive_String_Asynch(char*);

#endif /* UART_H_ */