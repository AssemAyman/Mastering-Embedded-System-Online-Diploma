/*
 ============================================================================
 Name        : ex3.c
 Author      : Assem Ayman
 Version     :
 Copyright   : Your copyright notice
 Description : print a string in reverse using a pointer in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <string.h>

int main(void){

	char str[20];
	char rev[20];
	char* p_str = str;
	char* p_rev = rev;
	int i,j;

	printf("Input a string : ");
	fflush(stdin); fflush(stdout);
	scanf("%s",str);

	for(i = strlen(str) - 1,j = 0; i >= 0; i-- , j++){
		*(p_rev + j) = *(p_str + i) ;
	}

	*(p_rev + j) = '\0';

	puts(p_rev);

	return 0;
}

