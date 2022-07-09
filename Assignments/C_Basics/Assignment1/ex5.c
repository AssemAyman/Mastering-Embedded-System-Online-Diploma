/*
 ============================================================================
 Name        : ex5.c
 Author      : Assem Ayman
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>

int main(void) {

	char x;
	printf("Enter a character: ");
	fflush(stdout); fflush(stdin);
	scanf("%c",&x);
	printf("ASCII value of %c = %d",x,x);
	return 0;
}
