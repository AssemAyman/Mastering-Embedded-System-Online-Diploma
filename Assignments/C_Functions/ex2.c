/*
 ============================================================================
 Name        : ex2.c
 Author      : Assem Ayman
 Version     :
 Copyright   : Your copyright notice
 Description : Factorial of a number in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>

int fact(int);

int main(void) {

	int n;

	printf("Enter an positive integer: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&n);

	printf("Factorial of %d = %d",n,fact(n));

	return 0;
}

int fact (int num){

	if(num == 1)
		return 1;
	else
		return num*fact(num-1);
}
