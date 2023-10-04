/*
 * Key_Pad.c
 *
 * Created: 7/30/2023 4:51:45 AM
 *  Author: assem
 */
#include "Key_Pad.h"

void delay_ms(uint32_t time){
	uint32_t i,j;
	for(i = 0; i<time; i++)
		for(j=0; j<255; j++);
}

void KEYPAD_INIT(void)
{
	// Set lower part(rows) of keypad port as input PD and Set upper part(columns) of keypad port as output PP
	GPIO_PinConfig_t Pincfg;
	uint16_t pin[8] = {R0,R1,R2,R3,C0,C1,C2,C3};
	uint8_t i;
	for(i=0; i<8; i++){
		if(i<4){
			Pincfg.GPIO_PinNumber = pin[i] ;
			Pincfg.GPIO_MODE = GPIO_MODE_INPUT_PD;
			MCAL_GPIOx_Init(KeyPad_PORT, &Pincfg);
		}else{
			Pincfg.GPIO_PinNumber = pin[i];
			Pincfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
			Pincfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
			MCAL_GPIOx_Init(KeyPad_PORT,&Pincfg);
		}
	}
}

char KEYPAD_GET_KEY(void)
{
	int keypad_C[] = {C0, C1, C2, C3}; // Columns of the keypad
	int keypad_R[] = {R0, R1, R2, R3}; // Rows of the keypad
	int i, j;
	for (i = 0; i < 4; i++)
	{
		// Send a high to a particular column of the keypad
		MCAL_GPIOx_WritePin(KeyPad_PORT, keypad_C[i],GPIO_PIN_SET);
		for (j = 0; j < 4; j++)
		{
			if (MCAL_GPIOx_ReadPin(KeyPad_PORT, keypad_R[j])) // Check if is key is pressed
			{
				while (MCAL_GPIOx_ReadPin(KeyPad_PORT, keypad_R[j])); // Wait for the key to be released (Single pressed)
				switch (i)
				{
				case 0:
					if (j == 0) return '7';
					else if(j == 1) return '4';
					else if(j == 2) return '1';
					else if(j == 3) return '?';
					break;

				case 1:
					if (j == 0) return '8';
					else if(j == 1) return '5';
					else if(j == 2) return '2';
					else if(j == 3) return '0';
					break;

				case 2:
					if (j == 0) return '9';
					else if(j == 1) return '6';
					else if(j == 2) return '3';
					else if(j == 3) return '=';
					break;

				case 3:
					if (j == 0) return '/';
					else if(j == 1) return '*';
					else if(j == 2) return '-';
					else if(j == 3) return '+';
					break;
				}
			}
		}
		delay_ms(10);
		MCAL_GPIOx_WritePin(KeyPad_PORT, keypad_C[i],GPIO_PIN_RESET); //Return the column low again
	}
	return '\0'; // Return '\0' if no key is pressed
}
