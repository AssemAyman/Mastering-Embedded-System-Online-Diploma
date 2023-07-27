/*
 * Section1.c
 *
 * Created: 7/27/2023 9:41:06 PM
 * Author : assem
 */ 

#define F_CPU 8000000UL 
#include <util/delay.h>

#define DDRA  *(volatile unsigned char*)0x3A
#define PORTA *(volatile unsigned char*)0x3B

#define SetBit(REG,BIT)   REG |= 1<<BIT
#define ClearBit(REG,BIT) REG &= ~(1<<BIT)

int main(void)
{
	DDRA = 0xFF;
	unsigned char bit = 0;
	while (1) 
	{
		if(bit <= 7){
			while(bit <= 7){
				SetBit(PORTA,bit++);
				_delay_ms(250);
			}
		}
			else{
				while(bit > 0){
					ClearBit(PORTA,--bit);
					_delay_ms(250);
				}
			}
		}
	}