/*
 ============================================================================
 Name        : ex4.c
 Author      : Assem Ayman
 Version     :
 Copyright   : Your copyright notice
 Description : Power of a number in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>

int power(int,int);

int main(void) {

	int n,pow;

	printf("Enter base number: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&n);

	printf("Enter power number(positive integer): ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&pow);

	printf("%d^%d = %d",n ,pow ,power(n,pow));
	return 0;
}

int power (int num,int exponent){

	if(exponent == 1)
		return num;
	else
		return num * power(num,exponent-1);
}
