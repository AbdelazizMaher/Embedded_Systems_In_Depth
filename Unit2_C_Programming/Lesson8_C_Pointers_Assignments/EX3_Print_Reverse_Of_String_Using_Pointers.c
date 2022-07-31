/*
 * main.c
 *
 *  Created on: July 31, 2022
 *      Author: Abdelaziz Maher
 */

#include "stdio.h"
#include "string.h"

int main()
{
	char str[100] ,Rev_str[100];
	int i=0;
	char* pstr = str;
	char* pRev_str = Rev_str;

	printf("Print a string in reverse  order : \n");
	printf("--------------------------------\n");

    printf("Enter a string : ");
    fflush(stdout);
    gets(str);

    for(i = 0 ; i <strlen(str) ; i++)
    	*(pRev_str + i) = *(pstr + strlen(pstr)-i-1 );
    *(pRev_str + i) = 0;

    printf("Reverse string is %s ",pRev_str);

    return 0;
}
