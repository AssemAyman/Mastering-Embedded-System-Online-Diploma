/*
 ============================================================================
 Name        : Students_DataBase.c
 Author      : Assem Ayman
 Version     :
 Copyright   : Your copyright notice
 Description : Student Data Base using linked list in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

//node
struct SStudent{
	char name[40];
	unsigned int ID;
	float height;
	struct SStudent* pNextStudent;
};

//head
struct SStudent* gpFirstStudent = NULL;

void Add_Student(){
	struct SStudent* pLastStudent;
	struct SStudent* pNewStudent;
	char temp[40];

	if(gpFirstStudent == NULL){
		//create first record
		pNewStudent = (struct SStudent*)malloc(sizeof(struct SStudent));
		gpFirstStudent = pNewStudent;
	}else{
		//if the list have already records
		pLastStudent = gpFirstStudent;
		while(pLastStudent->pNextStudent) //navigate last node
			pLastStudent= pLastStudent->pNextStudent;

		pNewStudent = (struct SStudent*)malloc(sizeof(struct SStudent));
		pLastStudent->pNextStudent = pNewStudent;
	}
	printf("Enter The Name: ");
	fflush(stdin); fflush(stdout);
	gets(pNewStudent->name);

	printf("Enter ID: ");
	fflush(stdin); fflush(stdout);
	gets(temp);
	pNewStudent->ID = atoi(temp);

	printf("Enter Height: ");
	fflush(stdin); fflush(stdout);
	gets(temp);
	pNewStudent->height = atof(temp);

	pNewStudent->pNextStudent = NULL;
}

int Delete_Student(){
	unsigned int Selected_ID;


	if(gpFirstStudent){ //List have records
		printf("Enter ID to be deleted: ");
		fflush(stdin); fflush(stdout);
		scanf("%u",&Selected_ID);
		struct SStudent* pPreviousStudent = NULL;
		struct SStudent* pSelectedStudent = gpFirstStudent;
		//loop on all records
		while(pSelectedStudent){

			if(pSelectedStudent->ID == Selected_ID){
				if(pPreviousStudent)
					pPreviousStudent->pNextStudent = pSelectedStudent->pNextStudent;
				else //if first node contains the selected ID
					gpFirstStudent = pSelectedStudent->pNextStudent;

				free(pSelectedStudent);
				puts("Student Record has been deleted.");
				return 1;
			}
			pPreviousStudent = pSelectedStudent;
			pSelectedStudent = pSelectedStudent->pNextStudent;
		}
		puts("ID is not found.");
		return 0;
	}
	puts("\nList has no records to delete a student.");
	return 0;
}

void View_Students(){
	unsigned int count = 1;
	struct SStudent* pCurrentStudent = gpFirstStudent;

	if(gpFirstStudent == NULL)
		puts("\nList has no records to be viewed.");

	while(pCurrentStudent){
		printf("\nRecord Number %d\n",count++);
		printf("\t ID: %u\n",pCurrentStudent->ID);
		printf("\t Name: %s\n",pCurrentStudent->name);
		printf("\t Height: %0.2f\n",pCurrentStudent->height);
		pCurrentStudent = pCurrentStudent->pNextStudent;
	}
}

void Delete_All(){
	struct SStudent* pCurrentStudent = gpFirstStudent;
	struct SStudent* pTempStudent = NULL;
	char flag = 0;

	if(gpFirstStudent == NULL)
		puts("\nList has no records to be deleted.");

	while(pCurrentStudent){
		pTempStudent = pCurrentStudent;
		pCurrentStudent = pCurrentStudent->pNextStudent;
		free(pTempStudent);
		flag = 1;
	}

	gpFirstStudent = NULL;
	if(flag) puts("Records Deletion is done.");
}

int Count(struct SStudent* pCurrent){

	if(pCurrent == NULL) 	//basic condition
		return 0;
	else
		return 1 + Count(pCurrent->pNextStudent);  //recursive procedure
}

void Middle(){
	unsigned int count = 1;

	if(gpFirstStudent == NULL)
		puts("\nList has no records to Find its Middle.");
	else{
		struct SStudent* slow_ptr = gpFirstStudent;
		struct SStudent* fast_ptr = gpFirstStudent;
		while(fast_ptr && fast_ptr->pNextStudent){
			fast_ptr = fast_ptr->pNextStudent->pNextStudent;
			slow_ptr = slow_ptr->pNextStudent;
			count++;
		}
		printf("\nMiddle Node index is %d\n",count);
	}
}

void GetNth(){
	int count = 0;

	if( gpFirstStudent == NULL)
		puts("\nList has no records");
	else{
		struct SStudent* main_ptr = gpFirstStudent;
		struct SStudent* ref_ptr  = gpFirstStudent;
		int x;

		printf("Enter n’th node: ");
		fflush(stdin); fflush(stdout);
		scanf("%d",&x);

		while(count++ != x)
			ref_ptr = ref_ptr->pNextStudent;

		while(ref_ptr){
			ref_ptr = ref_ptr->pNextStudent;
			main_ptr = main_ptr->pNextStudent;
		}
		printf("\n\t ID: %u\n",main_ptr->ID);
		printf("\t Name: %s\n",main_ptr->name);
		printf("\t Height: %0.2f\n",main_ptr->height);
	}
}

void Reverse(){
	if(gpFirstStudent == NULL)
		puts("\nList has No Record to reverse.");
	//if the list have already records
	else{
		struct SStudent* Previous_ptr = NULL;
		struct SStudent* Current_ptr = gpFirstStudent;
		struct SStudent* Next_ptr = NULL;

		//navigate till last node
		while(Current_ptr){
			Next_ptr = Current_ptr->pNextStudent;
			Current_ptr->pNextStudent = Previous_ptr;
			Previous_ptr = Current_ptr;
			Current_ptr = Next_ptr;
		}
		gpFirstStudent = Previous_ptr;
		puts("\nReverse is Done.");
	}
}
int main(void) {
	int option,x;

	while(1){
		puts("\t Select One Of The Following Options");
		puts("1: Add Student.");
		puts("2: Delete Student.");
		puts("3: View Students.");
		puts("4: Delete All.");
		puts("5: Reverse List.");
		puts("6: Print n’th node from the end of a Linked List.");
		puts("7: Find the Middle.");
		puts("8: Number of Nodes.");
		printf("Enter Option Number: ");
		fflush(stdin); fflush(stdout);
		scanf("%d",&option);
		switch(option){

		case 1:
			Add_Student();
			break;

		case 2:
			Delete_Student();
			break;

		case 3:
			View_Students();
			break;

		case 4:
			Delete_All();
			break;

		case 5:
			Reverse();
			break;

		case 6:
			GetNth();
			break;

		case 7:
			Middle();
			break;

		case 8:
			x = Count(gpFirstStudent);
			printf("\nNumber of Nodes is %d\n",x);
			break;

		default:
			puts("\nWrong option.\n");
		}
		puts("\t=====================================\n");
	}
}
