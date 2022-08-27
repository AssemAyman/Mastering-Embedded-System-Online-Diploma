/*
 * lifo.h
 *
 *  Created on: Aug 27, 2022
 *      Author: Assem Ayman
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#ifndef lifo_H_
#define lifo_H_

// type definitions

typedef struct {
	uint32_t* base ;
	uint32_t* head ;
	uint32_t  length;
	uint32_t  count;
}LIFO_t;

typedef enum {
	LIFO_No_Error,
	LIFO_Full,
	LIFO_Empty,
	LIFO_Null
}LIFO_Status_t;

//APIs

LIFO_Status_t LIFO_init(LIFO_t*,uint32_t*,uint32_t);
LIFO_Status_t LIFO_push(LIFO_t*,uint32_t);
LIFO_Status_t LIFO_pop(LIFO_t*,uint32_t*);

#endif /* lifo_H_ */
