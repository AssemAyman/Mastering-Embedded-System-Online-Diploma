/*
 * Pressure_Sensor.c
 *
 *  Created on: Sep 5, 2022
 *      Author: Assem Ayman
 */

#include "Pressure_Sensor.h"

void(*PS_ptr)();
static int pVal;

Define_State(ReadingPressure){
	Pressure_Sensor_State = ReadingPressure;
	pVal = getPressureVal();
	PS_ptr = State(SendPressure);
	Delay(100000);
	PS_ptr();
}

Define_State(SendPressure){
	Pressure_Sensor_State = SendPressure;
	PressureValue(pVal);
	PS_ptr = State(ReadingPressure);
}
