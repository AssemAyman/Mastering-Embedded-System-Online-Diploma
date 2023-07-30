/*
 * Key_Pad.h
 *
 * Created: 7/30/2023 4:51:30 AM
 *  Author: assem
 */ 

#ifndef KEY_PAD_H_
#define KEY_PAD_H_

#define F_CPU 1000000UL

#include "avr/io.h"
#include "util/delay.h"

#define R0 0
#define R1 1
#define R2 2
#define R3 3
#define C0 4
#define C1 5
#define C2 6
#define C3 7

#define KEYPAD_PORT PORTD
#define KEYPAD_PIN PIND
#define KEYPAD_DIR DDRD

void KEYPAD_INIT(void);
char KEYPAD_GET_KEY(void);

#endif /* KEY_PAD_H_ */