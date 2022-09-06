/*
 * Pressure_Sensor.h
 *
 *  Created on: Sep 5, 2022
 *      Author: Assem Ayman
 */

#ifndef PRESSURE_SENSOR_H_
#define PRESSURE_SENSOR_H_

#include "state.h"

//Status OF State Machine
enum{
	ReadingPressure,
	SendPressure
}Pressure_Sensor_State;

//States Functions of Pressure Sensor
extern Define_State(ReadingPressure);
extern Define_State(SendPressure);

//Pointer to States Functions
extern void(*PS_ptr)();

#endif /* PRESSURE_SENSOR_H_ */
