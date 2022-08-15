/*
 ============================================================================
 Name        : ex2.c
 Author      : Assem Ayman
 Version     :
 Copyright   : Your copyright notice
 Description : print all the alphabets using a pointer in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>

int main(void) {

	char alph[26];
	char* ptr = alph;
	int i;

	puts("The Alphabets are :");
	for(i = 0; i<26; i++){
		*(ptr + i) = 'A' + i;
		printf("%c ",*(ptr + i));
	}

	return 0;
}
