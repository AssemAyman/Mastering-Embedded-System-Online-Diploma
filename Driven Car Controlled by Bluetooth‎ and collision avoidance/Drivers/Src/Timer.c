/*
 * Timer.c
 *
 */


#include "Timer.h"

vuint32_t OVF,clk;

void Timer2_init(void)
{
	TIMER2_CLK_EN();  			 //Enable CLK for TIMER2

	TIMER2->PSC = 7;            //Clk_input=(8M/(7+1))=1MHZ
	TIMER2->ARR = 0xC350;        //to make interrupt after 50000 tick(50000*10^-6)= 0.05s

}

void Timer3_init(void)
{
	TIMER3_CLK_EN();  			 //Enable CLK for TIMER3

	TIMER3->CR1 |= 1<<2;		//Only counter overflow/underflow generates an update
	TIMER3->DIER |= 1<<0;		//Update interrupt enabled

	TIMER3->ARR = 64000;        //to make interrupt after 64000 tick(64000*(1/8)*10^-6)= 8ms
	TIMER3->PSC = 0;            //Clk_input=(8M/(0+1))=8MHZ
	TIMER3->EGR |= 1<<0;		// Re-initialize the counter and generates an update of the registers.

	NVIC_IRQ29_TIMER3_Enable();

	clk = MCAL_RCC_TIMXCLK();
}

void dus(int us)
{
	TIMER2->CR1 |=(1<<0);		//Enable timer
	TIMER2->CNT=0;
	while((TIMER2->CNT)<us);
	TIMER2->CR1 &=~(1<<0);		//Disable timer
}

void dms(int ms)
{
	int i=0;
	for(i=0;i<ms;i++)
	{
		dus(1000);
	}
}

vuint32_t Time_Claculation(Entery_t entery_num){

	if(entery_num == first_entry){
		TIMER3->CR1 |=(1<<0);		//Enable timer
		return 0;
	}
	else{
		TIMER3->CR1 &=~(1<<0);		//Disable timer
		vuint32_t time = (TIMER3->CNT + (OVF * 64000))/(clk/1000000);
		OVF = 0;
		TIMER3->CNT=0;
		return time;
	}
}

void TIM3_IRQHandler(){

	TIMER3->SR &= ~(1<<0);
	OVF++;

}
