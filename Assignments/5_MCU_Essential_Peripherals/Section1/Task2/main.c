/*
 * Section1_Task2.c
 *
 * Created: 7/27/2023 11:02:25 PM
 * Author : assem
 */ 

#define F_CPU 8000000UL
#include <util/delay.h>

#define DDRA  *(volatile unsigned char*)0x3A
#define PORTA *(volatile unsigned char*)0x3B

#define PINC  *(volatile unsigned char*)0x33

#define SetBit(REG,BIT)   REG |= 1<<BIT
#define ClearBit(REG,BIT) REG &= ~(1<<BIT)
#define ReadBit(REG,BIT)  (REG & 1<<BIT) >> BIT

int main(void)
{
	DDRA = 0xFF;
	unsigned char bit = 0;
    
    while (1) 
    {
		if (ReadBit(PINC,0) == 0 && bit <= 7)
		{
			SetBit(PORTA,bit++);
			_delay_ms(250);
		}
    }
}

