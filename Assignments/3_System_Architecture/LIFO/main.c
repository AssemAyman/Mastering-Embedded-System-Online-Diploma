/*
 * main.c
 *
 *  Created on: Aug 27, 2022
 *      Author: Assem Ayman
 */

#include "lifo.h"

uint32_t buffer[5];

int main(void) {

	uint32_t i,item;
	LIFO_t UART_buffer;
	LIFO_Status_t status;

	status = LIFO_init(&UART_buffer, buffer, 5);

	if(status == LIFO_No_Error){
		//push elements
		for(i = 0; i<5; i++){
			status = LIFO_push(&UART_buffer, i);

			switch(status){

			       case LIFO_No_Error:
				    printf("Pushing: %d\n",i);
				    break;

			       case LIFO_Full:
				    puts("LIFO is Full");
				    break;
			}
		}
		printf("\n");
		//pop elements
		for(i = 0; i<5; i++){
			status = LIFO_pop(&UART_buffer,&item);
			
			switch(status){
					
			      case LIFO_No_Error:
				   printf("Popping: %d\n",item);
				   break;
					
			     case LIFO_Empty:
				  puts("LIFO is Empty");
				  break;
			}
		}
	}else
		printf("Null Buffer"); //in case of dynamic allocation

	return 0;
}
