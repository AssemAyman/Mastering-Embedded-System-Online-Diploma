/*
 * fifo.h
 *
 *  Created on: Aug 27, 2022
 *      Author: Assem Ayman
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#ifndef FIFO_H_
#define FIFO_H_

//user configuration
#define Element_Type uint8_t
#define size 5

//type definitions
typedef struct{
	Element_Type* base;
	Element_Type* head;
	Element_Type* tail;
	uint32_t length;
	uint32_t count;
}FIFO_t;

typedef enum{
	FIFO_NO_Error,
	FIFO_Full,
	FIFO_Null,
	FIFO_Empty
}FIFO_Status_t;

//APIs
FIFO_Status_t FIFO_init(FIFO_t*,Element_Type*,uint32_t);
FIFO_Status_t FIFO_enqueue(FIFO_t*,Element_Type);
FIFO_Status_t FIFO_dequeue(FIFO_t*,Element_Type*);

#endif /* FIFO_H_ */
