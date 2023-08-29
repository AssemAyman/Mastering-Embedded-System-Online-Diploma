/*
 * I2C.c
 *
 *  Created on: Aug 26, 2023
 *      Author: assem
 */

/* =========================== Includes =========================== */
#include "I2C.h"

/* ===================== Generic Variables ======================== */
I2C_Config_t g_I2C_Config[2];


/* ================================================================
 * @Fn 				- MCAL_I2C_Init
 * @brief 			- Initializes I2Cx according to the specified parameters in I2C_Config
 * @param [in] 		- I2Cx : where x can be (1..2 depending on device used) to select I2C peripheral
 * @param [in] 		- I2C_Config : a pointer to I2C_Config_t structure that contains the configuration information for the specified I2C Module
 * @retval 			- None
 * Note 			- Supported for I2C SM mode only
 * 					- Support only 7-bit address mode
 */
void MCAL_I2C_Init(I2Cx_REG* I2Cx,I2C_Config_t* I2C_Config){

	uint32_t pclk1;

	/* 1. Enable the RCC Clock */
	if(I2Cx == I2C1){
		/* If I2C1 Put all configurations in the global configuration */
		g_I2C_Config[0] = *I2C_Config;
		/* Open the I2C1 RCC Clock */
		I2C1_CLK_EN();

	}else if (I2Cx == I2C2){
		/* If I2C2 Put all configurations in the global configuration */
		g_I2C_Config[1] = *I2C_Config;
		/* Open the I2C2 RCC Clock */
		I2C2_CLK_EN();

	}

	/* 2.Program the peripheral input clock in I2C_CR2 Register in order to generate correct timings */
	pclk1 = MCAL_RCC_GetPCLK1();
	I2Cx->CR2 |= pclk1 / 1000000;

	/* 3.Configure the clock control registers */
	I2Cx->CCR |= pclk1 / (2 * I2C_Config->Clock_Speed);

	/* 4.Configure the rise time register */
	I2Cx->TRISE = (I2Cx->CR2 & 0x3f) + 1 ;

	/* 5. Enable/Disable Stretch Mode*/
	I2Cx->CR1 |= I2C_Config->Stretch_Mode;

	/* 6. Enable/Disable General Call*/
	I2Cx->CR1 |= I2C_Config->General_Call;

	/* 7. Enable Acknowledge */
	I2Cx->CR1 |= (1<<10);

	/* 8. Set 7-bit Slave Address */
	if(I2C_Config->Slave_Address.Dual_ADD == 0){

		I2Cx->OAR1 = I2C_Config->Slave_Address.Primary_Slave_address << 1;

	}else{

		I2Cx->OAR1 = I2C_Config->Slave_Address.Primary_Slave_address   << 1;
		I2Cx->OAR2 = I2C_Config->Slave_Address.Secondary_Slave_address << 1 | 1;

	}

	/* 9. Configure Interrupts for (Slave Mode) */
	if(I2C_Config->P_Slave_Event_CallBack != NULL){

		//Enable IRQ
		I2Cx->CR2 |= 0b111<<8;

		if(I2Cx == I2C1){

			NVIC_IRQ31_I2C1_EV_Enable();
			NVIC_IRQ32_I2C1_ER_Enable();

		}else if(I2Cx == I2C2){

			NVIC_IRQ33_I2C2_EV_Enable();
			NVIC_IRQ34_I2C2_ER_Enable();
		}
	}

	/* 10.Program the I2C_CR1 register to enable the peripheral*/
	I2Cx->CR1 |= 1;
}
/* ================================================================
 * @Fn 				- MCAL_I2C_DeInit
 * @brief 			- Resets Selected I2C Module and disable NVIC IRQs
 * @param [in] 		- I2Cx : where x can be (1..2 depending on device used) to select I2C peripheral
 * @retval 			- None
 * Note 			- Reset The Module By RCC & Disable NVIC
 */
