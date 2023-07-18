/*
 * Lab3.c
 *
 * Created: 7/18/2023 5:44:35 AM
 * Author : assem
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void GPIOA_Init(){
	
	DDRD |= 1<<5; //PD5 is output
	DDRD |= 1<<6; //PD6 is output
	DDRD |= 1<<7; //PD7 is output
}

int main(void)
{
	GPIOA_Init();
   
	MCUCR  |= 1;		 //Any logical change on INT0 generates an irq
	MCUCR  |= 0b11<<2;   //The rising edge of INT1 generates an irq
	MCUCSR &= ~(1<<6);   //The falling edge of INT2 generates an irq
	
	GICR |= 0b111<<5;	//Enable EXTI0 , EXTI1 , EXTI2
	sei();				//Set SREG I-flag
	
    while (1);
}

ISR(INT0_vect){
	GIFR  |= 1<<6; //Clear INFT0
	PORTD |= 1<<5; //Turn LED ON @PD5
	_delay_ms(100); //1s delay
	PORTD &= ~(1<<5); //Turn LED OFF @PD5
}

ISR(INT1_vect){
	GIFR  |= 1<<7; //Clear INFT1
	PORTD |= 1<<6; //Turn LED ON @PD6
	_delay_ms(100); //1s delay
	PORTD &= ~(1<<6); //Turn LED OFF @PD6
}

ISR(INT2_vect){
	GIFR  |= 1<<5; //Clear INFT2
	PORTD |= 1<<7; //Turn LED ON @PD7
	_delay_ms(100); //1s delay
	PORTD &= ~(1<<7); //Turn LED OFF @PD7
}