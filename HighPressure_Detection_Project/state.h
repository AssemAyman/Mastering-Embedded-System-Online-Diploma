/*
 * state.h
 *
 *  Created on: Sep 5, 2022
 *      Author: Assem Ayman
 */

#ifndef STATE_H_
#define STATE_H_

#include "driver.h"

#define Define_State(state) void ST_##state ()
#define State(state) ST_##state

//Connections
extern void PressureValue(int pVal);
extern void Start_Alarm();
extern void Stop_Alarm();

#endif /* STATE_H_ */
