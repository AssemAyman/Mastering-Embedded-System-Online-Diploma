/*
 * LCD.h
 *
 * Created: 10/3/2023 2:08:55 AM
 *  Author: assem
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "GPIO.h"

#define Read_Bit(reg,index)		((reg & 1<<index)>>index)

/*=========Configurations============*/
//#define Eight_Bit_MODE
#define FOUR_Bit_MODE

#define LCD1_DATA 	GPIOB->ODR
#define LCD1_PORT	GPIOB
#define LCD2_DATA 	GPIOA->ODR
#define LCD2_PORT	GPIOA

#define RS1 		GPIO_PIN_11
#define EN1 		GPIO_PIN_10
#define RS2 		GPIO_PIN_5
#define EN2 		GPIO_PIN_6

#ifdef Eight_Bit_MODE
#define D0			GPIO_PIN_0
#define D1			GPIO_PIN_1
#define D2			GPIO_PIN_2
#define D3			GPIO_PIN_3
#endif

#define D4			GPIO_PIN_12
#define D5			GPIO_PIN_13
#define D6			GPIO_PIN_14
#define D7			GPIO_PIN_15
/*==================================*/
#define ADMIN_LCD 0
#define ENTRY_LCD 1
#define LCD_8bit_1Line        0x30
#define LCD_8bit_4Line        0x38
#define LCD_4bit_1_Line       0x20
#define LCD_4bit_4_Line       0x28
#define LCD_Entry_Mode        0x06
#define LCD_Display_off_Cursor_off  0x08
#define LCD_Display_Cursor_On     0x0E
#define LCD_Display_Cursor_Off    0x0C
#define LCD_Display_Cursor_Blinking  0x0F
#define LCD_Shift_Entire_Display_Left 0x18
#define LCD_Shift_Entire_Display_Right 0x1C
#define LCD_Move_Cursor_Left_By_one_Character   0x10
#define LCD_Cursor_Right_By_One_Character    0x14
#define LCD_Clear_Display                    0x01
#define LCD_Start_At_Beginning_Of_First_Line 0x80
#define LCD_Start_At_Beginning_Of_Second_Line 0xC0
#define LCD_Start_At_Beginning_Of_Third_Line 0x90
#define LCD_Start_At_Beginning_Of_Fourth_Line 0xD0
#define LCD_Two_Lines_5_7_Matrix 0x38
#define Data_Shift   4

extern void LCD_Send_Command (unsigned char CMD,int index);
extern void LCD_Send_A_Character (char data,int index);
extern void LCD_Send_A_String(char* str,int index);
extern void LCD_Init();
extern void LCD_Clear_Screen(int index);
extern void LCD_Goto_XY(unsigned char line,unsigned char position,int index);
extern void LCD_Display_Number(int Number);
extern void LCD_Diplay_Real_Number(double Number);
extern void wait_ms(uint32_t time);

#endif /* LCD_H_ */