void MCAL_I2C_DeInit(I2Cx_REG* I2Cx){

	if(I2Cx == I2C1){

		RCC->APB1RSTR |= 1<<21;
		NVIC_IRQ31_I2C1_EV_Disable();
		NVIC_IRQ32_I2C1_ER_Disable();

	}else if(I2Cx == I2C2){

		RCC->APB1RSTR |= 1<<22;
		NVIC_IRQ33_I2C2_EV_Disable();
		NVIC_IRQ34_I2C2_ER_Disable();

	}
}
/* ================================================================
 * @Fn 				- MCAL_I2C_GPIO_Set_Pins
 * @brief 			- Initializes GPIO Pins to be connected with the selected I2C
 * @param [in] 		- I2Cx : where x can be (1..2 depending on device used) to select I2C peripheral
 * @retval 			- None
 * Note 			- Must open clock for  GPIO After GPIO Initialization
 * 					- Supported for I2C SM MODE only
 */
void MCAL_I2C_GPIO_Set_Pins(I2Cx_REG* I2Cx){

	GPIO_PinConfig_t Pincfg;

	Pincfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_OD;
	Pincfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;

	if(I2Cx == I2C1){
		//I2C1_SCL PB6
		Pincfg.GPIO_PinNumber = GPIO_PIN_6;
		MCAL_GPIOx_Init(GPIOB,&Pincfg);

		//I2C1_SDA PB7
		Pincfg.GPIO_PinNumber = GPIO_PIN_7;
		MCAL_GPIOx_Init(GPIOB,&Pincfg);

	}else if(I2Cx == I2C2){
		//I2C2_SCL PB10
		Pincfg.GPIO_PinNumber = GPIO_PIN_10;
		MCAL_GPIOx_Init(GPIOB,&Pincfg);

		//I2C2_SDA PB11
		Pincfg.GPIO_PinNumber = GPIO_PIN_11;
		MCAL_GPIOx_Init(GPIOB,&Pincfg);
	}
}
/* ================================================================
 * @Fn 				- MCAL_I2C_MASTER_TX
 * @brief 			- Master Send data with I2C
 * @param [in] 		- I2Cx : where x can be (1..2 depending on device used) to select I2C peripheral
 * @param [in] 		- slaveAddr : slave address
 * @param [in] 		- p_dataOut : a pointer to the data which will be send
 * @param [in] 		- dataLen : number of data bytes to be Transmitted
 * @param [in] 		- Stop : select send stop bit or not
 * @param [in] 		- Start : select send start or repeated start
 * @retval 			- None
 * Note 			- None
 */
void MCAL_I2C_Master_TX(I2Cx_REG* I2Cx,uint8_t slaveAddr,uint8_t* p_dataOut,uint16_t dataLen,Stop_Condition Stop,START_Condition start){

	/* 1. Set the start bit in the I2C_CR1 register to generate a start condition from this will start as master */
	I2C_GenerateSTART(I2Cx,start);

	/* 2. Wait for SB == 1 */
	while(!(I2C_GetFlagStatus(I2Cx,SB)));

	/* 3. Send Address */
	I2C_SendAddress(I2Cx,slaveAddr,write);

	/* 4. Wait for ADDR == 1*/
	while(!(I2C_GetFlagStatus(I2Cx,ADDR)));

	/* 5. Wait for EV8_1 */
	while(!(I2C_GetFlagStatus(I2Cx,EV8_1)));

	/* 6. Send Data*/
	for(int i = 0; i<dataLen; i++){
		I2Cx->DR = p_dataOut[i];
		//Wait for transmit buffer to be empty to send another byte
		while(!(I2C_GetFlagStatus(I2Cx,TxE)));
	}

	/* 7. Wait for Shift register to be empty*/
	while(!(I2C_GetFlagStatus(I2Cx,BTF)));

	/* 8. Send Stop condition */
	if(Stop == with_Stop)
		I2C_GenerateSTOP(I2Cx);
}
/* ================================================================
 * @Fn 				- MCAL_I2C_MASTER_RX
 * @brief 			- Master Receive data with I2C
 * @param [in] 		- I2Cx : where x can be (1..2 depending on device used) to select I2C peripheral
 * @param [in] 		- slaveAddr : slave address
 * @param [in] 		- p_datain : a pointer to the data which will be received
 * @param [in] 		- dataLen : number of data bytes to be Received
 * @param [in] 		- Stop : select send stop bit or not
 * @param [in] 		- Start : select send start or repeated start
 * @retval 			- None
 * Note 			- None
 */
