/*
 * main.c
 *
 *  Created on: July 20, 2022
 *      Author: Abdelaziz Maher
 */

#include "stdio.h"

int main()
{
    char str[100],c;
	int freq = 0;
	int i = 0;

    printf("Enter a string : ");
    fflush(stdout);
    gets(str);

    printf("Enter a character to find frequency : ");
    fflush(stdout);
    scanf("%c",&c);

    while( str[i] != 0 )
    {
    	if( str[i] == c )
    		freq++;
    	i++;
    }

    printf("frequency of %c = %d",c,freq);


    return 0;
}
