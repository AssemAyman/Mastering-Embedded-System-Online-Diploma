/*
 ============================================================================
 Name        : ex3.c
 Author      : Assem Ayman
 Version     :
 Copyright   : Your copyright notice
 Description : Reverse a sentence in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>

void reverse (char* s);

int main(void) {

	char s[50];

	printf("Enter a sentence: ");
	fflush(stdin); fflush(stdout);
	gets(s);

	reverse(s);

	return 0;
}

void reverse (char* s){

	if(*s != '\0'){
		reverse(s+1);
		printf("%c",*s);
	}
}
