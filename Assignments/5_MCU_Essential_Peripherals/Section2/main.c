/*
 * Section2.c
 *
 * Created: 7/30/2023 2:08:19 AM
 * Author : assem
 */ 

#include "LCD/LCD.h"
#include "Key_Pad/Key_Pad.h"

int main(void)
{
	char Pressed_Key;
    LCD_Init();
	KEYPAD_INIT();
	LCD_Send_A_String("HI I'm Eng/Assem,I'm from Alexandria.I study Embedded Systems.");
    while (1) 
    {
		Pressed_Key = KEYPAD_GET_KEY();
		switch(Pressed_Key){
			//No pressed Key
			case 'A': break;
			//ON/C is pressed
			case '?': 
			LCD_Clear_Screen();
			break;
			//Others
			default:
			LCD_Send_A_Character(Pressed_Key);
       }
    }
}