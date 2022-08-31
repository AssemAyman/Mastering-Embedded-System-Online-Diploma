/*
 * CA.c
 *
 *  Created on: Aug 30, 2022
 *      Author: 7ARB
 */

#include "CA.h"

int CA_speed = 0, CA_distance = 0, CA_threshold = 50 ;

//STATE Pointer to function
void (*CA_state) ();

void US_set_distance(int distance){
	CA_distance = distance;
	CA_state = (CA_distance <= CA_threshold)? STATE(CA_waiting) : STATE(CA_driving) ;
	printf("US-----distance = %d-----> CA\n",CA_distance);
}

STATE_Define(CA_waiting){

	//state Name
	CA_state_id = CA_Waiting;
	printf("CA_Waiting State: distance = %d \t speed = %d\n",CA_distance,CA_speed);

	//state Action
	CA_speed = 0;
	DC_motor(CA_speed);
}

STATE_Define(CA_driving){

	//state Name
	CA_state_id = CA_Driving;
	printf("CA_Driving State: distance = %d \t speed = %d\n",CA_distance,CA_speed);

	//state Action
	CA_speed = 30;
	DC_motor(CA_speed);

}