void MCAL_I2C_Master_RX(I2Cx_REG* I2Cx,uint8_t slaveAddr,uint8_t* p_datain,uint16_t dataLen,Stop_Condition Stop,START_Condition start){

	/* 1. Set the start bit in the I2C_CR1 register to generate a start condition from this will start as master */
	I2C_GenerateSTART(I2Cx,start);

	/* 2. Wait for SB == 1 */
	while(!(I2C_GetFlagStatus(I2Cx,SB)));

	/* 3. Send Address */
	I2C_SendAddress(I2Cx,slaveAddr,read);

	/* 4. Wait for ADDR == 1*/
	while(!(I2C_GetFlagStatus(I2Cx,ADDR)));

	/* 5. Receive the data from slave */
	for(int i = dataLen; i>=1; i--){
		//Wait till the data is received
		while(!(I2C_GetFlagStatus(I2Cx,RxNE)));
		p_datain[i] = I2Cx->DR;

		//if the slave sends The penultimate data -> disable Acknowledgement from master
		if(i == 2)
			I2Cx->CR1 &= ~(1<<10);
	}

	/* 6. Send a stop request */
	if(Stop == with_Stop)
		I2C_GenerateSTOP(I2Cx);

	//re-enable ACK
	I2Cx->CR1 |= (1<<10);
}
/* ================================================================
 * @Fn 				- MCAL_I2C_Slave_TX
 * @brief 			- Slave send data to master using interrupt mechanism
 * @param [in] 		- I2Cx : where x can be (1..2 depending on device used) to select I2C peripheral
 * @param [in] 		- TxData : slave data to be sent to master
 * @retval 			- None
 * Note 			- Support interrupt mechanism only
 */
void MCAL_I2C_Slave_TX(I2Cx_REG* I2Cx, uint8_t TxData)
{
	I2Cx->DR = TxData;
}
/* ================================================================
 * @Fn 				- MCAL_I2C_Slave_RX
 * @brief 			- Slave Receive data from master using interrupt mechanism
 * @param [in] 		- I2Cx : where x can be (1..2 depending on device used) to select I2C peripheral
 * @retval 			- Received data
 * Note 			- Support interrupt mechanism only
 *
 */
uint8_t MCAL_I2C_Slave_RX(I2Cx_REG* I2Cx)
{
	return I2Cx->DR;
}




void I2C_GenerateSTART(I2Cx_REG* I2Cx,START_Condition start){

	/* Check the type of start (Start or Repeated Start) */
	if(start != Repeated_START ){
		//Check if the BUS is idle
		while(I2C_GetFlagStatus(I2Cx,BUSY));
	}

	/* Generate a START condition */
	I2Cx->CR1 |= 1<<8;

}

Flag_Status I2C_GetFlagStatus(I2Cx_REG* I2Cx, Flag flag){

	Flag_Status bit_status;
	uint32_t event;

	switch(flag){

	case BUSY:

		bit_status = I2Cx->SR2 & 1<<1 ? SET : RESET;
		break;

	case SB:

		bit_status = I2Cx->SR1 & 1 ? SET : RESET;
		break;

	case ADDR:

		bit_status = I2Cx->SR1 & 1<<1 ? SET : RESET;
		/* In slave mode, it is recommended to perform the complete clearing sequence (READ SR1 then READ SR2) after ADDR is set. */
		I2Cx->SR2;
		break;

	case EV8_1:
		event = I2Cx->SR1 | I2Cx->SR2 << 16;
		/* Check if BUSY ,TRA ,MSL ,TXE flags are all set */
		bit_status = event & EV8_1 ? SET : RESET;
		break;

	case TxE:

		bit_status = I2Cx->SR1 & 1<<7 ? SET : RESET;
		break;

	case BTF:

		bit_status = I2Cx->SR1 & 1<<2 ? SET : RESET;
		break;

	case RxNE:

		bit_status = I2Cx->SR1 & 1<<6 ? SET : RESET;
		break;
	}

	return bit_status;
}

