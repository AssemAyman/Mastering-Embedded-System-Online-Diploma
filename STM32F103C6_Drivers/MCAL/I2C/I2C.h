/*
 * I2C.h
 *
 *  Created on: Aug 26, 2023
 *      Author: assem
 */

#ifndef I2C_H_
#define I2C_H_

/* ================================================================ */
/* =========================== Includes =========================== */
/* ================================================================ */
#include "STM32F103C6.h"
#include "GPIO.h"
#include "RCC.h"
/* ================================================================ */
/* =================== Configuration Structure ==================== */
/* ================================================================ */
typedef enum{

	I2C_EV_STOP,
	I2C_EV_ADD_MATCHED,
	I2C_EV_DATA_REQ,							// APP_Layer should send data (MCAL_I2C_Slave_TX)
	I2C_EV_DATA_RCV								// APP_Layer should receive data (MCAL_I2C_Slave_RX)

}Slave_State;

typedef enum{

	with_Stop,
	without_Stop

}Stop_Condition;

typedef enum
{
	START,
	Repeated_START

}START_Condition;

typedef enum
{
	RESET,
	SET

}Flag_Status;

typedef enum{

	BUSY,
	SB,
	ADDR,
	TxE,
	BTF,
	RxNE,
	EV8_1 = 0x00070080

}Flag;


typedef enum{
	write,
	read
}Data_Dir;

typedef struct{

	uint8_t  Dual_ADD;					//1-Enable 0-Disable
	uint8_t Primary_Slave_address;		//7-bit mode only
	uint8_t Secondary_Slave_address;	//7-bit mode only

}I2C_Slave_address_t;

typedef struct{

	uint32_t 				Clock_Speed;				// Specifies I2C clock speed
														// This parameter must be set based on @ref I2C_CLOCK_SPEED_DEFINE

	uint8_t					Stretch_Mode;				// specifies Enable or Disable clock stretching in slave mode only
														// This parameter must be set based on @ref I2C_STRETCH_MODE_DEFINE

	I2C_Slave_address_t		Slave_Address;

	uint8_t					General_Call;				// specifies Enable or Disable General_Call
														// This parameter must be set based on @ref I2C_GENERAL_CALL_DEFINE

	void(*P_Slave_Event_CallBack)(Slave_State); 		// Set the C Function which will be called once IRQ Happens

}I2C_Config_t;

/* ================================================================ */
/* =============== Configuration References Macros ================ */
/* ================================================================ */
//@ref I2C_CLOCK_SPEED_DEFINE
#define I2C_SCLK_SM_50K			50000U
#define I2C_SCLK_SM_100K		100000U

//@ref I2C_STRETCH_MODE_DEFINE
#define I2C_StretchMode_Enable		0
#define I2C_StretchMode_Disable		1<<7

//@ref I2C_GENERAL_CALL_DEFINE
#define I2C_GENERAL_CALL_Enable			1<<6
#define I2C_GENERAL_CALL_Disable		0
/* ================================================================ */
/* =========== APIs Supported by "MCAL I2C DRIVER" ================ */
/* ================================================================ */
extern void MCAL_I2C_Init(I2Cx_REG* I2Cx,I2C_Config_t* I2C_Config);
extern void MCAL_I2C_DeInit(I2Cx_REG* I2Cx);
extern void MCAL_I2C_GPIO_Set_Pins(I2Cx_REG* I2Cx);
extern void MCAL_I2C_Master_TX(I2Cx_REG* I2Cx,uint8_t slaveAddr,uint8_t* p_dataOut,uint16_t dataLen,Stop_Condition Stop,START_Condition start);
extern void MCAL_I2C_Master_RX(I2Cx_REG* I2Cx,uint8_t slaveAddr,uint8_t* p_datain,uint16_t dataLen,Stop_Condition Stop,START_Condition start);
extern void MCAL_I2C_Slave_TX(I2Cx_REG* I2Cx, uint8_t TxData);
extern uint8_t MCAL_I2C_Slave_RX(I2Cx_REG* I2Cx);
/* ================================================================ */
/* ====================== Private APIs ============================ */
/* ================================================================ */
void I2C_GenerateSTART(I2Cx_REG* I2Cx,START_Condition start);
Flag_Status I2C_GetFlagStatus(I2Cx_REG* I2Cx, Flag flag);
void I2C_SendAddress(I2Cx_REG* I2Cx,uint8_t slaveAddr,Data_Dir R_W);
void I2C_GenerateSTOP(I2Cx_REG* I2Cx);

#endif /* I2C_H_ */
