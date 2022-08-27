/*
 ============================================================================
 Name        : ex1.c
 Author      : Assem Ayman
 Version     :
 Copyright   : Your copyright notice
 Description : even or odd in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>


int main(void) {

	int x;
	printf("Enter an integer you want to check: ");
	fflush(stdout); fflush(stdin);
	scanf("%d",&x);
	x%2 == 0? printf("%d is even",x) : printf("%d is odd",x);
	return 0;
}
