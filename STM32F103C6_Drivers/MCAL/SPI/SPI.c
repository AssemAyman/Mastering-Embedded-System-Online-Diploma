/*
 * SPI.c
 *
 *  Created on: Aug 19, 2023
 *      Author: assem
 */


/* =========================== Includes =========================== */
/* ================================================================ */
#include "SPI.h"
#include "GPIO.h"
/* ===================== Generic Variables ======================== */
/* ================================================================ */
SPI_Config_t* g_SPI_Config[2] = {NULL, NULL};


/* ================================================================
 * @Fn 				- MCAL_SPI_Init
 * @brief 			- Initializes SPIx according to the specified parameters in SPI_Config_t
 * @param [in] 		- SPIx : where x can be (1..2 depending on device used) to select SPI peripheral
 * @param [in] 		- SPI_Config : a pointer to SPI_Config_t structure that contains the configuration information for the specified SPI Module
 * @retval 			- None
 * Note 			- Supported for SPI FULL DUPLEX Master/Slave only & NSS Hardware/Software
 * 					- You have to configure RCC to select clock for the selected SPI Module
 */
void MCAL_SPI_Init(SPIx_REG* SPIx,SPI_Config_t* SPI_Config){
	if(SPIx == SPI1){
		//Take a backup for SPI1 config register
		g_SPI_Config[0] = SPI_Config;
		/* 1. Open the SPI1 RCC Clock */
		SPI1_CLK_EN();

	}else if(SPIx == SPI2){
		//Take a backup for SPI2 config register
		g_SPI_Config[1] = SPI_Config;
		/* 1. Open the SPI2 RCC Clock */
		SPI2_CLK_EN();
	}

	/* 2.Choose Master or Slave */
	SPIx->CR1 |= SPI_Config->SPI_Mode;

	/* 3. Set Communication Mode */
	SPIx->CR1 |= SPI_Config->Communication_Mode;

	/* 4. Set Frame format */
	SPIx->CR1 |= SPI_Config->Frame_Format;

	/* 5. Set Data Size */
	SPIx->CR1 |= SPI_Config->DataSize;

	/* 6. Set Clock Polarity */
	SPIx->CR1 |= SPI_Config->CLK_Polarity;

	/* 7. Set Clock Phase */
	SPIx->CR1 |= SPI_Config->CLK_Phase;

	/* 8. Configure The NSS for master and Slave*/
	//A.In case of NSS will operate in SW mode
	if(SPI_Config->NSS == SPI_NSS_SW_Master || SPI_Config->NSS == SPI_NSS_SW_Slave){
		SPIx->CR1 |= SPI_Config->NSS;
	}
	//B.In case of NSS will operate in HW mode
	else{
		SPIx->CR2 |= SPI_Config->NSS;
	}

	/* 9. Set BaudRate Pre-Scaler */
	SPIx->CR1 |= SPI_Config->BaudRate_Prescaler;

	/* 10. Set Interrupt Type */
	if(SPI_Config->IRQ_Enable != SPI_IRQ_Enable_None){

		SPIx->CR2 |= SPI_Config->IRQ_Enable;

		if(SPIx == SPI1)
			NVIC_IRQ35_SPI1_Enable();
		else if(SPIx == SPI2)
			NVIC_IRQ36_SPI2_Enable();
	}

	/* 11. Enable SPI */
	SPIx->CR1 |= 1<<6;
}
/* ================================================================
 * @Fn 				- MCAL_SPI_DeInit
 * @brief 			- Resets Selected SPI Module
 * @param [in] 		- SPIx : where x can be (1..2 depending on device used) to select SPI peripheral
 * @retval 			- None
 * Note 			- Reset The Module By RCC & Disable NVIC
 */
void MCAL_SPI_DeInit(SPIx_REG* SPIx){
	if(SPIx == SPI1){
		RCC->APB2RSTR |= 1<<12;
		NVIC_IRQ35_SPI1_Disable();
	}
	else if(SPIx == SPI2){
		RCC->APB1RSTR |= 1<<14;
		NVIC_IRQ36_SPI2_Disable();
	}
}
/* ================================================================
 * @Fn 				- MCAL_SPI_GPIO_Set_Pins
 * @brief 			- Initializes GPIO Pins to be connected with the selected SPI
 * @param [in] 		- SPIx : where x can be (1..2 depending on device used) to select SPI peripheral
 * @retval 			- None
 * Note 			- Must open clock for GPIO After GPIO Initialization
 * 					- Supported for SPI FULL DUPLEX Master/Slave only & NSS Hardware/Software
 */
