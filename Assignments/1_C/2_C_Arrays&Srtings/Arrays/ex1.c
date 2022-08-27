/*
 ============================================================================
 Name        : ex1.c
 Author      : Assem Ayman
 Version     :
 Copyright   : Your copyright notice
 Description : sum of two matrix in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>

int main(void) {

	int i,j;
	float a[2][2],b[2][2],arr[3][3];
	printf("Enter elements of 1st matrix\n");
	for(i=0; i<2; i++){
		for(j=0; j<2; j++){
			printf("Enter a%d%d: ",i+1,j+1);
			fflush(stdin); fflush(stdout);
			scanf("%f",&a[i][j]);
		}
	}
	printf("Enter elements of 2nd matrix\n");
	for(i=0; i<2; i++){
		for(j=0; j<2; j++){
			printf("Enter b%d%d: ",i+1,j+1);
			fflush(stdin); fflush(stdout);
			scanf("%f",&b[i][j]);
		}
	}
	for(i=0; i<2; i++){
		for(j=0; j<2; j++){
			arr[i][j]=a[i][j]+b[i][j];
			printf("%0.1f ",arr[i][j]);
		}
		printf("\n");
	}
	return 0;
}
