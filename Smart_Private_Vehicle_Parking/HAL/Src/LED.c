/*
 * LED.c
 *
 *  Created on: Oct 4, 2023
 *      Author: assem
 */

#include "LED.h"

void LED_init(){

	GPIO_PinConfig_t gpio_cfg;

	gpio_cfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	gpio_cfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	gpio_cfg.GPIO_PinNumber = GPIO_PIN_0;

	/*Initialize RED LED*/
	MCAL_GPIOx_Init(GPIOA, &gpio_cfg);
	MCAL_GPIOx_WritePin(GPIOA, GPIO_PIN_0,GPIO_PIN_SET);

	gpio_cfg.GPIO_PinNumber = GPIO_PIN_11;

	/*Initialize Green LED*/
	MCAL_GPIOx_Init(GPIOA, &gpio_cfg);
	MCAL_GPIOx_WritePin(GPIOA, GPIO_PIN_11,GPIO_PIN_SET);

}

void RED_LED_ON(){

	for(int i = 0; i<3; i++){

		MCAL_GPIOx_WritePin(GPIOA, GPIO_PIN_0,GPIO_PIN_RESET);
		dms(100);
		MCAL_GPIOx_WritePin(GPIOA, GPIO_PIN_0,GPIO_PIN_SET);
		dms(100);

	}
}

void Green_LED_ON(){

	for(int i = 0; i<3; i++){

		MCAL_GPIOx_WritePin(GPIOA, GPIO_PIN_11,GPIO_PIN_RESET);
		dms(100);
		MCAL_GPIOx_WritePin(GPIOA, GPIO_PIN_11,GPIO_PIN_SET);
		dms(100);

	}
}
