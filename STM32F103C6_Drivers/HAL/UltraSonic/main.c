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

#include "USART.h"
#include "GPIO.h"
#include "Timer.h"
#include "EXTI.h"
#include "RCC.h"
#include <stdio.h>

void Echo();

int main(void)
{
	GPIOx_CLK_EN('A');
	GPIOx_CLK_EN('B');
	Timer2_init();
	Timer3_init();

	//Make A0 (Trigger pin) as an output
	GPIO_PinConfig_t A0;
	A0.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	A0.GPIO_OUTPUT_SPEED = GPIO_SPEED_2M;
	A0.GPIO_PinNumber = GPIO_PIN_0;

	MCAL_GPIOx_Init(GPIOA, &A0);

	//Initialize uart to use Bluetooth module to send distance to the mobile
	USART_Config_t USART1cfg ;

	USART1cfg.USART_Mode = USART_Mode_Tx;
	USART1cfg.BaudRate = USART_BaudRate_9600;
	USART1cfg.Payload_Length = USART_Payload_Length_8B;
	USART1cfg.Parity = USART_Parity_NONE;
	USART1cfg.StopBits = USART_StopBits_1;
	USART1cfg.HwFlowCtl = USART_HwFlowCtl_NONE;
	USART1cfg.IRQ_Enable = USART_IRQ_Enable_NONE;
	USART1cfg.P_IRQ_CallBack = NULL;

	MCAL_USART_Init(USART1, &USART1cfg);

	MCAL_UASRT_GPIO_Set_Pins(USART1);

	//Make A1(Echo pin) an external interrupt pin in both rising and falling
	EXTI_PinConfig_t pincfg;

	pincfg.EXTI_PIN = EXTI1PA1;
	pincfg.Trigger_Case = EXTI_Trigger_RisingAndFalling;
	pincfg.IRQ_EN = EXTI_IRQ_Enable;
	pincfg.P_IRQ_CallBack = Echo;

	MCAL_EXTI_GPIO_Init(&pincfg);

	while(1){
		//Send a trigger pulse to the ultrasonic
		MCAL_GPIOx_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
		dms(30);
		MCAL_GPIOx_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
		dms(1);
	}

}

Entery_t entery_index = first_entry;

void Echo(){

	if(entery_index == first_entry){
		entery_index = second_entery;
		Time_Claculation(first_entry);
	}else{
		entery_index = first_entry;
		char text[7]={0};
		u_int32_t distance = (170 * Time_Claculation(second_entery)) / 10000;
		sprintf(text,"%lucm\n",distance);
		//Send the distance to the Bluetooth module
		MCAL_USART_SendData(USART1, (uint16_t*)&text[0], enable);
		MCAL_USART_SendData(USART1, (uint16_t*)&text[1], enable);
		MCAL_USART_SendData(USART1, (uint16_t*)&text[2], enable);
		MCAL_USART_SendData(USART1, (uint16_t*)&text[3], enable);
		MCAL_USART_SendData(USART1, (uint16_t*)&text[4], enable);
		MCAL_USART_SendData(USART1, (uint16_t*)&text[5], enable);
		MCAL_USART_SendData(USART1, (uint16_t*)&text[6], enable);
	}
}
