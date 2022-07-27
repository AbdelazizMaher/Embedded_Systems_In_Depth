/*
 * main.c
 *
 *  Created on: July 26, 2022
 *      Author: Abdelaziz Maher
 */

#include "stdio.h"

int Sum_of_Digits(int num);

int main()
{
	int num;

    printf("Enter number : ");
    fflush(stdout);
    scanf("%d",&num);

    printf("sum of the digits = %d  ",Sum_of_Digits(num));

    return 0;
}

int Sum_of_Digits(int num)
{
	int sum = 0;
	int remainder;

	 do
	 {
		remainder = num %10;
		sum += remainder;
	 }
	 while( (num = num/10) );

	 return sum;
}
