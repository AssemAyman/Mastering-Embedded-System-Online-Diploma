/*
 ============================================================================
 Name        : ex7.c
 Author      : Assem Ayman
 Version     :
 Copyright   : Your copyright notice
 Description : Factorial in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>

int main(void) {

	int x,i,fact=1;
	printf("Enter an integer: ");
	fflush(stdout); fflush(stdin);
	scanf("%d",&x);
	if(x<0)
		printf("Error! Factorial of negative number doesn't exist.");
	else if(x==0)
		printf("Factorial = 1");
	else
		for(i=1;i<=x;i++)
			fact *= i;
    printf("Factorial = %d",fact);
	return 0;
}
