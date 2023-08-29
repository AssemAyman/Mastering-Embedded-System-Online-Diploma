/*
 * EEPROM.c
 *
 *  Created on: Aug 29, 2023
 *      Author: assem
 */

#include "EEPROM.h"

void HAL_EEPROM_Init(I2Cx_REG* I2CX){

	//Initialize I2Cx controller to act as a master

	I2C_Config_t I2C_cfg;

	I2C_cfg.Clock_Speed = I2C_SCLK_SM_100K;
	I2C_cfg.Stretch_Mode = I2C_StretchMode_Enable;
	I2C_cfg.P_Slave_Event_CallBack = NULL;

	MCAL_I2C_Init(I2CX, &I2C_cfg);
	MCAL_I2C_GPIO_Set_Pins(I2CX);

}

void HAL_EEPROM_Send(I2Cx_REG* I2CX, uint8_t* p_dataOut,uint16_t dataLen,uint16_t Mem_Add){

	// I2Cx master receive data from EEPROM

	uint8_t buffer[2];

	buffer[0] = Mem_Add >> 8;  //Higher_Mem_Add
	buffer[1] = Mem_Add ;	    //Lower_Mem_Add

	//Write Address only
	MCAL_I2C_Master_TX(I2CX, EEPROM_Slave_Address, buffer, 2, without_Stop, START);

	MCAL_I2C_Master_RX(I2CX, EEPROM_Slave_Address, p_dataOut, dataLen, with_Stop, Repeated_START);
}

void HAL_EEPROM_Receive(I2Cx_REG* I2CX, uint8_t* p_datain,uint16_t dataLen,uint16_t Mem_Add){

	// I2Cx master transmit data to EEPROM

	uint8_t buffer[dataLen + 2] ;

	buffer[0] = Mem_Add >> 8;  //Higher_Mem_Add
	buffer[1] = Mem_Add ;		//Higher_Mem_Add

	for(int i = 2; i<dataLen+2; i++)
		buffer[i] = p_datain[i-2];

	MCAL_I2C_Master_TX(I2CX, EEPROM_Slave_Address, buffer, dataLen + 2, with_Stop, START);

}
