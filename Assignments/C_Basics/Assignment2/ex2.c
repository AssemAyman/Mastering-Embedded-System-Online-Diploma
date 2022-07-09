/*
 ============================================================================
 Name        : ex2.c
 Author      : Assem Ayman
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>

int main(void) {

	char x;
	printf("Enter an alphabet: ");
	fflush(stdout); fflush(stdin);
	scanf("%c",&x);
	if(x=='a' || x=='e' || x=='i' || x== 'o' || x== 'u' || x=='A' || x=='E' || x=='I' || x== 'O' || x== 'U')
		printf("%c is a vowel",x);
	else
		printf("%c is a consonant",x);
	return 0;
}
