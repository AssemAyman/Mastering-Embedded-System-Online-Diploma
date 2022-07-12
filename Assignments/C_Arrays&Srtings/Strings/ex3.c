/*
 ============================================================================
 Name        : ex3.c
 Author      : Assem Ayman
 Version     :
 Copyright   : Your copyright notice
 Description : Reverse String in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <string.h>

int main(void) {

	char c[50];
	int i;

	printf("Enter the string  : ");
	fflush(stdin); fflush(stdout);
	gets(c);

	printf("Reverse string is :");
	for(i=strlen(c); i>=0; i--)
		printf("%c",c[i]);
	return 0;
}
