/*
 * main.c
 *
 *  Created on: July 24, 2022
 *      Author: Abdelaziz Maher
 */

#include "stdio.h"

int get_4th_least_bit(int num);

int main()
{
	int num;

    printf("Enter Number : ");
    fflush(stdout);
    scanf("%d",&num);

    printf("result = %d ",get_4th_least_bit(num));

    return 0;
}

int get_4th_least_bit(int num)
{
	return ((num>>3) & 1) ;
}
