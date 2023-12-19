/*
 * Timer.h
 *
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include "STM32F103C6.h"
#include "RCC.h"

/*=================Timer2======================*/
typedef volatile enum{
	first_entry,
	second_entery
}Entery_t;

void Timer2_init(void);
void Timer3_init(void);
void dus(int us);
void dms(int ms);
vuint32_t Time_Claculation(Entery_t);

#endif /* INC_TIMER_H_ */
