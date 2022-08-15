/*
 ============================================================================
 Name        : ex5.c
 Author      : Assem Ayman
 Version     :
 Copyright   : Your copyright notice
 Description : search an element in array in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>

int main(void) {

	int n,i,search_for;

	printf("Enter no of elements: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&n);

	int a[n];
	for(i=0; i<n; i++)
		scanf("%d",&a[i]);

	printf("Enter the elements to be searched: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&search_for);
    for(i=0; i<n; i++){
    	if(a[i]==search_for)
    		printf("Number found at the location = %d",i+1);
    }
	return 0;
}
