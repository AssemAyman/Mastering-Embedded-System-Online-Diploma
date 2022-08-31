/*
 * US.c
 *
 *  Created on: Aug 30, 2022
 *      Author: 7ARB
 */

#include "US.h"

int US_distance = 0 ;

//STATE Pointer to function
void (*US_state) ();

int US_distance_random(int l,int r,int count){

	int i,rand_num;
	for(i = 0; i<count; i++)
		rand_num = rand() % (r - l + 1) + l;
	return rand_num ;
}
void US_init(){
	puts("US_init");
}

STATE_Define(US_busy){

	//state Action
	US_state_id = US_Busy;

	US_distance = US_distance_random(45,55,1);

	printf("US_Waiting State: distance = %d\n",US_distance);

	US_set_distance(US_distance);
	US_state = STATE(US_busy);
}
