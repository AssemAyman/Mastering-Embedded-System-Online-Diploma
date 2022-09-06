/*
 * High_Pressure_Detection.c
 *
 *  Created on: Sep 5, 2022
 *      Author: Assem Ayman
 */

#include "High_Pressure_Detection.h"

void (*HPD_ptr)();
static int bar,threshold = 20;

void PressureValue(int pVal){
	bar = pVal;
	HPD_ptr = State(Monitor_Pressure);
}

Define_State(Monitor_Pressure){
	if(bar > threshold)
		Start_Alarm();
	else
		Stop_Alarm();
}
