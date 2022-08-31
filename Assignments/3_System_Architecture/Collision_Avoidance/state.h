/*
 * state.h
 *
 *  Created on: Aug 30, 2022
 *      Author: 7ARB
 */

#ifndef STATE_H_
#define STATE_H_

//Automatic STATE Function generated

#define STATE_Define(_statFUN_) void ST_##_statFUN_ ()
#define STATE(_statFUN_) ST_##_statFUN_

void US_set_distance(int distance);
void DC_motor(int speed);

#endif /* STATE_H_ */
