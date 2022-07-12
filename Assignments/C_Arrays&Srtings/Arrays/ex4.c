/*
 ============================================================================
 Name        : ex4.c
 Author      : Assem Ayman
 Version     :
 Copyright   : Your copyright notice
 Description : Insert an element in an array in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>

int main(void) {

	int n,x,location,i;

	printf("Enter no of elements: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&n);

	int a[n+1];
	for(i=0; i<n; i++)
		scanf("%d",&a[i]);

	printf("Enter the element to be inserted: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&x);

	printf("Enter the location: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&location);

	for(i=n;i>=location-1;i--)
		a[i+1] = a[i];

	a[location-1]=x;

	for(i=0; i<n+1; i++)
		printf("%d ",a[i]);

	return 0;
}
