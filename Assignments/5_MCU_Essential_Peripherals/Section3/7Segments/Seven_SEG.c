/*
 * Seven_SEG.c
 *
 *  Created on: Aug 2, 2023
 *      Author: assem
 */

#include "Seven_SEG.h"

void SevenSeg_init(){
	//  Set PB9..PB15 as output PP
	GPIO_PinConfig_t Pincfg;
	uint16_t SEG_pins[7]={GPIO_PIN_9,GPIO_PIN_10,GPIO_PIN_11,GPIO_PIN_12,GPIO_PIN_13,GPIO_PIN_14,GPIO_PIN_15};
	uint8_t i;

	for(i=0; i<7; i++){
		Pincfg.GPIO_PinNumber = SEG_pins[i];
		Pincfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
		Pincfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
		MCAL_GPIOx_Init(GPIOB,&Pincfg);
	}
}
