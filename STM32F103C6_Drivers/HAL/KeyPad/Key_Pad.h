/*
 * Key_Pad.h
 *
 * Created: 7/30/2023 4:51:30 AM
 *  Author: assem
 */

#ifndef KEY_PAD_H_
#define KEY_PAD_H_

#include "GPIO.h"
/*=========Configurations============*/
#define KeyPad_PORT		GPIOB
/*==================================*/
#define R0 GPIO_PIN_0
#define R1 GPIO_PIN_1
#define R2 GPIO_PIN_3
#define R3 GPIO_PIN_4
#define C0 GPIO_PIN_5
#define C1 GPIO_PIN_6
#define C2 GPIO_PIN_7
#define C3 GPIO_PIN_8

extern void KEYPAD_INIT(void);
extern char KEYPAD_GET_KEY(void);

#endif /* KEY_PAD_H_ */

