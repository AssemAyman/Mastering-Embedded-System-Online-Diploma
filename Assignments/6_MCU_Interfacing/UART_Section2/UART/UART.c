/*
 * UART.c
 *
 * Created: 8/8/2023 7:06:06 PM
 *  Author: assem
 */ 

 #include "UART.h"
 #include "../LCD/LCD.h"

char *g_buffer,*p_buffer;

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
 
 void UART_Send_String(char* str){
	 
	 while(*str != '\0')
		 UART_Send(*str++);
 }
 
 void UART_Receive_String(char buffer[]){
	 
	 unsigned short i = 0;
	 
	 buffer[i] = UART_Receive();
	 
	 while(buffer[i++] != '\r')
		buffer[i] = UART_Receive();
		
	 buffer[--i] = '\0';	
 }
 
 char UART_Receive_PerodicCheck(char* pVal){
	 //if there is received data
	 if((UCSRA & 1<<RXC))
	 {
		*pVal = UDR;
		 return 1; 
	 }
	 
	 //if there is no received data
	 return 0;
 }
 
 void UART_Send_String_Asynch(char* buffer){
	 
	 g_buffer = buffer;
	 
	//Send first element of the buffer	 
	 UDR = *buffer;
	//Enable TXC interrupt
	 UART_TX_Interrupt_Enable();
  
 }
 
ISR(USART_TXC_vect)
{
	static short i = 1;
	
	if(g_buffer[i] != '\0')
		UDR = g_buffer[i++];
		
	//Disable TXC interrupt after all buffer is transmitted
	else 
		UART_TX_Interrupt_Disable();	
}

void UART_Receive_String_Asynch(char* buffer){
		p_buffer = buffer;
		UART_RX_Interrupt_Enable();
}

ISR(USART_RXC_vect)
{
	static short j = 0;
	
	 p_buffer[j] = UDR ;
	 
	 if (p_buffer[j] == '\r'){
		 LCD_Goto_XY(1,0);
		LCD_Send_A_String(p_buffer);
	 }
	j++;	
}