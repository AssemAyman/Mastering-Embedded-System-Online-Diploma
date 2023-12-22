/*========INCLUDES========*/
#include "USART.h"
#include "GPIO.h"
#include "Timer.h"
#include "EXTI.h"
#include "RCC.h"
#include <stdio.h>
/*======================*/

void Echo();

/*==========Genaric variables===========*/
vuint32_t distance;
uint16_t data;
vuint8_t moving_Forward = 0;;
char text[8];
/*=====================================*/

void Forward(){

	MCAL_GPIOx_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
	MCAL_GPIOx_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
	MCAL_GPIOx_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
	MCAL_GPIOx_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
	moving_Forward = 1;
}

void Backward(){

	MCAL_GPIOx_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);
	MCAL_GPIOx_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
	MCAL_GPIOx_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
	MCAL_GPIOx_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
	moving_Forward = 0;
}

void Left(){

	MCAL_GPIOx_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
	MCAL_GPIOx_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
	MCAL_GPIOx_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
	MCAL_GPIOx_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
	moving_Forward = 0;
}

void Right(){

	MCAL_GPIOx_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);
	MCAL_GPIOx_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
	MCAL_GPIOx_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
	MCAL_GPIOx_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
	moving_Forward = 0;
}

void Back_Left(){

	MCAL_GPIOx_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
	MCAL_GPIOx_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
	MCAL_GPIOx_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
	MCAL_GPIOx_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
	moving_Forward = 0;
}

void Back_Right(){

	MCAL_GPIOx_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
	MCAL_GPIOx_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
	MCAL_GPIOx_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
	MCAL_GPIOx_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
	moving_Forward = 0;
}

void Stop(){

	MCAL_GPIOx_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
	MCAL_GPIOx_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
	MCAL_GPIOx_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
	MCAL_GPIOx_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
	moving_Forward = 0;
}

void Horn(){

	MCAL_GPIOx_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
	dms(500);
	MCAL_GPIOx_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
}

void move(){
	switch(data){

	case 'w':
		if(distance >30) Forward();
		break;

	case 's':
		Backward();
		break;

	case 'a':
		Left();
		break;

	case 'd':
		Right();
		break;

	case 'e':
		Back_Right();
		break;

	case 'q':
		Back_Left();
		break;

	case 'x':
		Stop();
		break;

	case 'h':
		Horn();
		break;
	}
}

void Receive(){
	//if the interrupt occurs to receive another byte
		MCAL_USART_ReceiveData(USART1, &data, disable);
		move();
}

int main(void) {

	GPIOx_CLK_EN('A');
	Timer2_init();
	Timer3_init();

	USART_Config_t usart_cfg;

	usart_cfg.BaudRate = USART_BaudRate_9600;
	usart_cfg.HwFlowCtl = USART_HwFlowCtl_NONE;
	usart_cfg.IRQ_Enable = USART_IRQ_Enable_RXNE;
	usart_cfg.P_IRQ_CallBack = Receive;
	usart_cfg.Parity = USART_Parity_NONE;
	usart_cfg.Payload_Length = USART_Payload_Length_8B;
	usart_cfg.StopBits = USART_StopBits_1;
	usart_cfg.USART_Mode = USART_Mode_Tx_Rx;

	MCAL_USART_Init(USART1, &usart_cfg);
	MCAL_UASRT_GPIO_Set_Pins(USART1);

	uint16_t PIN[6] = {GPIO_PIN_0,GPIO_PIN_2,GPIO_PIN_3,GPIO_PIN_4,GPIO_PIN_5,GPIO_PIN_6};
	GPIO_PinConfig_t gpio_cfg;

	gpio_cfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	gpio_cfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_2M;

	for(int i = 0; i<6; i++){

		gpio_cfg.GPIO_PinNumber = PIN[i];
		MCAL_GPIOx_Init(GPIOA, &gpio_cfg);

	}

	//Make A1(Echo pin) an external interrupt pin in both rising and falling
	EXTI_PinConfig_t pincfg;

	pincfg.EXTI_PIN = EXTI1PA1;
	pincfg.Trigger_Case = EXTI_Trigger_RisingAndFalling;
	pincfg.IRQ_EN = EXTI_IRQ_Enable;
	pincfg.P_IRQ_CallBack = Echo;

	MCAL_EXTI_GPIO_Init(&pincfg);

	while(1){
		//Send a trigger pulse to the ultrasonic
		MCAL_GPIOx_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
		dms(30);
		MCAL_GPIOx_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
		dms(1);

	}

}


Entery_t entery_index = first_entry;

void Echo(){

	if(entery_index == first_entry){
		entery_index = second_entery;
		Time_Claculation(first_entry);
	}else{
		entery_index = first_entry;
		distance = (170 * Time_Claculation(second_entery)) / 10000;
		if(distance <=30 && moving_Forward == 1) Stop();
		sprintf(text,"%lucm\n",distance);
		//Send the distance to the Bluetooth module
		MCAL_USART_SendData(USART1, (uint16_t*)&text[0], enable);
		MCAL_USART_SendData(USART1, (uint16_t*)&text[1], enable);
		MCAL_USART_SendData(USART1, (uint16_t*)&text[2], enable);
		MCAL_USART_SendData(USART1, (uint16_t*)&text[3], enable);
		MCAL_USART_SendData(USART1, (uint16_t*)&text[4], enable);
		MCAL_USART_SendData(USART1, (uint16_t*)&text[5], enable);
		MCAL_USART_SendData(USART1, (uint16_t*)&text[6], enable);
	}
}
