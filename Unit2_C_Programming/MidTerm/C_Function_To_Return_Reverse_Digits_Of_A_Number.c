/*
 * main.c
 *
 *  Created on: July 26, 2022
 *      Author: Abdelaziz Maher
 */

#include "stdio.h"

int Reverse_Num(int num);

int main()
{
	int num;

    printf("Enter number : ");
    fflush(stdout);
    scanf("%d",&num);

    printf("reverse of the digits = %d  ",Reverse_Num(num));

    return 0;
}

int Reverse_Num(int num)
{
	int reverse = 0;
	int remainder;

	 do
	 {
		remainder = num %10;
		reverse = (reverse*10) + remainder;
	 }
	 while( (num = num/10) );

	 return reverse;
}
