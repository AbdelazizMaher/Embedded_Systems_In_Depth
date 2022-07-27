/*
 * main.c
 *
 *  Created on: July 26, 2022
 *      Author: Abdelaziz Maher
 */

#include "stdio.h"

int max_ones(int num);

int main()
{
	int num;

    printf("Enter number : ");
    fflush(stdout);
    scanf("%d",&num);

    printf("number of ones = %d  ",max_ones(num));

    return 0;
}

int max_ones(int num)
{
	int i , now , occ =0;
	int ones = 0;

	for( i = 0 ; i < 32 ; i++)
	{
		now = ((num >> i) & 1);
		ones = ones + now ;
		if( now == 0)
		{
			occ = ( ones > occ) ? ones:occ;
			ones = 0;
		}
	}

	return occ;
}
