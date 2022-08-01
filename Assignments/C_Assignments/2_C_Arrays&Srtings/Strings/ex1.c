/*
 ============================================================================
 Name        : ex1.c
 Author      : Assem Ayman
 Version     :
 Copyright   : Your copyright notice
 Description : Frequency of characters in a string in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <string.h>

int main(void) {

	int i,count=0;
	char c,a[100];

	printf("Enter a string: ");
	fflush(stdin); fflush(stdout);
	gets(a);

	printf("Enter a character to find frequency: ");
	fflush(stdin); fflush(stdout);
	scanf("%c",&c);

	for(i=0; i<strlen(a); i++){
		if(a[i]==c)
			count++;
	}
	printf("Frequency of %c = %d",c,count);

	return 0;
}
