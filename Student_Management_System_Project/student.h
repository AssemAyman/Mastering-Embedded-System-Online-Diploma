/*
 * student.h
 *
 *  Created on: Sep 7, 2022
 *      Author: Assem Ayman
 */

#ifndef STUDENT_H_
#define STUDENT_H_

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define flush fflush(stdin); fflush(stdout)

//Students Info
typedef struct {
	char firstname[15];
	char lastname[15];
	uint32_t ID;
	float GPA;
	uint32_t CourseID[5];
}Data;

//buffer
Data st[50];

//FIFO
typedef struct{
	Data* base ;
	Data* head ;
	Data* tail ;
	uint32_t length;
	uint32_t count;
}FIFO_t;

FIFO_t fifo;

//FIFO status
typedef enum{
	FIFO_NO_Error,
	FIFO_Error,
	FIFO_Full,
	FIFO_Empty
}FIFO_Status_t;

//APIs
extern FIFO_Status_t add_student_manually();
extern FIFO_Status_t add_student_file();
extern FIFO_Status_t find_ID();
extern FIFO_Status_t find_firstname();
extern FIFO_Status_t find_course();
extern FIFO_Status_t count();
extern FIFO_Status_t delete_student();
extern FIFO_Status_t update_student();
extern FIFO_Status_t show_all();

#endif /* STUDENT_H_ */
