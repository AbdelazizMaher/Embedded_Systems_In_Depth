/*
 * main.c
 *
 *  Created on: July 31, 2022
 *      Author: Abdelaziz Maher
 */

#include "stdio.h"

struct S_Employee
{
	char name[50];
	int ID;
};

int main()
{
	struct S_Employee Employee1 , Employee2;
	struct S_Employee* pEmployee[5] = {&Employee1,&Employee2};
	struct S_Employee*(*arr)[5] = &pEmployee;
	int i;

	for( i = 0 ; i < 2 ; i++)
	{
		printf("Input information about employee %d : \n", i+1);

		printf("Employee name : ");
		fflush(stdout);fflush(stdin);
		gets( (*((*arr)[i])).name);

		printf("Employee ID : ");
		fflush(stdout);fflush(stdin);
		scanf("%d", &(*arr)[i]->ID );
	}

	for( i = 0 ; i < 2 ; i++)
	{
		printf("\nDisplay information about employee %d : \n", i+1);

		printf("Employee name : %s \n", (*arr)[i]->name);
		printf("Employee ID : %d", (*((*arr)[i])).ID);
	}


    return 0;
}


