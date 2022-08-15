/*
 ============================================================================
 Name        : ex2.c
 Author      : Assem Ayman
 Version     :
 Copyright   : Your copyright notice
 Description : Add two distances (inch-feet) using structure in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>

enum index{first=1,second};
struct distance{

	float feet;
	float inch;

}dis1,dis2;

struct distance get_Data(enum index);
void add(struct distance,struct distance);

float feet_sum,inch_sum;

int main(void) {

	dis1 = get_Data(first);
	dis2 = get_Data(second);
	add(dis1,dis2);
	printf("sum of distances = %0.2f'-%0.2f''",feet_sum,inch_sum);
	return 0;
}

struct distance get_Data(enum index n){

	struct distance temp;
	printf("Enter information for %dst distance\n",n);
	printf("Enter feet: ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&temp.feet);
	printf("Enter inch: ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&temp.inch);
	return temp;
}
void add(struct distance dis1,struct distance dis2){
	feet_sum = dis1.feet + dis2.feet;
	inch_sum = dis1.inch + dis2.inch;

	while(inch_sum >= 12){
		feet_sum++;
		inch_sum-=12;
	}
}
