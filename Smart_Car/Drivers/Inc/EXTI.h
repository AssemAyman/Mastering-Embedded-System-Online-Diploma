/*
 * EXTI.h
 *
 *  Created on: Aug 3, 2023
 *      Author: assem
 */

#ifndef EXTI_H_
#define EXTI_H_

/* =========================== Includes =========================== */
#include "GPIO.h"
#include "STM32F103C6.h"
/* =====================Configuration Structure==================== */
typedef struct{
	uint8_t    EXTIx;				 // Choose The Line Number To Use in EXTI
	GPIOx_REG* GPIOx;                // GPIO Port Used For EXTI Driver
	uint16_t   GPIO_PIN;			 // GPIO Pin Used For EXTI Driver
}EXTI_GPIO_Mapping_t;

typedef struct{
	EXTI_GPIO_Mapping_t EXTI_PIN;       // Specifics the EXTI GPIO Mapping
								        // This parameter must be set based on @ref EXTI_define

	uint8_t				Trigger_Case;   // Specifics RISING or FALLING or Both trigger
										// This parameter must be set based on @ref EXTI_Trigger_define

	uint8_t				IRQ_EN;	        // Enable or Disable the EXTI IRQ (That will enable or disable the IRQ mask in EXTI and also on the NVIC)
										// This parameter must be set based on @ref EXTI_IRQ_define

	void(*P_IRQ_CallBack)(void);		//Set the C Function() which will be called once the IRQ happen

}EXTI_PinConfig_t;

#define EXTI0		0
#define EXTI1		1
#define EXTI2		2
#define EXTI3		3
#define EXTI4		4
#define EXTI5		5
#define EXTI6		6
#define EXTI7		7
#define EXTI8		8
#define EXTI9		9
#define EXTI10		10
#define EXTI11		11
#define EXTI12		12
#define EXTI13		13
#define EXTI14		14
#define EXTI15		15

/* =====================Configuration References Macros ==================== */
// @ref EXTI_define
//EXTI0
#define EXTI0PA0        (EXTI_GPIO_Mapping_t){EXTI0, GPIOA, GPIO_PIN_0}
#define EXTI0PB0        (EXTI_GPIO_Mapping_t){EXTI0, GPIOB, GPIO_PIN_0}
#define EXTI0PC0        (EXTI_GPIO_Mapping_t){EXTI0, GPIOC, GPIO_PIN_0}
#define EXTI0PD0        (EXTI_GPIO_Mapping_t){EXTI0, GPIOD, GPIO_PIN_0}

//EXTI1
#define EXTI1PA1        (EXTI_GPIO_Mapping_t){EXTI1, GPIOA, GPIO_PIN_1}
#define EXTI1PB1        (EXTI_GPIO_Mapping_t){EXTI1, GPIOB, GPIO_PIN_1}
#define EXTI1PC1        (EXTI_GPIO_Mapping_t){EXTI1, GPIOC, GPIO_PIN_1}
#define EXTI1PD1        (EXTI_GPIO_Mapping_t){EXTI1, GPIOD, GPIO_PIN_1}

//EXTI2
#define EXTI2PA2        (EXTI_GPIO_Mapping_t){EXTI2, GPIOA, GPIO_PIN_2}
#define EXTI2PB2        (EXTI_GPIO_Mapping_t){EXTI2, GPIOB, GPIO_PIN_2}
#define EXTI2PC2        (EXTI_GPIO_Mapping_t){EXTI2, GPIOC, GPIO_PIN_2}
#define EXTI2PD2        (EXTI_GPIO_Mapping_t){EXTI2, GPIOD, GPIO_PIN_2}

//EXTI3
#define EXTI3PA3        (EXTI_GPIO_Mapping_t){EXTI3, GPIOA, GPIO_PIN_3}
#define EXTI3PB3        (EXTI_GPIO_Mapping_t){EXTI3, GPIOB, GPIO_PIN_3}
#define EXTI3PC3        (EXTI_GPIO_Mapping_t){EXTI3, GPIOC, GPIO_PIN_3}
#define EXTI3PD3        (EXTI_GPIO_Mapping_t){EXTI3, GPIOD, GPIO_PIN_3}

//EXTI4
#define EXTI4PA4        (EXTI_GPIO_Mapping_t){EXTI4, GPIOA, GPIO_PIN_4}
#define EXTI4PB4        (EXTI_GPIO_Mapping_t){EXTI4, GPIOB, GPIO_PIN_4}
#define EXTI4PC4        (EXTI_GPIO_Mapping_t){EXTI4, GPIOC, GPIO_PIN_4}
#define EXTI4PD4        (EXTI_GPIO_Mapping_t){EXTI4, GPIOD, GPIO_PIN_4}

//EXTI5
#define EXTI5PA5        (EXTI_GPIO_Mapping_t){EXTI5, GPIOA, GPIO_PIN_5}
#define EXTI5PB5        (EXTI_GPIO_Mapping_t){EXTI5, GPIOB, GPIO_PIN_5}
#define EXTI5PC5        (EXTI_GPIO_Mapping_t){EXTI5, GPIOC, GPIO_PIN_5}
#define EXTI5PD5        (EXTI_GPIO_Mapping_t){EXTI5, GPIOD, GPIO_PIN_5}

//EXTI6
#define EXTI6PA6        (EXTI_GPIO_Mapping_t){EXTI6, GPIOA, GPIO_PIN_6}
#define EXTI6PB6        (EXTI_GPIO_Mapping_t){EXTI6, GPIOB, GPIO_PIN_6}
#define EXTI6PC6        (EXTI_GPIO_Mapping_t){EXTI6, GPIOC, GPIO_PIN_6}
#define EXTI6PD6        (EXTI_GPIO_Mapping_t){EXTI6, GPIOD, GPIO_PIN_6}

