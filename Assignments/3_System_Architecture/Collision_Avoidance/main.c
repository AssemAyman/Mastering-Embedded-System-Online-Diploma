/*
 ============================================================================
 Name        : main.c
 Author      : Assem Ayman
 Version     :
 Copyright   : Your copyright notice
 Description : Collision Avoidance in C, Ansi-style
 ============================================================================
 */

#include "CA.h"
#include "US.h"
#include "DC.h"

int main(void) {

	US_init();
	DC_init();

	CA_state = STATE(CA_waiting);
	US_state = STATE(US_busy);
	DC_state = STATE(DC_idle);

	volatile  int d;

	while(1){
		US_state();
		CA_state();
		DC_state();
		//delay
		for(d = 0; d<1000; d++);
	}

	return 0;
}
