/*
 * main.c
 *
 *  Created on: Sep 5, 2022
 *      Author: Assem Ayman
 */

#include "Pressure_Sensor.h"
#include "High_Pressure_Detection.h"
#include "Alarm.h"

int main (){

	//Setup
	GPIO_INITIALIZATION();
	PS_ptr = State(ReadingPressure);
	HPD_ptr = State(Monitor_Pressure);
	Alarm_ptr = State(Idle);

	while (1)
	{
		PS_ptr();
		HPD_ptr();
		Alarm_ptr();
	}
	return 0;
}
