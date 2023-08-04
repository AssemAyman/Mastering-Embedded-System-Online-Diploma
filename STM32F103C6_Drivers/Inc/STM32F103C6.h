/*
 * STM32F103C6.h
 *
 *  Created on: Jul 31, 2023
 *      Author: assem
 */

#ifndef STM32F103C6_H_
#define STM32F103C6_H_
#define LQFP48
//-----------------------------
//Includes
//-----------------------------
#include "Platform_Types.h"
#include <stdlib.h>
//-----------------------------
//Base addresses for Memories
//-----------------------------
#define FLASH_MEMORY_BASE 	0x08000000UL
#define SYS_MEMORY_BASE 	0x1FFFF000UL
#define SRAM_MEMORY_BASE 	0x20000000UL
//----------------------------
//NVIC Register Map
//---------------------------
#define NVIC_Base			0xE000E100UL
#define NVIC_ISER0			*(vuint32_t*)(NVIC_Base + 0x0)
#define NVIC_ISER1			*(vuint32_t*)(NVIC_Base + 0x4)
#define NVIC_ISER2			*(vuint32_t*)(NVIC_Base + 0x8)
#define NVIC_ICER0			*(vuint32_t*)(NVIC_Base + 0x80)
#define NVIC_ICER1			*(vuint32_t*)(NVIC_Base + 0x84)
#define NVIC_ICER2			*(vuint32_t*)(NVIC_Base + 0x88)
//-----------------------------
//Base addresses for  AHB BUS Peripherals
//-----------------------------
#define RCC_BASE 0x40021000
//-----------------------------
//Base addresses for  APB2 BUS Peripherals
//-----------------------------
#define GPIOA_BASE 0x40010800UL
#define GPIOB_BASE 0x40010C00UL
#define GPIOC_BASE 0x40011000UL
#define GPIOD_BASE 0x40011400UL
#ifndef LQFP48
#define GPIOE_BASE 0x40011800UL
#endif
#define EXTI_BASE  0x40010400UL
#define AFIO_BASE  0x40010000UL
//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: GPIOx
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct {
	vuint32_t CRL;
	vuint32_t CRH;
	vuint32_t IDR;
	vuint32_t ODR;
	vuint32_t BSRR;
	vuint32_t BRR;
	vuint32_t LCKR;
}GPIOx_REG;
//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: AFIO
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct {
	vuint32_t EVCR;
	vuint32_t MAPR;
	vuint32_t EXTICR[4];
	uint32_t RESERVED;
	vuint32_t MAPR2;
}AFIO_REG;
//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: EXTI
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct {
	vuint32_t IMR;
	vuint32_t EMR;
	vuint32_t RTSR;
	vuint32_t FTSR;
	vuint32_t SWIER;
	vuint32_t PR;
}EXTI_REG;
//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: RCC
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct{
	vuint32_t CR;
	vuint32_t CFGR;
	vuint32_t CIR;
	vuint32_t APB2RSTR;
	vuint32_t APB1RSTR;
	vuint32_t AHBENR;
	vuint32_t APB2ENR;
	vuint32_t APB1ENR;
	vuint32_t BDCR;
	vuint32_t CSR;
}RCC_REG;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants:
//-*-*-*-*-*-*-*-*-*-*-*
#define GPIOA		((GPIOx_REG *) GPIOA_BASE)
#define GPIOB		((GPIOx_REG *) GPIOB_BASE)
#define GPIOC		((GPIOx_REG *) GPIOC_BASE)
#define GPIOD		((GPIOx_REG *) GPIOD_BASE)
#define AFIO		((AFIO_REG  *) AFIO_BASE)
#ifndef LQFP48
#define GPIOE		((GPIOx_REG *) GPIOD_BASE)
#endif
#define RCC   		((RCC_REG   *) RCC_BASE)
#define EXTI	    ((EXTI_REG  *) EXTI_BASE)
//-*-*-*-*-*-*-*-*-*-*-*-
//clock enable Macros:
//-*-*-*-*-*-*-*-*-*-*-*
#define GPIOx_CLK_EN(x) RCC->APB2ENR |= 1<<(x-63)  //x is either 'A' or 'B' or 'C' .....
#define AFIO_CLK_EN()   RCC->APB2ENR |= 1<<0
//-*-*-*-*-*-*-*-*-*-*-*-*-
//NVIC IRQ Enable/Disable Macros:
//-*-*-*-*-*-*-*-*-*-*-*-*-
#define NVIC_IRQ6_EXTI0_Enable()		NVIC_ISER0 |=1<<6
#define NVIC_IRQ7_EXTI1_Enable()		NVIC_ISER0 |=1<<7
#define NVIC_IRQ8_EXTI2_Enable()		NVIC_ISER0 |=1<<8
#define NVIC_IRQ9_EXTI3_Enable()		NVIC_ISER0 |=1<<9
#define NVIC_IRQ10_EXTI4_Enable()		NVIC_ISER0 |=1<<10
#define NVIC_IRQ23_EXTI5_9_Enable()		NVIC_ISER0 |=1<<23
#define NVIC_IRQ40_EXTI10_15_Enable()	NVIC_ISER1 |=1<<8

#define NVIC_IRQ6_EXTI0_Disable()		NVIC_ICER0 |=1<<6
#define NVIC_IRQ7_EXTI1_Disable()		NVIC_ICER0 |=1<<7
#define NVIC_IRQ8_EXTI2_Disable()		NVIC_ICER0 |=1<<8
#define NVIC_IRQ9_EXTI3_Disable()		NVIC_ICER0 |=1<<9
#define NVIC_IRQ10_EXTI4_Disable()		NVIC_ICER0 |=1<<10
#define NVIC_IRQ23_EXTI5_9_Disable()	NVIC_ICER0 |=1<<23
#define NVIC_IRQ40_EXTI10_15_Disable()	NVIC_ICER1 |=1<<8

#endif /* STM32F103C6_H_ */
