/*
 ============================================================================
 Name        : ex3.c
 Author      : Assem Ayman
 Version     :
 Copyright   : Your copyright notice
 Description : add two complex numbers using structure in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>

enum index{first=1,second=2};
struct complex{
	float real;
	float imaginary;
}num1,num2;

struct complex get_Data(enum index);
struct complex add(struct complex,struct complex);

int main(void) {

	num1 = get_Data(first);
	num2 = get_Data(second);
	struct complex SUM = add(num1,num2);
	printf("Sum = %0.2f + %0.2fi",SUM.real,SUM.imaginary);
	return 0;
}
struct complex get_Data(enum index n){
	struct complex temp;
	printf("For %dst complex number\n",n);
	printf("Enter real imaginary respectively: ");
	fflush(stdin); fflush(stdout);
	scanf("%f %f",&temp.real,&temp.imaginary);
	return temp;
}
struct complex add(struct complex num1,struct complex num2){
	struct complex sum;
	sum.real = num1.real + num2.real;
	sum.imaginary = num1.imaginary + num2.imaginary;
	return sum;
}
