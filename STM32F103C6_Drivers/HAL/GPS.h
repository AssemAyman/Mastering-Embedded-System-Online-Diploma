/*
 * GPS.h
 *
 *  Created on: Oct 18, 2024
 *      Author: assem
 */

#ifndef GPS_H_
#define GPS_H_

#include "USART.h"
#include <string.h>

#define USARTx 			USART1

uint8_t location_data[40],done;

extern void GPS_Init();
extern void Get_Location(float*, float*);

#endif /* GPS_H_ */
