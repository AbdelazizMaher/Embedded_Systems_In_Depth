/*
 * main.c
 *
 *  Created on: July 23, 2022
 *      Author: Abdelaziz Maher
 */

#include "stdio.h"


int calc_factorial(int num);

int main()
{
	int value;

	printf("Enter a positive integer: ");
	fflush(stdout);
	scanf("%d",&value);

    // calculate factorial
	printf("factorial of %d = %d", value , calc_factorial(value) );

    return 0;
}


int calc_factorial(int num)
{
	if( num == 0 )
		return 1;

	return num*calc_factorial(num-1);
}
