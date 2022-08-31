/*
 * DC.h
 *
 *  Created on: Aug 30, 2022
 *      Author: 7ARB
 */

#include "state.h"
#include "stdlib.h"
#include "stdio.h"

#ifndef DC_H_
#define DC_H_

//Define States
enum{
	DC_Idle,
	DC_Busy
}DC_state_id;

void DC_init();

//declare states functions DC

extern STATE_Define(DC_idle);
extern STATE_Define(DC_driving);

//STATE Pointer to function
extern void (*DC_state) ();

#endif /* DC_H_ */
