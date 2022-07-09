/*
 ============================================================================
 Name        : ex4.c
 Author      : Assem Ayman
 Version     :
 Copyright   : Your copyright notice
 Description : positive or negative in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>

int main(void) {

	float x;
	printf("Enter a number: ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&x);
	if(x>0)
		printf("%0.2f is positive",x);
	else if(x<0)
		printf("%0.2f is negative",x);
	else
		printf("You entered Zero");
	return 0;
}