void MCAL_SPI_GPIO_Set_Pins(SPIx_REG* SPIx){

	GPIO_PinConfig_t GPIOcfg;

	if(SPIx == SPI1){

		GPIOx_CLK_EN('A');
		
		//in case of SPI1 is master
		if(g_SPI_Config[0]->SPI_Mode == SPI_MODE_Master){

			//Configure SPI1_SCK PA5
			GPIOcfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			GPIOcfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
			GPIOcfg.GPIO_PinNumber = GPIO_PIN_5;
			MCAL_GPIOx_Init(GPIOA, &GPIOcfg);

			//Configure SPI1_MOSI PA7
			GPIOcfg.GPIO_PinNumber = GPIO_PIN_7;
			MCAL_GPIOx_Init(GPIOA, &GPIOcfg);

			//Configure SPI1_MISO PA6
			GPIOcfg.GPIO_MODE = GPIO_MODE_AF_INPUT;
			GPIOcfg.GPIO_PinNumber = GPIO_PIN_6;
			MCAL_GPIOx_Init(GPIOA, &GPIOcfg);

			//Configure SPI1_NSS PA4
			/* A.if NSS of the master is configured as HW output  */
			if(g_SPI_Config[0]->NSS == SPI_NSS_HW_Master_OutPut){

				GPIOcfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
				GPIOcfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
				GPIOcfg.GPIO_PinNumber = GPIO_PIN_4;
				MCAL_GPIOx_Init(GPIOA, &GPIOcfg);

				/* B.if NSS of the master is configured as HW input  */
			}else if(g_SPI_Config[0]->NSS == SPI_NSS_HW_Master_Input){

				GPIOcfg.GPIO_MODE = GPIO_MODE_AF_INPUT;
				GPIOcfg.GPIO_PinNumber = GPIO_PIN_4;
				MCAL_GPIOx_Init(GPIOA, &GPIOcfg);
			}
			/* C.Software the pin is not used. can be used as a GPIO */
		}
		//in case of SPI1 is slave
		else{
			//Configure SPI1_SCK PA5
			GPIOcfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			GPIOcfg.GPIO_PinNumber = GPIO_PIN_5;
			MCAL_GPIOx_Init(GPIOA, &GPIOcfg);

			//Configure SPI1_MOSI PA7
			GPIOcfg.GPIO_PinNumber = GPIO_PIN_7;
			MCAL_GPIOx_Init(GPIOA, &GPIOcfg);

			//Configure SPI1_MISO PA6
			/* A. Full duplex / slave (point to point) Alternate function push-pull */
			GPIOcfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			GPIOcfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
			GPIOcfg.GPIO_PinNumber = GPIO_PIN_6;
			MCAL_GPIOx_Init(GPIOA, &GPIOcfg);
			/* B.TODO Full duplex / slave (multi-slave) Alternate function open drain */

			//Configure SPI1_NSS PA4
			/* A.if NSS of the slave is configured as HW input  */
			if(g_SPI_Config[0]->NSS == SPI_NSS_HW_Slave){
				GPIOcfg.GPIO_MODE = GPIO_MODE_AF_INPUT;
				GPIOcfg.GPIO_PinNumber = GPIO_PIN_4;
				MCAL_GPIOx_Init(GPIOA, &GPIOcfg);
			}
			/* B.Software the pin is not used. can be used as a GPIO */
		}
	}

	else if(SPIx == SPI2){

		GPIOx_CLK_EN('B');
		
		//in case of SPI2 is master
		if(g_SPI_Config[1]->SPI_Mode == SPI_MODE_Master){

			//Configure SPI2_SCK PB13
			GPIOcfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			GPIOcfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
			GPIOcfg.GPIO_PinNumber = GPIO_PIN_13;
			MCAL_GPIOx_Init(GPIOB, &GPIOcfg);

			//Configure SPI2_MOSI PB15
			GPIOcfg.GPIO_PinNumber = GPIO_PIN_15;
			MCAL_GPIOx_Init(GPIOB, &GPIOcfg);

			//Configure SPI2_MISO PB14
			GPIOcfg.GPIO_MODE = GPIO_MODE_AF_INPUT;
			GPIOcfg.GPIO_PinNumber = GPIO_PIN_14;
			MCAL_GPIOx_Init(GPIOB, &GPIOcfg);

			//Configure SPI2_NSS PB12
			/* A.if NSS of the master is configured as HW output  */
			if(g_SPI_Config[1]->NSS == SPI_NSS_HW_Master_OutPut){

				GPIOcfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
				GPIOcfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
				GPIOcfg.GPIO_PinNumber = GPIO_PIN_12;
				MCAL_GPIOx_Init(GPIOB, &GPIOcfg);

				/* B.if NSS of the master is configured as HW input  */
			}else if(g_SPI_Config[1]->NSS == SPI_NSS_HW_Master_Input){

				GPIOcfg.GPIO_MODE = GPIO_MODE_AF_INPUT;
				GPIOcfg.GPIO_PinNumber = GPIO_PIN_12;
				MCAL_GPIOx_Init(GPIOB, &GPIOcfg);
			}
			/* C.Software the pin is not used. can be used as a GPIO */
		}
		//in case of SPI2 is slave
		else{
			//Configure SPI2_SCK PB13
			GPIOcfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			GPIOcfg.GPIO_PinNumber = GPIO_PIN_13;
			MCAL_GPIOx_Init(GPIOB, &GPIOcfg);

			//Configure SPI2_MOSI PB15
			GPIOcfg.GPIO_PinNumber = GPIO_PIN_15;
			MCAL_GPIOx_Init(GPIOB, &GPIOcfg);

			//Configure SPI2_MISO PB14
			/* A. Full duplex / slave (point to point) Alternate function push-pull */
			GPIOcfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			GPIOcfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
			GPIOcfg.GPIO_PinNumber = GPIO_PIN_14;
			MCAL_GPIOx_Init(GPIOB, &GPIOcfg);
			/* B.TODO Full duplex / slave (multi-slave) Alternate function open drain */

			//Configure SPI2_NSS PB12
			/* A.if NSS of the slave is configured as HW input  */
			if(g_SPI_Config[1]->NSS == SPI_NSS_HW_Slave){
				GPIOcfg.GPIO_MODE = GPIO_MODE_AF_INPUT;
				GPIOcfg.GPIO_PinNumber = GPIO_PIN_12;
				MCAL_GPIOx_Init(GPIOB, &GPIOcfg);
			}
			/* B.Software the pin is not used. can be used as a GPIO */
		}
	}
}
/* ================================================================
 * @Fn 				- MCAL_SPI_SendData
 * @brief 			- Send Buffer With SPI
 * @param [in] 		- SPIx : where x can be (1..2 depending on device used) to select SPI peripheral
 * @param [in] 		- pTxBuffer : Pointer to buffer Which holds the Tx data
 * @param [in] 		- Polling : Enable Polling or Disable it
 * @retval 			- None
 * Note 			- None
 *
 */
