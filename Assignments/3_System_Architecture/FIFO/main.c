/*
 * main.c
 *
 *  Created on: Aug 27, 2022
 *      Author: Assem Ayman
 */

#include "fifo.h"

Element_Type buffer[size];

int main(void) {

	FIFO_t UART_Buffer;
	Element_Type temp,i;
	FIFO_Status_t status;
	status = FIFO_init(&UART_Buffer,buffer,5);

	if(status == FIFO_NO_Error){
		//enqueue elements
		for(i=0; i<5; i++){
			status = FIFO_enqueue(&UART_Buffer,i);

			switch(status){
			case FIFO_NO_Error:
				printf("Enqueuing: %d\n",i);
				break;

			case FIFO_Full:
				puts("FIFO is Full");
				break;
			}
		}

		printf("\n");
		//dequeue elements
		for(i=0; i<5; i++){
			status = FIFO_dequeue(&UART_Buffer,&temp);

			switch(status){
			case FIFO_NO_Error:
				printf("Dequeuing: %d\n",temp);
				break;

			case FIFO_Empty:
				puts("FIFO is Empty");
				break;
			}
		}
	}else //in case of failed dynamic allocation
		puts("NULL Buffer");

	return 0;
}
