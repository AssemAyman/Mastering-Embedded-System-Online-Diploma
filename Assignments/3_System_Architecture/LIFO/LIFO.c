/*
 * LIFO.c
 *
 *  Created on: Aug 27, 2022
 *      Author: Assem Ayman
 */

#include "lifo.h"

LIFO_Status_t LIFO_init(LIFO_t* LIFO_ptr,uint32_t* buf,uint32_t length){

	if(buf == NULL)  //in case of dynamic allocation
		return LIFO_Null;

	LIFO_ptr->base = buf;
	LIFO_ptr->head = buf;
	LIFO_ptr->count = 0;
	LIFO_ptr->length = length;

	return LIFO_No_Error;
}

LIFO_Status_t LIFO_push(LIFO_t* LIFO_ptr,uint32_t item){

	if(LIFO_ptr->count == LIFO_ptr->length) //check is lifo full?
		return LIFO_Full;

	//add value
	*(LIFO_ptr->head++) = item;
	LIFO_ptr->count++;

	return LIFO_No_Error;
}

LIFO_Status_t LIFO_pop(LIFO_t* LIFO_ptr,uint32_t* item){

	if(LIFO_ptr-> count == 0) //check is lifo empty?
		return LIFO_Empty;

	LIFO_ptr->head--;
	*item = *(LIFO_ptr->head);
	LIFO_ptr->count--;

	return LIFO_No_Error;
}
