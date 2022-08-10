/*
 ============================================================================
 Name        : ex4.c
 Author      : Assem Ayman
 Version     :
 Copyright   : Your copyright notice
 Description : print the elements of an array in reverse order with pointers in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>

int main(void) {

	int size;
	int arr[15];
	int* ptr = arr;
	int i;

	printf("Input the number of elements to store in the array (max 15): ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&size);

	printf("Input %d number of elements in the array\n",size);
	for(i = 0; i<size; i++){
		printf("element - %d : ",i+1);
		fflush(stdin); fflush(stdout);
		scanf("%d",ptr+i);
	}

	puts("The elements of array in reverse order are :");
	for(i=size; i>0; i--){
		printf("element - %d : %d\n",i,*(ptr+i-1));
	}
	return 0;
}
