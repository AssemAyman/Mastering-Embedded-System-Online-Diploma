/*
 * High_Pressure_Detection.h
 *
 *  Created on: Sep 5, 2022
 *      Author: 7ARB
 */

#ifndef HIGH_PRESSURE_DETECTION_H_
#define HIGH_PRESSURE_DETECTION_H_

#include "state.h"

//Status OF State Machine
enum{
	Monitor_Pressure
}High_Pressure_Detection_State;

//States Functions of High Pressure Detection
extern Define_State(Monitor_Pressure);

//Pointer to States Functions
extern void (*HPD_ptr)();

#endif /* HIGH_PRESSURE_DETECTION_H_ */
