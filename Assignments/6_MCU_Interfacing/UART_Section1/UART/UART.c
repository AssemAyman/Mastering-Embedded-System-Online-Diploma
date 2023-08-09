/*
 * UART.c
 *
 * Created: 8/8/2023 7:06:06 PM
 *  Author: assem
 */ 

 #include "UART.h"
 
 void UART_Init(){
	 //Set baud rate to 9600
	 UBRRL = 51;
	 //Enable USART Transmitter and Receiver
	 UCSRB |= 1<<TXEN;
	 UCSRB |= 1<<RXEN;
 }
 void UART_Send(char data){
	 //Wait until UDR is empty to send data
	  while(!(UCSRA & 1<<UDRE));
	  UDR = data;
 }
 
 char UART_Receive(){
	 //Wait until there is unread data on UDR
	 while(!(UCSRA & 1<<RXC));
	 return UDR;
 } 