/*
 * LCD.c
 *
 * Created: 7/30/2023 2:08:45 AM
 *  Author: assem
 */ 

#include "LCD.h"

void wait_ms(uint32_t time){
	uint32_t i,j;
	for(i = 0; i<time; i++)
		for(j=0; j<255; j++);
}

void LCD_Kick(){
	MCAL_GPIOx_WritePin(LCD_PORT,EN,GPIO_PIN_SET);
	wait_ms(20);
	MCAL_GPIOx_WritePin(LCD_PORT,EN,GPIO_PIN_RESET);
}

void LCD_Send_Command (unsigned char CMD){
	//turn RS off for command mode.
	MCAL_GPIOx_WritePin(LCD_PORT,RS,GPIO_PIN_RESET);

#ifdef Eight_Bit_MODE
	//Write the command on D0...D7
	LCD_DATA = (LCD_DATA & 0xff00) | CMD;
	LCD_Kick();
#endif

#ifdef FOUR_Bit_MODE
	//Write the command on D4..D7 first
	MCAL_GPIOx_WritePin(LCD_PORT, D4, Read_Bit(CMD,4));
	MCAL_GPIOx_WritePin(LCD_PORT, D5, Read_Bit(CMD,5));
	MCAL_GPIOx_WritePin(LCD_PORT, D6, Read_Bit(CMD,6));
	MCAL_GPIOx_WritePin(LCD_PORT, D7, Read_Bit(CMD,7));
	LCD_Kick();
	//Write the command on D0..D3
	MCAL_GPIOx_WritePin(LCD_PORT, D4, Read_Bit(CMD,0));
	MCAL_GPIOx_WritePin(LCD_PORT, D5, Read_Bit(CMD,1));
	MCAL_GPIOx_WritePin(LCD_PORT, D6, Read_Bit(CMD,2));
	MCAL_GPIOx_WritePin(LCD_PORT, D7, Read_Bit(CMD,3));
	LCD_Kick();
#endif
}

void LCD_Init(){
	wait_ms(20);
	//set the control port direction as output so you can send commands to the LCD.
	GPIO_PinConfig_t Pincfg;

	//RS OUTPUT Push-Pull
	Pincfg.GPIO_PinNumber = RS;
	Pincfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	Pincfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIOx_Init(LCD_PORT,&Pincfg);

	//EN OUTPUT Push-Pull
	Pincfg.GPIO_PinNumber = EN;
	Pincfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	Pincfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIOx_Init(LCD_PORT,&Pincfg);

	//turn off enable
	MCAL_GPIOx_WritePin(LCD_PORT,EN,GPIO_PIN_RESET);

#ifdef Eight_Bit_MODE
	//set the port direction as output so you can send information to the LCD.
	uint16_t pin[8]={D0,D1,D2,D3,D4,D5,D6,D7};
	int i;
	for(i=0; i<8; i++){
		Pincfg.GPIO_PinNumber = pin[i];
		Pincfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
		Pincfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
		MCAL_GPIOx_Init(LCD_PORT,&Pincfg);
	}
	LCD_Send_Command(LCD_8bit_2Line);
#endif

#ifdef FOUR_Bit_MODE
	//set the MSB port direction as output so you can send information to the LCD.
	uint16_t pin[4]={D4,D5,D6,D7};
	int i;
	for(i=0; i<4; i++){
		Pincfg.GPIO_PinNumber = pin[i];
		Pincfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
		Pincfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
		MCAL_GPIOx_Init(LCD_PORT,&Pincfg);
	}
	LCD_Send_Command(0x02);
	LCD_Send_Command(LCD_4bit_2_Line);
#endif

	LCD_Send_Command(LCD_Entry_Mode);
	LCD_Send_Command(LCD_Start_At_Beginning_Of_First_Line);
	LCD_Send_Command(LCD_Display_Cursor_Blinking);
}

void LCD_Send_A_Character (char data){
	//turn RS ON for Data mode.
	MCAL_GPIOx_WritePin(LCD_PORT,RS,GPIO_PIN_SET);

#ifdef Eight_Bit_MODE
	//write data on D0...D7
	LCD_DATA = (LCD_DATA & 0xff00) | data;
	LCD_Kick();
#endif

#ifdef FOUR_Bit_MODE
	//send D4..D7 first
	MCAL_GPIOx_WritePin(LCD_PORT, D4, Read_Bit(data,4));
	MCAL_GPIOx_WritePin(LCD_PORT, D5, Read_Bit(data,5));
	MCAL_GPIOx_WritePin(LCD_PORT, D6, Read_Bit(data,6));
	MCAL_GPIOx_WritePin(LCD_PORT, D7, Read_Bit(data,7));
	LCD_Kick();
	//send data D0..D3
	MCAL_GPIOx_WritePin(LCD_PORT, D4, Read_Bit(data,0));
	MCAL_GPIOx_WritePin(LCD_PORT, D5, Read_Bit(data,1));
	MCAL_GPIOx_WritePin(LCD_PORT, D6, Read_Bit(data,2));
	MCAL_GPIOx_WritePin(LCD_PORT, D7, Read_Bit(data,3));
	LCD_Kick();
#endif
}

void LCD_Clear_Screen(){
	//wait_ms(10);
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
