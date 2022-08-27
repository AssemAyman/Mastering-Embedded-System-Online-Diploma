/*
 ============================================================================
 Name        : ex5.c
 Author      : Assem Ayman
 Version     :
 Copyright   : Your copyright notice
 Description : a pointer to an array which contents are pointer to structure in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>

struct employee{

	char* name;
	int ID;
};

int main(void) {

	struct employee emp[3] = {{"Assem",1001},{"Alex",1002},{"Tarek",1003}};
	struct employee* arr[3] = {&emp[0],&emp[1],&emp[2]};
	struct employee* (*ptr) [3] = &arr;

	printf("Employee Name: %s\n",(*(*ptr+1))->name);
	printf("Employee ID : %d",(*(*ptr+1))->ID);

	return 0;
}
