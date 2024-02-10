/*
 * EXTI.c
 *
 *  Created on: Aug 3, 2023
 *      Author: assem
 */

/* ============== Includes =============== */
#include "EXTI.h"
#include "GPIO.h"
/* ============== Generic Variables =============== */
void(*g_P_IRQ_CallBack[16])(void);
/* =============== Generic Macros ================= */
#define AFIO_GPIO_EXTI_Mapping(x)	((x == GPIOA)? 0:\
									(x == GPIOB)? 1:\
									(x == GPIOC)? 2:3) // 3 if x == GPIOD
/**================================================================
 * @Fn				- MCAL_EXTI_GPIO_Init
 * @brief			- This Is Used To Initialize EXTI From Specific GPIO PIN and Specify Mask/Trigger Condition and IRQ CallBack
 * @param [in] 		- EXTI_Config: set by @ref EXTI_define, EXTI_Trigger_define and EXTI_IRQ_define
 * @retval 			- None
 * Note				- None
 */

void MCAL_EXTI_GPIO_Init(EXTI_PinConfig_t* EXTI_Config){
	//1- Configure GPIO to be AF Floating Input
	GPIO_PinConfig_t pincfg;
	pincfg.GPIO_PinNumber = EXTI_Config->EXTI_PIN.GPIO_PIN;
	pincfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIOx_Init(EXTI_Config->EXTI_PIN.GPIOx, &pincfg);
	//==============================================
	//2- Configure AFIO to Select the wanted EXTI Line with PORT A or B or C or D
	uint8_t EXTICR_index 	 		 = (EXTI_Config->EXTI_PIN.EXTIx)/4;
	uint8_t EXTICR_BitField_position = ((EXTI_Config->EXTI_PIN.EXTIx)%4)*4;
	
	AFIO->EXTICR[EXTICR_index] &= ~(0xf <<EXTICR_BitField_position); //Clear the four bit first
	AFIO->EXTICR[EXTICR_index] |= AFIO_GPIO_EXTI_Mapping(EXTI_Config->EXTI_PIN.GPIOx) << EXTICR_BitField_position;
	//======================================
	//3- Configure EXTI Rising and falling trigger
	//a. clear the bit first
	EXTI->RTSR &= ~(1<<EXTI_Config->EXTI_PIN.EXTIx);
	EXTI->FTSR &= ~(1<<EXTI_Config->EXTI_PIN.EXTIx);
	//b. set the trigger case
	switch(EXTI_Config->Trigger_Case){
	case EXTI_Trigger_RISING:
		EXTI->RTSR |= 1<<EXTI_Config->EXTI_PIN.EXTIx;
		break;
	case EXTI_Trigger_FALLING:
		EXTI->FTSR |= 1<<EXTI_Config->EXTI_PIN.EXTIx;
		break;
	case EXTI_Trigger_RisingAndFalling:
		EXTI->RTSR |= 1<<EXTI_Config->EXTI_PIN.EXTIx;
		EXTI->FTSR |= 1<<EXTI_Config->EXTI_PIN.EXTIx;
		break;
	}
	//===================================
	// 4- Enable/Disable INTERRUPT MASK for the wanted EXTI input line in EXTI Peripheral and NVIC
	switch(EXTI_Config->IRQ_EN){

	case EXTI_IRQ_Enable:
		//Enable NTERRUPT MASK for the wanted EXTI input line in EXTI Peripheral
		EXTI->IMR |= 1<<EXTI_Config->EXTI_PIN.EXTIx;
		//Enable NTERRUPT MASK for the wanted EXTI input line in NVIC
		if(EXTI_Config->EXTI_PIN.EXTIx == 0)
			NVIC_IRQ6_EXTI0_Enable();
		else if(EXTI_Config->EXTI_PIN.EXTIx == 1)
			NVIC_IRQ7_EXTI1_Enable();
		else if(EXTI_Config->EXTI_PIN.EXTIx == 2)
			NVIC_IRQ8_EXTI2_Enable();
		else if(EXTI_Config->EXTI_PIN.EXTIx == 3)
			NVIC_IRQ9_EXTI3_Enable();
		else if(EXTI_Config->EXTI_PIN.EXTIx == 4)
			NVIC_IRQ10_EXTI4_Enable();
		else if((EXTI_Config->EXTI_PIN.EXTIx >= 5) && (EXTI_Config->EXTI_PIN.EXTIx <= 9))
			NVIC_IRQ23_EXTI5_9_Enable();
		else if((EXTI_Config->EXTI_PIN.EXTIx >= 10) && (EXTI_Config->EXTI_PIN.EXTIx <= 15))
			NVIC_IRQ40_EXTI10_15_Enable();
		break;

	case EXTI_IRQ_Disable:
		//Disable NTERRUPT MASK for the wanted EXTI input line in EXTI Peripheral
		EXTI->IMR &= ~(1<<EXTI_Config->EXTI_PIN.EXTIx);
		//Disable NTERRUPT MASK for the wanted EXTI input line in NVIC
		if(EXTI_Config->EXTI_PIN.EXTIx == 0)
			NVIC_IRQ6_EXTI0_Disable();
		else if(EXTI_Config->EXTI_PIN.EXTIx == 1)
			NVIC_IRQ7_EXTI1_Disable();
		else if(EXTI_Config->EXTI_PIN.EXTIx == 2)
			NVIC_IRQ8_EXTI2_Disable();
		else if(EXTI_Config->EXTI_PIN.EXTIx == 3)
			NVIC_IRQ9_EXTI3_Disable();
		else if(EXTI_Config->EXTI_PIN.EXTIx == 4)
			NVIC_IRQ10_EXTI4_Disable();
		else if((EXTI_Config->EXTI_PIN.EXTIx >= 5) && (EXTI_Config->EXTI_PIN.EXTIx <= 9))
			NVIC_IRQ23_EXTI5_9_Disable();
		else if((EXTI_Config->EXTI_PIN.EXTIx >= 10) && (EXTI_Config->EXTI_PIN.EXTIx <= 15))
			NVIC_IRQ40_EXTI10_15_Disable();
		break;
	}
	//========================
	// 5- Set IRQ_CallBack function
	g_P_IRQ_CallBack[EXTI_Config->EXTI_PIN.EXTIx] = EXTI_Config->P_IRQ_CallBack;

}
/**================================================================
 * @Fn				- MCAL_EXTI_GPIO_DeInit
 * @brief			- Reset EXTI Registers and NVIC corresponding IRQ Mask
 * @retval 			- None
 * Note				- None
 */
