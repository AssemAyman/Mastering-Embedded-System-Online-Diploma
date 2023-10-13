/*
 * Seven_SEG.h
 *
 *  Created on: Aug 2, 2023
 *      Author: assem
 */

#ifndef SEVEN_SEG_H_
#define SEVEN_SEG_H_

#include "GPIO.h"

/* ========= Configurations ========*/
#define Seven_SEG_Port	GPIOB

#define a 				GPIO_PIN_9
#define b				GPIO_PIN_10
#define c				GPIO_PIN_11
#define d  				GPIO_PIN_12
#define e 				GPIO_PIN_13
#define f				GPIO_PIN_14
#define g				GPIO_PIN_15
/* =================================*/

#define ZERO 0x01
#define ONE 0x79
#define TWO 0x24
#define THREE 0x30
#define FOUR 0x58
#define FIVE 0x12
#define SIX 0x02
#define SEVEN 0x19
#define EIGHT 0x00
#define NINE 0x10

extern void SevenSeg_init();

#endif /* SEVEN_SEG_H_ */
