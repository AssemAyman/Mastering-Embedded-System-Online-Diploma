/*
 ============================================================================
 Name        : ex2.c
 Author      : Assem Ayman
 Version     :
 Copyright   : Your copyright notice
 Description : calculate average using array in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>

int main(void) {

	int n,i;
	printf("Enter the number of data: ");
	fflush(stdin); fflush(stdout);
    scanf("%d",&n);
	float a[n],sum=0.0;
    for(i=0; i<n; i++){
    	printf("%d. Enter number: ",i+1);
    	fflush(stdin); fflush(stdout);
    	scanf("%f",&a[i]);
    	sum+=a[i];
    }
    printf("Average = %0.2f",sum/n);
	return 0;
}
