/*
 ============================================================================
 Name        : ex1.c
 Author      : Assem Ayman
 Version     :
 Copyright   : Your copyright notice
 Description : Prime numbers Between two intervals in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>

void get_prime(int,int);
int main(void) {

	int x,y;

	printf("Enter two numbers(Intervals): ");
	fflush(stdin); fflush(stdout);
	scanf("%d %d",&x,&y);
	get_prime(x,y);

	return 0;
}

void get_prime (int a,int b){

	int i,j,isprime=1;

	printf("Prime numbers between %d and %d are: ",a,b);
	for(i=a; i<b; i++){
		for(j=2; j<a; j++){
			if(i % j == 0){
				isprime = 0;
				break;
			}
		}
		if(isprime == 1)
			printf("%d ",i);
		isprime = 1;
	}
}
