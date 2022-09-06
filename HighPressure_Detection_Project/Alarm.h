/*
 * Alarm.h
 *
 *  Created on: Sep 5, 2022
 *      Author: Assem Ayman
 */

#ifndef ALARM_H_
#define ALARM_H_

#include "state.h"

//Status OF State Machine
enum{
	Alarming,
	Idle
}Alarm_State;

//States Functions of High Pressure Detection
extern Define_State(Alarming);
extern Define_State(Idle);

//Pointer to States Functions
extern void (*Alarm_ptr)();

#endif /* ALARM_H_ */