void MCAL_SPI_SendData(SPIx_REG* SPIx,uint16_t* p_Txbuffer,PollingMechanism Polling){
	if(Polling == Enable)
		while(!(SPIx->SR & 1<<1)); //Wait until Tx buffer is empty to send data
	SPIx->DR = *p_Txbuffer;
}
/* ================================================================
 * @Fn 				- MCAL_SPI_RecieveData
 * @brief 			- Receive Buffer With SPI
 * @param [in] 		- SPIx : where x can be (1..2 depending on device used) to select SPI peripheral
 * @param [in] 		- pRxBuffer : Pointer to buffer which holds Rx data
 * @param [in] 		- Polling : Enable Polling or Disable it
 * @retval 			- None
 * Note 			- None
 */
void MCAL_SPI_ReceiveData(SPIx_REG* SPIx,uint16_t* p_Rxbuffer,PollingMechanism Polling){
	if(Polling == Enable)
		while(!(SPIx->SR & 1)); //Wait until Rx buffer is not empty to receive data
	*p_Rxbuffer = SPIx->DR ;
}
/* ================================================================
 * @Fn 				- MCAL_SPI_TX_RX
 * @brief 			- Transmit and Receive Data
 * @param [in] 		- SPIx : where x can be (1..2 depending on device used) to select SPI peripheral
 * @param [in] 		- pTxBuffer : Pointer to buffer which holds Transmit and Received data
 * @param [in] 		- Polling : Enable Polling or Disable it
 * @retval 			- None
 * Note 			- None
 */
void MCAL_SPI_TX_RX(SPIx_REG* SPIx,uint16_t* p_buffer,PollingMechanism Polling){
	if(Polling == Enable)
	{
		while(!(SPIx->SR & 1<<1));  //Wait until Tx buffer is empty to send data
	}
	SPIx->DR = *p_buffer;

	if(Polling == Enable)
	{
		while(!(SPIx->SR & 1)); //Wait until Rx buffer is not empty to receive data
	}
	*p_buffer = SPIx->DR ;
}

/* ================================================================ */
/* ================= IRQ Function Definitions ===================== */
/* ================================================================ */
S_IRQ_SRC_t irq_src;

void SPI1_IRQHandler(){

	irq_src.TXE = (SPI1->SR >> 1)&1;
	irq_src.RXNE = (SPI1->SR )&1;
	irq_src.ERRI = ((SPI1->SR >> 4)&1) | ((SPI1->SR >> 5)&1) | ((SPI1->SR >> 6)&1);

	g_SPI_Config[0]->P_IRQ_CallBack(irq_src);
}
void SPI2_IRQHandler(){

	irq_src.TXE = (SPI2->SR >> 1)&1;
	irq_src.RXNE = (SPI2->SR )&1;
	irq_src.ERRI = ((SPI2->SR >> 4)&1) | ((SPI2->SR >> 5)&1) | ((SPI2->SR >> 6)&1);

	g_SPI_Config[1]->P_IRQ_CallBack(irq_src);
}
