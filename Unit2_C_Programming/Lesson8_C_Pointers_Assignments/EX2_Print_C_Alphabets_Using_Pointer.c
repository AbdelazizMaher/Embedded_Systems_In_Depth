/*
 * main.c
 *
 *  Created on: July 31, 2022
 *      Author: Abdelaziz Maher
 */

#include "stdio.h"

int main()
{
	char alphabet = 'A';
	char *p = &alphabet;

	int i;

	for( i = 0 ; i < 26 ; i++)
		printf("%c  ", (*p)++ );

    return 0;
}


