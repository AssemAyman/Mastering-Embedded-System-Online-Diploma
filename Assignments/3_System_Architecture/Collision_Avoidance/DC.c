/*
 * DC.c
 *
 *  Created on: Aug 30, 2022
 *      Author: 7ARB
 */

#include "DC.h"

int DC_speed = 0 ;

//STATE Pointer to function
void (*DC_state) ();

void DC_init(){
	puts("DC_init");
}

STATE_Define(DC_idle){

	//state Name
	DC_state_id = DC_Idle;

	//state Action
	DC_state = STATE(DC_idle) ;

	printf("DC_idle State: speed = %d\n",DC_speed);
}

STATE_Define(DC_busy){

	//state Name
	DC_state_id = DC_Busy;

	//state Action
	DC_state = STATE(DC_idle);

	printf("DC_busy State: speed = %d\n",DC_speed);
}

void DC_motor(int speed){
	DC_speed = speed;
	DC_state = STATE(DC_busy);
	printf("CA speed = %d -> DC\n",DC_speed);
}
