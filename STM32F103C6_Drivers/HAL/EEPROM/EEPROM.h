/*
 * EEPROM.h
 *
 *  Created on: Aug 29, 2023
 *      Author: assem
 */

#ifndef EEPROM_H_
#define EEPROM_H_

#include "I2C.h"

#define EEPROM_Slave_Address 		0x2A

			/* ================== APIs ===================== */
extern void HAL_EEPROM_Init(I2Cx_REG* I2CX);
extern void HAL_EEPROM_Send(I2Cx_REG* I2CX, uint8_t* p_dataOut,uint16_t dataLen,uint16_t Mem_Add);
extern void HAL_EEPROM_Receive(I2Cx_REG* I2CX, uint8_t* p_datain,uint16_t dataLen,uint16_t Mem_Add);

#endif /* EEPROM_H_ */
