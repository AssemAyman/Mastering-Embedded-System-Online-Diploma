/*
 * student.c
 *
 *  Created on: Sep 7, 2022
 *      Author: Assem Ayman
 */

#include "student.h"

//Initialization of FIFO
void init_fifo(){
	fifo.base = st;
	fifo.head = st;
	fifo.tail = st;
	fifo.length = 50;
	fifo.count = 0;
}

//Display One Student ONLY
void show_student(Data* ptr){
	puts("The Student Details are");
	printf("The First name is %s\n",ptr->firstname);
	printf("The Last name is %s\n",ptr->lastname);
	printf("The GPA is %0.2f\n",ptr->GPA);
	printf("Courses IDs are ");
	for(int i = 0; i<5; i++){
		printf("%u  ",ptr->CourseID[i]);
	}
	puts("\n------------------------");
}

FIFO_Status_t add_student_manually(){
	//if buffer is full
	if(fifo.length == fifo.count)
		return FIFO_Full;

	//if buffer is not full
	puts("Add the Students Details");
	puts("------------------------");

	uint32_t temp_ID;
	printf("Enter the ID Number: ");
	flush;
	scanf("%u",&temp_ID);

	//check uniqueness of entered ID
	uint8_t unique = 1;
	for(int i = 0; i<fifo.count; i++){
		if(temp_ID == fifo.tail->ID)
			unique = 0;

		fifo.tail++;
	}
	//reset tail
	fifo.tail = fifo.base;

	if(unique)
		fifo.head->ID = temp_ID;
	else{
		puts("[ERROR] ID is already taken");
		puts("------------------------");
		return FIFO_Error;
	}

	printf("Enter the first name of the student: ");
	flush;
	scanf("%s",fifo.head->firstname);

	printf("Enter the last name of the student: ");
	flush;
	scanf("%s",fifo.head->lastname);

	printf("Enter the GPA you obtained: ");
	flush;
	scanf("%f",&(fifo.head->GPA));

	puts("Enter the course ID of each course");
	for(int i = 0; i<5; i++){
		printf("Course %d ID: ",i+1);
		flush;
		scanf("%u",&(fifo.head->CourseID[i]));
	}

	puts("[INFO] Students Details are added Successfully");
	puts("------------------------");
	fifo.head++;
	fifo.count++;

	count();

	return FIFO_NO_Error;
}

FIFO_Status_t add_student_file(){
	//if buffer is full
	if(fifo.length == fifo.count)
		return FIFO_Full;

	FILE* fptr;
	fptr = fopen("data.txt","r");

	//IF the file does NOT exist
	if(!fptr){
		puts("[ERROR] The File was not found.");
		puts("------------------------");
		return FIFO_Error;
	}

	//The file exists
	uint32_t temp_ID;
	while(!feof(fptr) && !ferror(fptr) && (fifo.count != fifo.length)){ //loops till the end of the text file
		//Check uniqueness of entered ID
	    uint8_t unique = 1;
		fscanf(fptr,"%u",&temp_ID);
		for(int i = 0; i<fifo.count; i++){
			if(temp_ID == fifo.tail->ID){
				printf("[ERROR] ID %u is already taken\n",temp_ID);
				puts("------------------------");
				// Ignore the rest of the line
			    fscanf(fptr, "%*[^\n]");
				unique = 0;
				break;
			}
			fifo.tail++;
		}
		//reset tail
		fifo.tail = fifo.base;

		//IF ID is unique
		if(unique){
			fifo.head->ID = temp_ID;
			fscanf(fptr,"%s",fifo.head->firstname);
			fscanf(fptr,"%s",fifo.head->lastname);
			fscanf(fptr,"%f",&fifo.head->GPA);
			for(int i = 0; i<5; i++)
				fscanf(fptr,"%u",&fifo.head->CourseID[i]);

			printf("[INFO] ID %u added Successfully\n",temp_ID);
			puts("------------------------");
			fifo.head++;
			fifo.count++;
		}
	}
	fclose(fptr);

	count();

	return FIFO_NO_Error;
}

