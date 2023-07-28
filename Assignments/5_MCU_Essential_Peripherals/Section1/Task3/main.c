/*
 * Section1_Task3.c
 *
 * Created: 7/28/2023 3:12:03 AM
 * Author : assem
 */ 

#include <avr/io.h>

int main(void)
{
   DDRD |= 1<<4;
    while (1) 
    {
		if ((PIND & 1) == 1)
		{
			PORTD |= 1<<4;
			while((PIND & 1) == 1);
		}
		PORTD &= ~(1<<4);
    }
}

