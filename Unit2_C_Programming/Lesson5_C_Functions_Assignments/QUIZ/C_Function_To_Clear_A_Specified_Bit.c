/*
 * main.c
 *
 *  Created on: July 24, 2022
 *      Author: Abdelaziz Maher
 */

#include "stdio.h"

int clear_bit(int num,int pos);

int main()
{
	int num,pos;
	int result;

    printf("Enter Number : ");
    fflush(stdout);
    scanf("%d",&num);

    printf("Enter position : ");
    fflush(stdout);
    scanf("%d",&pos);

    // calculate values
    result = clear_bit(num,pos);

    printf("result = %d ",result);


    return 0;
}

int clear_bit(int num,int pos)
{
	return num &= ~(1<<pos);
}