FIFO_Status_t find_ID(){
	//If buffer is empty
	if(!fifo.count){
		puts("[ERROR] There is NO Data");
		puts("------------------------");
		return FIFO_Empty;
	}

	//IF buffer is not empty
	uint32_t wanted_ID;
	printf("Enter the ID of the student: ");
	flush;
	scanf("%u",&wanted_ID);

	//loops till find wanted ID
	uint32_t i;
	for(i = 0; i<fifo.count; i++){
		if(wanted_ID == fifo.tail->ID){
			show_student(fifo.tail);
			break;
		}
		fifo.tail++;
	}
	//reset tail
	fifo.tail = fifo.base;

	//IF ID exists
	if(i < fifo.count)
		return FIFO_NO_Error;
	//IF ID does NOT exist
	else
	{
		printf("[ERROR] ID %u was not found\n",wanted_ID);
		puts("------------------------");
		return FIFO_Error;
	}
}

FIFO_Status_t find_firstname(){
	//If buffer is empty
	if(!fifo.count){
		puts("[ERROR] There is NO Data");
		puts("------------------------");
		return FIFO_Empty;
	}

	//IF buffer is not empty
	char wanted_name[15] ;
	printf("Enter the First Name of the student: ");
	flush;
	scanf("%s",wanted_name);

	uint8_t found = 0;
	//loops till find wanted name
	for(int i = 0; i<fifo.count; i++){
		if(!stricmp(wanted_name,fifo.tail->firstname)){
			show_student(fifo.tail);
			found = 1;
		}

		fifo.tail++;
	}
	//reset tail
	fifo.tail = fifo.base;

	//IF name exists
	if(found)
		return FIFO_NO_Error;
	//IF name does NOT exist
	else
	{
		printf("[ERROR] First Name %s was not found\n",wanted_name);
		puts("------------------------");
		return FIFO_Error;
	}
}

FIFO_Status_t find_course(){
	//If buffer is empty
	if(!fifo.count){
		puts("[ERROR] There is NO Data");
		return FIFO_Empty;
	}

	//IF buffer is not empty
	uint32_t wanted_CourseID;
	printf("Enter the Course ID: ");
	flush;
	scanf("%u",&wanted_CourseID);

	uint32_t count = 0;
	//loops till find wanted course ID
	for(int i = 0;  i<fifo.count; i++){
		for(int j = 0; j<5; j++){
			if(wanted_CourseID == fifo.tail->CourseID[j]){
				show_student(fifo.tail);
				count++;
			}
		}
		fifo.tail++;
	}
	//reset tail
	fifo.tail = fifo.base;

	//IF course ID exists
	if(count){
		printf("[INFO] Total Numbers of Students Enrolled: %u\n",count);
		puts("------------------------");
		return FIFO_NO_Error;
	}
	//IF course ID does NOT exist
	else
	{
		printf("[ERROR] Course ID %u was not found\n",wanted_CourseID);
		puts("------------------------");
		return FIFO_Error;
	}
}

