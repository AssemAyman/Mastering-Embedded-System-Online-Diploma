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

#include"USART.h"

uint16_t buffer;

void UART_IRQ_Callback(){

	MCAL_USART_ReceiveData(USART1, &buffer, disable);
	MCAL_USART_SendData(USART1, &buffer, enable);

}

int main(void)
{

	USART_Config_t USART1cfg ;

	USART1cfg.USART_Mode = USART_Mode_Tx_Rx;
	USART1cfg.BaudRate = USART_BaudRate_115200;
	USART1cfg.Payload_Length = USART_Payload_Length_8B;
	USART1cfg.Parity = USART_Parity_NONE;
	USART1cfg.StopBits = USART_StopBits_1;
	USART1cfg.HwFlowCtl = USART_HwFlowCtl_NONE;
	USART1cfg.IRQ_Enable = USART_IRQ_Enable_RXNE;
	USART1cfg.P_IRQ_CallBack = UART_IRQ_Callback;

	MCAL_USART_Init(USART1, &USART1cfg);

	GPIOx_CLK_EN('A');

	MCAL_UASRT_GPIO_Set_Pins(USART1);


	while(1);

}
