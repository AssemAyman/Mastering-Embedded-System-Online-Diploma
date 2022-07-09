/*
 ============================================================================
 Name        : ex2.c
 Author      : Assem Ayman
 Version     :
 Copyright   : Your copyright notice
 Description : print an integer in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>

int main(void) {
	int x;

	printf("Enter a integer: ");
	fflush(stdout); fflush(stdin);
	scanf("%d",&x);
	printf("You entered: %d",x);

	return 0;
}
