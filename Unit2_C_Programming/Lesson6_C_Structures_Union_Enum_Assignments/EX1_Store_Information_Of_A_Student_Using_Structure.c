/*
 * main.c
 *
 *  Created on: July 29, 2022
 *      Author: Abdelaziz Maher
 */

#include "stdio.h"

struct S_Student
{
	char name[20];
	int roll;
	float marks;
};

struct S_Student ReadInfo();
void DiplayInfo(struct S_Student display);

int main()
{
	struct S_Student student;

	student = ReadInfo();
	DiplayInfo(student);

    return 0;
}


struct S_Student ReadInfo()
{
	struct S_Student read;

	printf("Enter information of student: \n");
	fflush(stdout);

	printf("Enter Name: ");
	fflush(stdout);
	gets(read.name);

	printf("Enter roll number: ");
	fflush(stdout);
	scanf("%d",&read.roll);

	printf("Enter marks: ");
	fflush(stdout);
	scanf("%f",&read.marks);

	return read;
}

void DiplayInfo(struct S_Student display)
{
	printf("\nDisplaying information : \n");

	printf("Name: %s \n" ,display.name );
	printf("Roll: %d \n" , display.roll );
	printf("Marks: %.2f",display.marks );
}
