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

int is_prime(int);

int main(void) {

	int n1,n2,i;

	printf("Enter two numbers(Intervals): ");
	fflush(stdin); fflush(stdout);
	scanf("%d %d",&n1,&n2);

	printf("Prime numbers between %d and %d are: ",n1,n2);

	for(i = n1; i<=n2; i++){
		if(is_prime(i))
			printf("%d ",i);
	}
	return 0;
}

int is_prime (int i){

	int j,prime = 1;
	for(j=2; j<i; j++){
		if(i%j == 0){
			prime = 0;
			break;
		}
	}
	return prime;
}
