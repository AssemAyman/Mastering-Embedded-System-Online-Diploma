/*
 * Timer.c
 *
 * Created: 9/3/2023 10:11:03 AM
 * Author : assem
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "Timer_and_PWM_Driver/Timer.h"


void Timer_CTC(){
	
	static uint8_t  sw_counter = 0;
	sw_counter++;
	
	if (sw_counter == 33)
	{
		PORTA ^=1;
		/* Clear Counter */
		sw_counter = 0;
	}
}

int main(void)
{
	DDRA = 1;
	
	TIMER0_Config_t Timercfg = {TIMER0_MODE_CTC_Toggle,TIMER0_CLOCK_SOURCE_INTERNAL_PRESCALER_1024,TIMER0_IRQ_ENABLE_OCIE0,Timer_CTC};
	
	MCAL_TIMER0_Init(&Timercfg);
	MCAL_SetCompareValue(230);
	
    while (1);
 
}
