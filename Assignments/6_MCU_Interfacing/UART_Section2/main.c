/*
 * UART_Section2.c
 *
 * Created: 8/12/2023 3:56:10 AM
 * Author : assem
 */ 

#include "UART/UART.h"
#include "LCD/LCD.h"

extern char* p_buffer;

int main(void)
{
	sei();
	
	UART_Init();
	//UART_Send_String("Assem Ayman");
	
	LCD_Init();
	
	//char val;
	char x = '0';
	
	char buffer[100] = {0};
	
	UART_Send_String_Asynch("ENG/Assem Ayman");
	UART_Receive_String_Asynch(buffer);
	
    while (1) 
    {
		
		/*
		UART_Receive_String(buffer);
		LCD_Send_A_String(buffer);
		
		
		//if there is unread data
		if (UART_Receive_PerodicCheck(&val))
		{
			LCD_Goto_XY(1,0);
			LCD_Send_A_Character(val);
		}
		*/
		
		//the counter is running ethier there  is new read data or not
		LCD_Goto_XY(2,0);
		LCD_Send_A_Character(x);
		x++;
		if (x == '9'+1) x = '0';
		_delay_ms(1000);
    }
}

