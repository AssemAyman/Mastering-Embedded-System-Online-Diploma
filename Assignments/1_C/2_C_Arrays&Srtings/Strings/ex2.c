/*
 ============================================================================
 Name        : ex2.c
 Author      : Assem Ayman
 Version     :
 Copyright   : Your copyright notice
 Description : find the length of a string  in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>


int main(void) {

	int count=0,i;
	char c[50];
	printf("Enter a string: ");
	fflush(stdin); fflush(stdout);
	gets(c);

	i=0;
	while(c[i]!= '\0'){
		i++;
		count++;
	}

	printf("Length of string: %d",count);
	return 0;
}
