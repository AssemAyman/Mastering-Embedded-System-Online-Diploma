/*
 ============================================================================
 Name        : ex3.c
 Author      : Assem Ayman
 Version     :
 Copyright   : Your copyright notice
 Description : Transpose of a Matrix in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>

int main(void) {

	int r,c,i,j;
	printf("Enter rows and column of matrix: ");
	fflush(stdin); fflush(stdout);
	scanf("%d %d",&r,&c);
	int a[r][c],b[c][r];
	printf("Enter elements of matrix:\n");
	for(i=0; i<r; i++){
		for(j=0; j<c; j++){
			printf("Enter element a%d%d: ",i+1,j+1);
			fflush(stdin); fflush(stdout);
			scanf("%d",&a[i][j]);
		}
	}
	printf("Entered Matrix:\n");
	for(i=0; i<r; i++){
		for(j=0; j<c; j++){
			printf("%d ",a[i][j]);
		}
		printf("\n");
	}
	printf("Transpose of Matrix:\n");
	for(i=0; i<c; i++){
		for(j=0; j<r; j++){
			b[i][j] = a[j][i];
			printf("%d ",b[i][j]);
		}
		printf("\n");
	}
	return 0;
}
