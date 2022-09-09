/*
 * main.c
 *
 *  Created on: Sep 7, 2022
 *      Author: Assem Ayman
 */

#include "student.h"

extern void init_fifo();

int main(void){

	init_fifo();

	int x;
	puts("\t\t Welcome To The Student Management System\n");
	while(1){
		puts("Choose one of the following options:-");
		puts("1.Add new student manually.");
		puts("2.Add students from text file.");
		puts("3.Find student by ID.");
		puts("4.Find student by first name.");
		puts("5.Find students registered in a specific course.");
		puts("6.Total number of students.");
		puts("7.Delete student by ID.");
		puts("8.Update student by ID.");
		puts("9.Print all students.");
		puts("10.Exit.");

		printf("Enter option number: ");
		flush;
		scanf("%d",&x);
		puts("------------------------");

		switch(x){

		case 1:
			add_student_manually();
			break;

		case 2:
			add_student_file();
			break;

		case 3:
			find_ID();
			break;

		case 4:
			find_firstname();
			break;

		case 5:
			find_course();
			break;

		case 6:
			count();
			break;

		case 7:
			delete_student();
			break;

		case 8:
			update_student();
			break;

		case 9:
			show_all();
			break;

		case 10:
			exit(1);
			break;

		default:
			break;
		}
	}
	return 0;
}
