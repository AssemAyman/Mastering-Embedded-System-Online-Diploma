/*
 * US.h
 *
 *  Created on: Aug 30, 2022
 *      Author: 7ARB
 */

#include "state.h"
#include "stdlib.h"
#include "stdio.h"

#ifndef US_H_
#define US_H_

//Define States
enum{
	US_Busy
}US_state_id;

void US_init();

//declare states functions US
extern STATE_Define(US_busy);

//STATE Pointer to function
extern void (*US_state) ();

#endif /* US_H_ */
