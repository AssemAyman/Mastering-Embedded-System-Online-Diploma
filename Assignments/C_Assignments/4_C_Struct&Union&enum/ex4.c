/*
 ============================================================================
 Name        : ex4.c
 Author      : Assem Ayman
 Version     :
 Copyright   : Your copyright notice
 Description : Store information of students using structure in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>

struct students{
	char name[50];
	int roll;
	float marks;
};

struct students get_Data();
void print_Data(struct students s[]);

int main(void) {

	struct students s[10];
	int i;
    puts("Enter information of students");
    for(i=0; i<10; i++){
    	s[i] = get_Data();
    }
    puts("Displaying information of students");
    print_Data(s);

	return 0;
}
struct students get_Data(){

	struct students temp;
	static int j=1;

	printf("For roll number %d\n",j++);

	printf("Enter name: ");
	fflush(stdin); fflush(stdout);
	scanf("%s",temp.name);

	printf("Enter marks: ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&temp.marks);

	return temp;
}
void print_Data(struct students s[]){

	int i;
    for(i=0; i<10; i++){
    	printf("Information for roll number %d\nName: %s\nMarks: %0.2f\n",i+1,s[i].name,s[i].marks);
    }
}