//EXTI7
#define EXTI7PA7        (EXTI_GPIO_Mapping_t){EXTI7, GPIOA, GPIO_PIN_7}
#define EXTI7PB7        (EXTI_GPIO_Mapping_t){EXTI7, GPIOB, GPIO_PIN_7}
#define EXTI7PC7        (EXTI_GPIO_Mapping_t){EXTI7, GPIOC, GPIO_PIN_7}
#define EXTI7PD7        (EXTI_GPIO_Mapping_t){EXTI7, GPIOD, GPIO_PIN_7}

//EXTI8
#define EXTI8PA8        (EXTI_GPIO_Mapping_t){EXTI8, GPIOA, GPIO_PIN_8}
#define EXTI8PB8        (EXTI_GPIO_Mapping_t){EXTI8, GPIOB, GPIO_PIN_8}
#define EXTI8PC8        (EXTI_GPIO_Mapping_t){EXTI8, GPIOC, GPIO_PIN_8}
#define EXTI8PD8        (EXTI_GPIO_Mapping_t){EXTI8, GPIOD, GPIO_PIN_8}

//EXTI9
#define EXTI9PA9        (EXTI_GPIO_Mapping_t){EXTI9, GPIOA, GPIO_PIN_9}
#define EXTI9PB9        (EXTI_GPIO_Mapping_t){EXTI9, GPIOB, GPIO_PIN_9}
#define EXTI9PC9        (EXTI_GPIO_Mapping_t){EXTI9, GPIOC, GPIO_PIN_9}
#define EXTI9PD9        (EXTI_GPIO_Mapping_t){EXTI9, GPIOD, GPIO_PIN_9}

//EXTI10
#define EXTI10PA10      (EXTI_GPIO_Mapping_t){EXTI10, GPIOA, GPIO_PIN_10}
#define EXTI10PB10      (EXTI_GPIO_Mapping_t){EXTI10, GPIOB, GPIO_PIN_10}
#define EXTI10PC10      (EXTI_GPIO_Mapping_t){EXTI10, GPIOC, GPIO_PIN_10}
#define EXTI10PD10      (EXTI_GPIO_Mapping_t){EXTI10, GPIOD, GPIO_PIN_10}

//EXTI11
#define EXTI11PA11      (EXTI_GPIO_Mapping_t){EXTI11, GPIOA, GPIO_PIN_11}
#define EXTI11PB11      (EXTI_GPIO_Mapping_t){EXTI11, GPIOB, GPIO_PIN_11}
#define EXTI11PC11      (EXTI_GPIO_Mapping_t){EXTI11, GPIOC, GPIO_PIN_11}
#define EXTI11PD11      (EXTI_GPIO_Mapping_t){EXTI11, GPIOD, GPIO_PIN_11}

//EXTI12
#define EXTI12PA12      (EXTI_GPIO_Mapping_t){EXTI12, GPIOA, GPIO_PIN_12}
#define EXTI12PB12      (EXTI_GPIO_Mapping_t){EXTI12, GPIOB, GPIO_PIN_12}
#define EXTI12PC12      (EXTI_GPIO_Mapping_t){EXTI12, GPIOC, GPIO_PIN_12}
#define EXTI12PD12      (EXTI_GPIO_Mapping_t){EXTI12, GPIOD, GPIO_PIN_12}

//EXTI13
#define EXTI13PA13      (EXTI_GPIO_Mapping_t){EXTI13, GPIOA, GPIO_PIN_13}
#define EXTI13PB13      (EXTI_GPIO_Mapping_t){EXTI13, GPIOB, GPIO_PIN_13}
#define EXTI13PC13      (EXTI_GPIO_Mapping_t){EXTI13, GPIOC, GPIO_PIN_13}
#define EXTI13PD13      (EXTI_GPIO_Mapping_t){EXTI13, GPIOD, GPIO_PIN_13}

//EXTI14
#define EXTI14PA14      (EXTI_GPIO_Mapping_t){EXTI14, GPIOA, GPIO_PIN_14}
#define EXTI14PB14      (EXTI_GPIO_Mapping_t){EXTI14, GPIOB, GPIO_PIN_14}
#define EXTI14PC14      (EXTI_GPIO_Mapping_t){EXTI14, GPIOC, GPIO_PIN_14}
#define EXTI14PD14      (EXTI_GPIO_Mapping_t){EXTI14, GPIOD, GPIO_PIN_14}

//EXTI15
#define EXTI15PA15      (EXTI_GPIO_Mapping_t){EXTI15, GPIOA, GPIO_PIN_15}
#define EXTI15PB15      (EXTI_GPIO_Mapping_t){EXTI15, GPIOB, GPIO_PIN_15}
#define EXTI15PC15      (EXTI_GPIO_Mapping_t){EXTI15, GPIOC, GPIO_PIN_15}
#define EXTI15PD15      (EXTI_GPIO_Mapping_t){EXTI15, GPIOD, GPIO_PIN_15}
//=========================
//@ref EXTI_Trigger_define
#define EXTI_Trigger_RISING				0
#define EXTI_Trigger_FALLING			1
#define EXTI_Trigger_RisingAndFalling	2
//==========================
//@ref EXTI_IRQ_define
#define	EXTI_IRQ_Enable					1
#define	EXTI_IRQ_Disable				0

/* ============== APIs Supported by "MCAL EXTI DRIVER" =========== */
extern void MCAL_EXTI_GPIO_Init(EXTI_PinConfig_t*);
extern void MCAL_EXTI_GPIO_DeInit(void);
extern void MCAL_EXTI_GPIO_Update(EXTI_PinConfig_t*);

#endif /* EXTI_H_ */
