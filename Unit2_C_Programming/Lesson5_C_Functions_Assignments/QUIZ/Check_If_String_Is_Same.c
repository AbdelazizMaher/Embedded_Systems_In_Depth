/*
 * main.c
 *
 *  Created on: July 24, 2022
 *      Author: Abdelaziz Maher
 */

#include "stdio.h"
#include "string.h"

int cmp_username(char name1[],char name2[]);
int main()
{
	char name[] = "Abdelaziz";
	char cmp[50];
	int result;

    printf("Enter username : ");
    fflush(stdout);
    gets(cmp);
    // calculate values
    result = cmp_username(name,cmp);

    if(result)
    	printf("wrong username");
    else
    	printf("right username");

    return 0;
}
int cmp_username(char name1[],char name2[])
{
	return stricmp(name1,name2);
}
