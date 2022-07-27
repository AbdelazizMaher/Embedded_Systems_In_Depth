/*
 * main.c
 *
 *  Created on: July 26, 2022
 *      Author: Abdelaziz Maher
 */

#include "stdio.h"

int sum_of_digits(int num);

int main()
{
	int num = 100;

    printf("sum of numbers from 1 to 100 = %d  ",sum_of_digits(num));

    return 0;
}

int sum_of_digits(int num)
{
	if( num == 0)
		return 0;

	return num + sum_of_digits( num - 1 );
}
