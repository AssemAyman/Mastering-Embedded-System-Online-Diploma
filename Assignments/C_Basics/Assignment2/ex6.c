/*
 ============================================================================
 Name        : ex6.c
 Author      : Assem Ayman
 Version     :
 Copyright   : Your copyright notice
 Description : sum of natural numbers in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>

int main(void) {

	int x,i,sum=0;
	printf("Enter an integer: ");
	fflush(stdout); fflush(stdin);
	scanf("%d",&x);
	for(i=0; i<=x; i++)
		sum+=i;
	printf("Sum = %d",sum);
	return 0;
}
