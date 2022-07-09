/*
 ============================================================================
 Name        : ex3.c
 Author      : Assem Ayman
 Version     :
 Copyright   : Your copyright notice
 Description : largest of 3 numbers in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>

int main(void) {

	float x,y,z;
	printf("Enter three numbers: ");
	fflush(stdin); fflush(stdout);
	scanf("%f %f %f",&x,&y,&z);
	if(x>y && x>z)
		printf("Largest number = %f",x);
	else if(y>z)
		printf("Largest number = %f",y);
	else
		printf("Largest number = %f",z);
	return 0;
}
