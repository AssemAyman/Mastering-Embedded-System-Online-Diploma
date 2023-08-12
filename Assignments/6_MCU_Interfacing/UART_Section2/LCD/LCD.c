/*
 * LCD.c
 *
 * Created: 7/30/2023 2:08:45 AM
 *  Author: assem
 */ 

#include "LCD.h"

void LCD_Kick(){
	LCD_CONTROL |= 1<<EN;
	_delay_ms(50);
	LCD_CONTROL &= ~(1<<EN);
}

 void LCD_Send_Command (unsigned char CMD){
	 //turn RW off so you can write. turn RS off for command mode.
	 LCD_CONTROL &= ~(1<<RW | 1<<RS);
	 
	 #ifdef Eight_Bit_MODE
	 //Write the command on D0...D7
	 LCD_DATA = CMD;
	 LCD_Kick();
	 #endif
	 
	 #ifdef FOUR_Bit_MODE
	 //Write the command on D4..D7 first
	 LCD_DATA = (LCD_DATA & 0x0f) | (CMD & 0xf0);
	 LCD_Kick();
 	 //Write the command on D0..D3
	 LCD_DATA = (LCD_DATA & 0x0f) | (CMD<<4);
	 LCD_Kick();
	 #endif
 }
 
void LCD_Init(){
	_delay_ms(20);
	//set the control port direction as output so you can send commands to the LCD.
	LCD_CONTROL_DIR |= (1<<RS | 1<<RW | 1<<EN);
	//turn off enable
	LCD_CONTROL &= ~(1<<EN);
	
	#ifdef Eight_Bit_MODE
	//set the port direction as output so you can send information to the LCD.
    LCD_DATA_DIR = 0xff;
	LCD_Send_Command(LCD_8bit_2Line);
    #endif

    #ifdef FOUR_Bit_MODE
	//set the MSB port direction as output so you can send information to the LCD.
	LCD_DATA_DIR |= 0xf<<4; 
	LCD_Send_Command(0x02);
	LCD_Send_Command(LCD_4bit_2_Line);
    #endif
	
	LCD_Send_Command(LCD_Entry_Mode);
	LCD_Send_Command(LCD_Start_At_Beginning_Of_First_Line);
	LCD_Send_Command(LCD_Display_Cursor_Blinking);
}

void LCD_Send_A_Character (char data){
	//turn RW off so you can write.
	LCD_CONTROL &= ~(1<<RW);
	//turn RS ON for Data mode.
	LCD_CONTROL |= 1<<RS;
	
	#ifdef Eight_Bit_MODE
	//write data on D0...D7
	LCD_DATA = data;
	LCD_Kick();
	#endif
	
	#ifdef FOUR_Bit_MODE
	//send D4..D7 first
	LCD_DATA = (LCD_DATA & 0x0f) | (data & 0xf0);
	LCD_Kick();
	//send data D0..D3
	LCD_DATA = (LCD_DATA & 0x0f) | (data<<4);
	LCD_Kick();
	#endif
}

void LCD_Clear_Screen(){
	_delay_ms(500);
	LCD_Send_Command(LCD_Clear_Display);
}

void LCD_Goto_XY(unsigned char line,unsigned char position){
	if (line == 1)
		LCD_Send_Command(LCD_Start_At_Beginning_Of_First_Line + position);
	else if(line == 2)
		LCD_Send_Command(LCD_Start_At_Beginning_Of_Second_Line + position);	
}

void LCD_Send_A_String(char* str){
	static char count = 0;
	while(*str != 0){
		LCD_Send_A_Character(*str++);
		count++;
		//Line 1 is complete
		if (count == 16){
		//Go to the second line
			LCD_Goto_XY(2,0);
		}
		//Line 2 is complete	
		else if(count == 32){
			LCD_Clear_Screen();
			LCD_Goto_XY(1,0);
			count = 0;
		}
	}
}