FIFO_Status_t delete_student(){
	//IF buffer is empty
	if(!fifo.count){
		puts("[ERROR] There is NO Data");
		puts("------------------------");
		return FIFO_Empty;
	}

	//IF buffer is not empty
	uint32_t del_ID;
	uint8_t deleted = 0;
	printf("Enter The ID to be deleted: ");
	flush;
	scanf("%u",&del_ID);

	//loops till find ID
	int i;
	for(i = 0; i<fifo.count; i++){
		//IF student is found
		if(del_ID == fifo.tail->ID){
			//Shift each student back by one to exploit the space of deleted student
			Data* temp_tail = fifo.tail;
			while(++(fifo.tail) != fifo.head){ //while it hasn't reached the end yet
				//Copying data
				strcpy(temp_tail->firstname,fifo.tail->firstname);
				strcpy(temp_tail->lastname,fifo.tail->lastname);
				temp_tail->ID = fifo.tail->ID;
				temp_tail->GPA = fifo.tail->GPA;
				for(int i = 0; i<5; i++)
					temp_tail->CourseID[i] = fifo.tail->CourseID[i];

				temp_tail = fifo.tail;
			}
			fifo.count--;
			//set head one position back
			fifo.head--;
			//flag
			deleted = 1;
			break;
		}
		fifo.tail++;
	}

	//reset tail
	fifo.tail = fifo.base;

	//IF ID of student exists
	if(deleted){
		puts("[INFO] The Student is removed Successfully");
		puts("------------------------");
		return FIFO_NO_Error;
	}
	//IF ID of student does NOT exists
	else{
		printf("[ERROR] This ID %u was not found\n",del_ID);
		puts("------------------------");
		return FIFO_Error;
	}
}

FIFO_Status_t update_student(){
	//IF buffer is empty
	if(!fifo.count){
		puts("[ERROR] There is NO Data");
		puts("------------------------");
		return FIFO_Empty;
	}

	//IF buffer is NOT empty
	uint32_t i,x,update_ID;
	printf("Enter the ID to update its student data: ");
	flush;
	scanf("%u",&update_ID);

	//loops till find wanted ID
	for(i = 0; i<fifo.count; i++){
		//if ID is found
		if(update_ID == fifo.tail->ID){
			puts("What do you want to update?");
			puts("1. First Name.");
			puts("2. Last Name.");
			puts("3. ID.");
			puts("4. GPA.");
			puts("5. Courses IDs.");
			flush;
			scanf("%u",&x);

			switch(x){

			case 1:
				printf("Enter the new first name: ");
				flush;
				scanf("%s",fifo.tail->firstname);
				break;

			case 2:
				printf("Enter the new last name: ");
				flush;
				scanf("%s",fifo.tail->lastname);
				break;

			case 3:
				printf("Enter the new ID: ");
				flush;
				scanf("%u",&fifo.tail->ID);
				break;

			case 4:
				printf("Enter the new GPA: ");
				flush;
				scanf("%f",&fifo.tail->GPA);
				break;

			case 5:
				printf("Enter the new courses IDs: ");
				flush;
				for(int i = 0; i<5; i++)
					scanf("%u",&fifo.tail->CourseID[i]);
				break;

			default:
				break;
			}
			break;
		}
		fifo.tail++;
	}
	//reset tail
	fifo.tail = fifo.base;

	//IF ID exists
	if(i < fifo.count){
		puts("[INFO] Student Data Updated Successfully.");
		puts("------------------------");
		return FIFO_NO_Error;
	}
	//IF ID does NOT exist
	else
	{
		printf("[ERROR] ID %u was not found\n",update_ID);
		puts("------------------------");
		return FIFO_Error;
	}
}

FIFO_Status_t count(){
	//If buffer is empty
	if(!fifo.count){
		puts("[ERROR] There is NO Data");
		return FIFO_Empty;
	}

	//IF buffer is NOT empty
	printf("[INFO] The total number of Student is %u\n",fifo.count);
	puts("[INFO] You can add up to 50 Students");
	printf("[INFO] You can add %u more studetns\n",50-fifo.count);
	puts("------------------------");
	return FIFO_NO_Error;
}

FIFO_Status_t show_all(){
	//If buffer is empty
	if(!fifo.count){
		puts("[ERROR] There is NO Data");
		puts("------------------------");
		return FIFO_Empty;
	}

	//Display All Students
	for(int i = 0; i<fifo.count; i++){
		show_student(fifo.tail);
		fifo.tail++;
	}
	//reset tail
	fifo.tail = fifo.base;

	count();

	return FIFO_NO_Error;
}
