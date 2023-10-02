/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

typedef volatile unsigned int vuint32_t ;

#include <stdint.h>

#define NVIC_ISER0 	*(vuint32_t*)(0xE000E100)

//Register base addresses
#define RCC_BASE    0x40021000
#define PortA_BASE  0x40010800
#define EXTI_BASE 	0x40010400
#define AFIO_BASE 	0x40010000

//RCC Registers
#define RCC_APB2ENR *(vuint32_t*)(RCC_BASE + 0x18)

//GPIOA & AFIO Registers
#define GPIOA_CRL    *(vuint32_t*)(PortA_BASE)
#define GPIOA_CRH    *(vuint32_t*)(PortA_BASE + 0x04)
#define GPIOA_ODR    *(vuint32_t*)(PortA_BASE + 0x0c)
#define AFIO_EXTICR1 *(vuint32_t*)(AFIO_BASE + 0x08)

//EXTI Registers
#define EXTI_IMR	*(vuint32_t*)(EXTI_BASE)
#define EXTI_RTSR	*(vuint32_t*)(EXTI_BASE + 0x08)
#define EXTI_PR		*(vuint32_t*)(EXTI_BASE + 0x14)

void clock_init(){
	//Enable GPIOA Clock
	RCC_APB2ENR |= 1<<2;
	//Enable AFIO Clock
	RCC_APB2ENR |= 1;
}

void GPIO_INIT(){
	//Pin 13 portA is output
	GPIOA_CRH    &= 0xFF0FFFFF;
	GPIOA_CRH    |= 0x00200000;

	//PA[0] floating input
	GPIOA_CRL |= 1<<2;
}

int main(void)
{
	//Initialization
	 clock_init();
	 GPIO_INIT();

	 //makes PA[0] input for EXTI0
	 AFIO_EXTICR1 = 0;

	 //Enable Rising Edge Trigger
	 EXTI_RTSR |= 1;
	 //Enable EXTI0 Mask
	 EXTI_IMR |= 1;

	 NVIC_ISER0 |= 1<<6;
	 while(1);
}

void EXTI0_IRQHandler(){

	//Toggle LED on PORTA.13
	GPIOA_ODR ^= 1<<13;

	//Clear Pending bit for EXTI0
	EXTI_PR |= 1;
}