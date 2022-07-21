/*
 * main.c
 *
 *  Created on: July 20, 2022
 *      Author: Abdelaziz Maher
 */

#include "stdio.h"
#include "string.h"

int main()
{
    char str[100],Rev_str[100];
	int i;

    printf("Enter a string : ");
    fflush(stdout);
    gets(str);

    for(i = 0 ; i <strlen(str) ; i++)
    	Rev_str[i] = str[strlen(str)-i-1];
    Rev_str[i] = 0;

    printf("Reverse string is %s ",Rev_str);


    return 0;
}
