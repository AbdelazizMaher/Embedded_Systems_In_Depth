/*
 * main.c
 *
 *  Created on: July 20, 2022
 *      Author: Abdelaziz Maher
 */

#include "stdio.h"

int main()
{
    char str[100];
	int length = 0;
	int i = 0;

    printf("Enter a string : ");
    fflush(stdout);
    gets(str);


    while( str[i] != 0 )
    {
    	length++;
    	i++;
    }

    printf("length of  string : %d",length);


    return 0;
}
