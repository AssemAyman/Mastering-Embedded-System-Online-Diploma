/*
 ============================================================================
 Name        : ex5.c
 Author      : Assem Ayman
 Version     :
 Copyright   : Your copyright notice
 Description : area of a circle using macros in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>

#define area(r) 3.14*r*r

int main(void) {

	float r;

	printf("Enter the radius: ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&r);

	printf("Area = %0.2f",area(r));

	return 0;
}
