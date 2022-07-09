/*
 ============================================================================
 Name        : ex8.c
 Author      : Assem Ayman
 Version     :
 Copyright   : Your copyright notice
 Description : Simple calculator in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>

int main(void) {

	char x;
	float n1,n2;
	printf("Enter operator either + or - or * or / : ");
	fflush(stdout); fflush(stdin);
	scanf("%c",&x);
	printf("Enter two operands: ");
	fflush(stdout); fflush(stdin);
	scanf("%f %f",&n1,&n2);
	switch (x){
	case ('+'):
			printf("%0.2f %c %0.2f = %0.2f",n1,x,n2,n1+n2);
			break;
	case ('-'):
			printf("%0.2f %c %0.2f = %0.2f",n1,x,n2,n1-n2);
			break;
	case ('*'):
			printf("%0.2f %c %0.2f = %0.2f",n1,x,n2,n1*n2);
			break;
	case ('/'):
			printf("%0.2f %c %0.2f = %0.2f",n1,x,n2,n1/n2);
			break;
	}
	return 0;
}