void I2C_SendAddress(I2Cx_REG* I2Cx,uint8_t slaveAddr,Data_Dir R_W){

	if(R_W == write)
		I2Cx->DR = slaveAddr << 1;

	else if(R_W == read)
		I2Cx->DR = slaveAddr << 1 | 1;
}

void I2C_GenerateSTOP(I2Cx_REG* I2Cx){

	I2Cx->CR1 |= 1<<9;
}

/* ================================================================ */
/* ================= IRQ Function Definitions ===================== */
/* ================================================================ */

void I2C1_EV_IRQHandler(){

	// Handler For interrupt generated by STOPF event
	if(I2C1->SR1 & 1<<4){
		// Stop condition detected
		// Cleared by software reading the SR1 register followed by a write in the CR1 register
		I2C1->CR1 |=0;
		g_I2C_Config[0].P_Slave_Event_CallBack(I2C_EV_STOP);
	}

	// Handler For interrupt generated by ADDR even
	else if(I2C1->SR1 & 1<<1){
		// the received slave address matched with the OAR registers content or a general call
		/* In slave mode, it is recommended to perform the complete clearing sequence (READ SR1 then READ SR2) after ADDR is set. */
		I2C1->SR2;
		g_I2C_Config[0].P_Slave_Event_CallBack(I2C_EV_ADD_MATCHED);
	}

	//  Handler For interrupt generated by TxE event
	else if(I2C1->SR1 & 1<<7){
		//(Master request data from slave)--> slave_transmitter
		g_I2C_Config[0].P_Slave_Event_CallBack(I2C_EV_DATA_REQ);
	}

	//  Handler For interrupt generated by RxE event
	else if(I2C1->SR1 & 1<<6){
		//(slave receive data)-->slave_Receiver
		g_I2C_Config[0].P_Slave_Event_CallBack(I2C_EV_DATA_RCV);
	}
}

void I2C1_ER_IRQHandler(){

}

void I2C2_EV_IRQHandler(){

	// Handler For interrupt generated by STOPF event
	if(I2C2->SR1 & 1<<4){
		// Stop condition detected
		// Cleared by software reading the SR1 register followed by a write in the CR1 register
		I2C2->CR1 |=0;
		g_I2C_Config[1].P_Slave_Event_CallBack(I2C_EV_STOP);
	}

	// Handler For interrupt generated by ADDR even
	else if(I2C2->SR1 & 1<<1){
		// the received slave address matched with the OAR registers content or a general call
		/* In slave mode, it is recommended to perform the complete clearing sequence (READ SR1 then READ SR2) after ADDR is set. */
		I2C2->SR2;
		g_I2C_Config[1].P_Slave_Event_CallBack(I2C_EV_ADD_MATCHED);
	}

	//  Handler For interrupt generated by TxE event
	else if(I2C2->SR1 & 1<<7){
		//(Master request data from slave)--> slave_transmitter
		g_I2C_Config[1].P_Slave_Event_CallBack(I2C_EV_DATA_REQ);
	}

	//  Handler For interrupt generated by RxE event
	else if(I2C2->SR1 & 1<<6){
		//(slave receive data)-->slave_Receiver
		g_I2C_Config[1].P_Slave_Event_CallBack(I2C_EV_DATA_RCV);
	}
}

void I2C2_ER_IRQHandler(){

}
