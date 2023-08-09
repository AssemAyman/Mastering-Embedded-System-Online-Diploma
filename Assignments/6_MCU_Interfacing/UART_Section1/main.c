/*
 * UART_Section1.c
 *
 * Created: 8/9/2023 2:53:11 AM
 * Author : assem
 */ 

#include "UART/UART.h"
#include "LCD/LCD.h"

int main(void)
{
    UART_Init();
	UART_Send('A');
	UART_Send('S');
	UART_Send('S');
	UART_Send('E');
	UART_Send('M');
	
	LCD_Init();
	while(1){
	LCD_Send_A_Character(UART_Receive());
	}
}

