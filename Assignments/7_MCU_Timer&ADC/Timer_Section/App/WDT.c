/*
 * Timer_Section.c
 *
 * Created: 9/3/2023 10:11:03 AM
 * Author : assem
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

void WDT_Start(){
	// Enable Watch Dog Timer
	WDTCR |= 1<<WDE;
	// Make Time-out equals 1s
	WDTCR |= 1<<WDP2 | 1<<WDP1;
	WDTCR &= ~(1<<WDP0);
}

void WDT_Stop(){
	
	WDTCR |= 1<<WDTOE | 1<<WDE;
	WDTCR = 0x00;
	
}

int main(void)
{
	
   DDRC = 1;
   DDRA = 1;
   
   _delay_ms(100);
   PORTA = 1;
   
    while (1) 
    {
		
		WDT_Start();
		
		PORTC ^= 1;
		_delay_ms(1050);
		
		WDT_Stop();
		
    }
}

