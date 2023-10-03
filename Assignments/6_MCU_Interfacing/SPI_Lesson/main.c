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
#include "SPI.h"

#define Master
//#define Slave

uint16_t buffer;

void USART1_IRQ_CallBack(){
#ifdef Master
	MCAL_USART_ReceiveData(USART1, &buffer, disable);
	MCAL_USART_SendData(USART1, &buffer,enable);
	MCAL_GPIOx_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
	MCAL_SPI_TX_RX(SPI1, &buffer, Enable);
	MCAL_GPIOx_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
#endif
}

void SPI1_IRQ_CallBack(S_IRQ_SRC_t irq_src){
#ifdef Slave
	if(irq_src.RXNE){
	MCAL_SPI_ReceiveData(SPI1, &buffer, Disable);
	MCAL_USART_SendData(USART1, &buffer, enable);
	}
#endif
}

int main(void)
{

	GPIOx_CLK_EN('A');
	MCAL_UASRT_GPIO_Set_Pins(USART1);

	USART_Config_t USART1cfg ;

	USART1cfg.USART_Mode = USART_Mode_Tx_Rx;
	USART1cfg.BaudRate = USART_BaudRate_115200;
	USART1cfg.Payload_Length = USART_Payload_Length_8B;
	USART1cfg.Parity = USART_Parity_NONE;
	USART1cfg.StopBits = USART_StopBits_1;
	USART1cfg.HwFlowCtl = USART_HwFlowCtl_NONE;
	USART1cfg.IRQ_Enable = USART_IRQ_Enable_RXNE;
	USART1cfg.P_IRQ_CallBack =  USART1_IRQ_CallBack;

	MCAL_USART_Init(USART1, &USART1cfg);


	SPI_Config_t SPI1cfg;

	SPI1cfg.BaudRate_Prescaler = SPI_BAUDERATE_PRESCALER_8;
	SPI1cfg.CLK_Phase = SPI_CLK_PHASE_SecondEdge_Capture;
	SPI1cfg.CLK_Polarity = SPI_CLK_POLARITY_IDLE_HIGH;
	SPI1cfg.Communication_Mode = SPI_Communication_Mode_2LINE_FULL_DUPLEX;
	SPI1cfg.DataSize = SPI_DataSize_8bit;
	SPI1cfg.Frame_Format = SPI_Frame_Format_MSB_First;

#ifdef Master
	SPI1cfg.SPI_Mode = SPI_MODE_Master;
	SPI1cfg.NSS = SPI_NSS_SW_Master;
	SPI1cfg.IRQ_Enable = SPI_IRQ_Enable_None;
	SPI1cfg.P_IRQ_CallBack = NULL;

	/*Configure SS on PA4 */
	GPIO_PinConfig_t GPIOcfg;

	GPIOcfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	GPIOcfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	GPIOcfg.GPIO_PinNumber = GPIO_PIN_4;

	MCAL_GPIOx_Init(GPIOA, &GPIOcfg);
	MCAL_GPIOx_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
#endif

#ifdef Slave
	SPI1cfg.SPI_Mode = SPI_MODE_Slave;
	SPI1cfg.NSS = SPI_NSS_HW_Slave;
	SPI1cfg.IRQ_Enable = SPI_IRQ_Enable_RXNEIE;
	SPI1cfg.P_IRQ_CallBack = SPI1_IRQ_CallBack;
#endif

	MCAL_SPI_Init(SPI1, &SPI1cfg);
	MCAL_SPI_GPIO_Set_Pins(SPI1);

	while(1);

}
