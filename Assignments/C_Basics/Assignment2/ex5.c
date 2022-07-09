/*
 ============================================================================
 Name        : ex5.c
 Author      : Assem Ayman
 Version     :
 Copyright   : Your copyright notice
 Description : Alphabet or not in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>

int main(void) {

    char x;
    printf("Enter a character: ");
    fflush(stdin); fflush(stdout);
    scanf("%c",&x);
    (x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z')? printf("%c is an alphabet",x) : printf("%c is not an alphabet",x);
	return 0;
}
