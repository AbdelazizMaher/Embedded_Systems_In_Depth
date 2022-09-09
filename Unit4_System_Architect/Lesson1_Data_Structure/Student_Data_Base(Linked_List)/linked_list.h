/*
 * linked_list.h
 *
 *  Created on: Aug 13, 2022
 *      Author: Abdel
 */

#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_


#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "conio.h"


#define DPRINTF(...)     { fflush(stdout); \
		                  fflush(stdin); \
		                  printf(__VA_ARGS__); \
		                  fflush(stdout); \
		                  fflush(stdin); }


struct S_data
{
	int ID;
	char name[40];
	float height;
};

struct S_Student
{
	struct S_data Student;
	struct S_Student* pNextStudent;
};


void fill_the_record(struct S_Student* data);
void AddStudent();
void DeleteStudent();
void ViewStudents();
void DeleteAll();
void GetNth_Student();
void LengthOf_StudentList();
int GetLength_Recursive(struct S_Student* pLength);
void GetNth_StudentFromEnd();
void GetMiddle_Student();
void Reverse_StudentList();



#endif /* LINKED_LIST_H_ */
