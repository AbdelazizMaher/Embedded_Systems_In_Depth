/*
 * main.c
 *
 *  Created on: July 20, 2022
 *      Author: Abdelaziz Maher
 */

#include "stdio.h"

int main()
{
	char alphabet;

    printf("Enter a character : ");
    fflush(stdout);
    scanf("%c",&alphabet);

    if( (alphabet >= 'A') && (alphabet <= 'z') )
    	printf("%c is an alphabet ",alphabet);
    else
    	printf("%c is not an alphabet ",alphabet);

    return 0;
}
