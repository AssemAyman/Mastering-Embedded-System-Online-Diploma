/*
 * SPI.h
 *
 *  Created on: Aug 19, 2023
 *      Author: assem
 */

#ifndef SPI_H_
#define SPI_H_
/* ================================================================ */
/* =========================== Includes =========================== */
/* ================================================================ */
#include "STM32F103C6.h"
#include "GPIO.h"
/* ================================================================ */
/* =================== Configuration Structure ==================== */
/* ================================================================ */
typedef struct{
	uint8_t TXE:1;		//Tx buffer empty interrupt
	uint8_t RXNE:1;		//RX buffer not empty interrupt
	uint8_t ERRI:1;		//Error interrupt
	uint8_t	Reserved:5;
}S_IRQ_SRC_t;

typedef struct{
	uint16_t	SPI_Mode;			    // specifies SPI MODE Master/Slave
										// This parameter must be set based on @ref SPI_MODE_define

	uint16_t	Communication_Mode;		//Specifies The spi communication mode
										// This parameter must be set based on @ref SPI_Communication_Mode_define

	uint16_t    Frame_Format;			//Specifies LSB or MSB to be transmitted first
										//This parameter must be set based on @ref SPT_Frame_Format_define

	uint16_t  	DataSize;				// Specifies Data frame size 8-bit or 16_bit
										// This parameter must be set based on @ref SPI_DataSize_define

	uint16_t	CLK_Polarity;			// Specifies SPI clock Polarity idle on low or idle on high
										// This parameter must be set based on @ref SPI_CLK_POLARITY_define

	uint16_t	CLK_Phase;				//Specifies SPI clock Phase,first clock capture or second clock capture
										// This parameter must be set based on @ref SPI_CLK_PHASE_define

	uint16_t 	NSS;					// specifies slave select management by hardware or by software
										// This parameter must be set based on @ref SPI_NSS_define

	uint16_t    BaudRate_Prescaler;		/*Specifies the baud rate prescaler value which will be used to configure the transmit and receive SCK
										@note The SCK is derived from the master so the slave clk doesn't need to be set*/
										// This parameter must be set based on @ref SPI_BAUDERATE_PRESCALER_define

	uint16_t	IRQ_Enable;				//Enable or disable SPI IRQ
										//This parameters must be set based on @ref SPI_IRQ_Enable_define

	void(*P_IRQ_CallBack)(S_IRQ_SRC_t irq_src);	//Set the C function which will be called once the IRQ happens

}SPI_Config_t;
/* ================================================================ */
/* =============== Configuration References Macros ================ */
/* ================================================================ */
//@ref SPI_MODE_define
#define SPI_MODE_Master	1<<2
#define SPI_MODE_Slave	0

//@ref SPI_Communication_Mode_define
#define SPI_Communication_Mode_2LINE_FULL_DUPLEX	0
#define SPI_Communication_Mode_2LINE_RXE_ONLY		1<<10
#define SPI_Communication_Mode_1LINE_TX_ONLY		(1<<15 | 1<<14)
#define SPI_Communication_Mode_1LINE_RX_ONLY		1<<15

//@ref SPT_Frame_Format_define
#define SPI_Frame_Format_MSB_First	0
#define SPI_Frame_Format_LSB_First	1<<7

//@ref SPI_DataSize_define
#define SPI_DataSize_8bit	0
#define SPI_DataSize_16bit	1<<11

//@ref SPI_CLK_POLARITY_define
#define SPI_CLK_POLARITY_IDLE_LOW	0
#define SPI_CLK_POLARITY_IDLE_HIGH	1<<1

//@ref SPI_CLK_PHASE_define
#define SPI_CLK_PHASE_FirstEdge_Capture		0
#define SPI_CLK_PHASE_SecondEdge_Capture	1

//@ref SPI_NSS_define
//Hardware
#define SPI_NSS_HW_Slave				0
#define SPI_NSS_HW_Master_OutPut		1<<2
#define SPI_NSS_HW_Master_Input			0
//Software
#define SPI_NSS_SW_Slave	1<<9
#define SPI_NSS_SW_Master	(1<<9 | 1<<8)

//@ref SPI_BAUDERATE_PRESCALER_define
#define SPI_BAUDERATE_PRESCALER_2 		0
#define SPI_BAUDERATE_PRESCALER_4		1<<3
#define SPI_BAUDERATE_PRESCALER_8		2<<3
#define SPI_BAUDERATE_PRESCALER_16 		3<<3
#define SPI_BAUDERATE_PRESCALER_32 		4<<3
#define SPI_BAUDERATE_PRESCALER_64 		5<<3
#define SPI_BAUDERATE_PRESCALER_128 	6<<3
#define SPI_BAUDERATE_PRESCALER_256 	7<<3

//@ref SPI_IRQ_Enable_define
#define SPI_IRQ_Enable_None			0
#define SPI_IRQ_Enable_TXEIE		1<<7
#define SPI_IRQ_Enable_RXNEIE		1<<6
#define SPI_IRQ_Enable_ERRIE		1<<5

typedef enum{
	Disable,
	Enable
}PollingMechanism;
/* ================================================================ */
/* =========== APIs Supported by "MCAL SPI DRIVER" ================ */
/* ================================================================ */
extern void MCAL_SPI_Init(SPIx_REG* SPIx,SPI_Config_t* SPI_Config);
extern void MCAL_SPI_DeInit(SPIx_REG* SPIx);
extern void MCAL_SPI_GPIO_Set_Pins(SPIx_REG* SPIx);
extern void MCAL_SPI_SendData(SPIx_REG* SPIx,uint16_t* p_Txbuffer,PollingMechanism Polling);
extern void MCAL_SPI_ReceiveData(SPIx_REG* SPIx,uint16_t* p_Rxbuffer,PollingMechanism Polling);
extern void MCAL_SPI_TX_RX(SPIx_REG* SPIx,uint16_t* p_buffer,PollingMechanism Polling);

#endif /* SPI_H_ */
