/*
 * Timer_Section.c
 *
 * Created: 9/3/2023 10:11:03 AM
 * Author : assem
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "Timer_and_PWM_Driver/Timer.h"

int main(void)
{
	
	TIMER0_Config_t Timercfg = {TIMER0_MODE_PWM_Phase_Correct_non_inverting_mode,TIMER0_CLOCK_SOURCE_INTERNAL_PRESCALER_64,TIMER0_IRQ_ENABLE_NONE,NULL};
	
	MCAL_TIMER0_Init(&Timercfg);
	MCAL_PWM_DutyCycle(153); // 60% Duty Cycle
	
    while (1);
 
}
