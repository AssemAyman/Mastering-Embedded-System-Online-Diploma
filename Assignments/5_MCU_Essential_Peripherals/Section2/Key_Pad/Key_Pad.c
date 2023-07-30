/*
 * Key_Pad.c
 *
 * Created: 7/30/2023 4:51:45 AM
 *  Author: assem
 */ 
#include "Key_Pad.h"

int keypad_R[] = {R0, R1, R2, R3}; // Rows of the keypad
int keypad_C[] = {C0, C1, C2, C3}; // Columns of the keypad
	
void KEYPAD_INIT(void)
{
	//Set upper part of keypad port as input and Set lower part of keypad port as output 
	KEYPAD_DIR = 0xf0;
	KEYPAD_PORT = 0xff;
}	
char KEYPAD_GET_KEY(void)
{
	int i, j;
	for (i = 0; i < 4; i++)
	{
		KEYPAD_PORT &= ~(1<<keypad_C[i]); // Send a low to a particular column of the keypad
		for (j = 0; j < 4; j++)
		{
			if (!(KEYPAD_PIN & (1<<keypad_R[j]))) // Check if is key is pressed
			{
				while (!(KEYPAD_PIN & (1<<keypad_R[j]))); // Wait for the key to be released (Single pressed)
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
		KEYPAD_PORT |= 1<<keypad_C[i]; //Return the column high again
	}
	return 'A'; // Return 'A' if no key is pressed
}