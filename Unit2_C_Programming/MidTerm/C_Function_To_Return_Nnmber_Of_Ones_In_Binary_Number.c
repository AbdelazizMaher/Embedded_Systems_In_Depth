/*
 * main.c
 *
 *  Created on: July 26, 2022
 *      Author: Abdelaziz Maher
 */

#include "stdio.h"

int num_of_ones(int num);

int main()
{
	int num;

    printf("Enter number : ");
    fflush(stdout);
    scanf("%d",&num);

    printf("number of ones = %d  ",num_of_ones(num));

    return 0;
}

int num_of_ones(int num)
{
	int i;
	int ones = 0;

	for( i = 0; i < 32 ; i++)
	{
		ones = ones+  ((num >> i) & 1);
	}

	return ones;
}
