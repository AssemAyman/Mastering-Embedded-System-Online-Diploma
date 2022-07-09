/*
 ============================================================================
 Name        : ex4.c
 Author      : Assem Ayman
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>

int main(void) {

	float x,y;
	printf("Enter two numbers: ");
	fflush(stdout); fflush(stdin);
	scanf("%f %f",&x,&y);
	printf("Product: %f",x*y);
	return 0;
}
