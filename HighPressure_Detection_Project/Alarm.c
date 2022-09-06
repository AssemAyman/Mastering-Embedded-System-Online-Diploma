/*
 * Alarm.c
 *
 *  Created on: Sep 5, 2022
 *      Author: 7ARB
 */

#include "Alarm.h"

void (*Alarm_ptr)();

void Start_Alarm(){
	Alarm_ptr = State(Alarming);
}

void Stop_Alarm(){
	Alarm_ptr = State(Idle);
}

Define_State(Alarming){
	Alarm_State = Alarming;
	//Turn ON Alarm
	Set_Alarm_actuator(0);
	Delay(6000000);
	Alarm_ptr = State(Idle);
	Alarm_ptr();
}

Define_State(Idle){
	Alarm_State = Idle;
	//Turn OFF Alarm
	Set_Alarm_actuator(1);
}