void MCAL_EXTI_GPIO_DeInit(void){
	//Reset EXTI Peripheral
	EXTI->IMR 	= 0x00000000;
	EXTI->EMR	= 0x00000000;
	EXTI->RTSR 	= 0x00000000;
	EXTI->FTSR 	= 0x00000000;
	EXTI->SWIER = 0x00000000;
	EXTI->PR 	= 0xFFFFFFFF;
	//Disable IRQ0-15 @NVIC
	NVIC_IRQ6_EXTI0_Disable();
	NVIC_IRQ7_EXTI1_Disable();
	NVIC_IRQ8_EXTI2_Disable();
	NVIC_IRQ9_EXTI3_Disable();
	NVIC_IRQ10_EXTI4_Disable();
	NVIC_IRQ23_EXTI5_9_Disable();
	NVIC_IRQ40_EXTI10_15_Disable();
}
/**================================================================
 * @Fn				- MCAL_EXTI_GPIO_Update
 * @brief			- This Is Used To Update EXTI From Specific GPIO PIN and Specify Mask/Trigger Condition and IRQ CallBack
 * @param [in] 		- EXTI_Config: set by @ref EXTI_define, EXTI_Trigger_define and EXTI_IRQ_define
 * @retval 			- None
 * Note				- None
 */
void MCAL_EXTI_GPIO_Update(EXTI_PinConfig_t* EXTI_Config){
	MCAL_EXTI_GPIO_Init(EXTI_Config);
}

void EXTI0_IRQHandler(){
	//Clear Pending bit register
	EXTI->PR |= 1<<0;
	//Call IRQ_CallBack
	g_P_IRQ_CallBack[0]();
}
void EXTI1_IRQHandler(){
	//Clear Pending bit register
	EXTI->PR |= 1<<1;
	//Call IRQ_CallBack
	g_P_IRQ_CallBack[1]();
}
void EXTI2_IRQHandler(){
	//Clear Pending bit register
	EXTI->PR |= 1<<2;
	//Call IRQ_CallBack
	g_P_IRQ_CallBack[2]();
}
void EXTI3_IRQHandler(){
	//Clear Pending bit register
	EXTI->PR |= 1<<3;
	//Call IRQ_CallBack
	g_P_IRQ_CallBack[3]();
}
void EXTI4_IRQHandler(){
	//Clear Pending bit register
	EXTI->PR |= 1<<4;
	//Call IRQ_CallBack
	g_P_IRQ_CallBack[4]();
}
void EXTI9_5_IRQHandler(){

	if(EXTI->PR & 1<<5) {EXTI->PR |= 1<<5; g_P_IRQ_CallBack[5]();}
	if(EXTI->PR & 1<<6) {EXTI->PR |= 1<<6; g_P_IRQ_CallBack[6]();}
	if(EXTI->PR & 1<<7) {EXTI->PR |= 1<<7; g_P_IRQ_CallBack[7]();}
	if(EXTI->PR & 1<<8) {EXTI->PR |= 1<<8; g_P_IRQ_CallBack[8]();}
	if(EXTI->PR & 1<<9) {EXTI->PR |= 1<<9; g_P_IRQ_CallBack[9]();}

}
void EXTI15_10_IRQHandler(){

	if(EXTI->PR & 1<<10) {EXTI->PR |= 1<<10; g_P_IRQ_CallBack[10]();}
	if(EXTI->PR & 1<<11) {EXTI->PR |= 1<<11; g_P_IRQ_CallBack[11]();}
	if(EXTI->PR & 1<<12) {EXTI->PR |= 1<<12; g_P_IRQ_CallBack[12]();}
	if(EXTI->PR & 1<<13) {EXTI->PR |= 1<<13; g_P_IRQ_CallBack[13]();}
	if(EXTI->PR & 1<<14) {EXTI->PR |= 1<<14; g_P_IRQ_CallBack[14]();}
	if(EXTI->PR & 1<<15) {EXTI->PR |= 1<<15; g_P_IRQ_CallBack[15]();}

}
