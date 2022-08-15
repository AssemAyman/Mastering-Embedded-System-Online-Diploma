/*
 ============================================================================
 Name        : ex5.c
 Author      : Assem Ayman
 Version     :
 Copyright   : Your copyright notice
 Description : print ASCII value of a character in C, Ansi-style
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
