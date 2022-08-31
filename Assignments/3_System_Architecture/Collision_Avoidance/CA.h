/*
 * CA.h
 *
 *  Created on: Aug 30, 2022
 *      Author: 7ARB
 */

#include "state.h"
#include "stdlib.h"
#include "stdio.h"

#ifndef CA_H_
#define CA_H_

//Define States
enum{
	CA_Waiting,
	CA_Driving
}CA_state_id;

//declare states functions CA

extern STATE_Define(CA_waiting);
extern STATE_Define(CA_driving);

//STATE Pointer to function
extern void (*CA_state) ();

#endif /* CA_H_ */
