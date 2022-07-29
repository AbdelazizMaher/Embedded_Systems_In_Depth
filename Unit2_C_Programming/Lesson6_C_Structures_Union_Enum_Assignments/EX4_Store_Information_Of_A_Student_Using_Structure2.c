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
	struct S_Student student[10];
	int i;

	printf("Enter information of student: \n");
	for( i = 0 ; i<2 ; i++)
		student[i] = ReadInfo();

	printf("\nDisplaying information of student: \n");
	for( i = 0 ; i< 2 ; i++)
		DiplayInfo(student[i]);

    return 0;
}


struct S_Student ReadInfo()
{
	struct S_Student read;

	printf("\nEnter roll number: ");
	fflush(stdout);fflush(stdin);
	scanf("%d",&read.roll);

	printf("Enter Name: ");
	fflush(stdout);fflush(stdin);
	gets(read.name);

	printf("Enter marks: ");
	fflush(stdout);fflush(stdin);
	scanf("%f",&read.marks);

	return read;
}

void DiplayInfo(struct S_Student display)
{
	printf("\nInformation for Roll number %d: " , display.roll );
	printf("\nName: %s " ,display.name );
	printf("\nMarks: %.2f",display.marks );
}
