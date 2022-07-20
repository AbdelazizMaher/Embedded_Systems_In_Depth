/*
 * main.c
 *
 *  Created on: July 20, 2022
 *      Author: Abdelaziz Maher
 */

#include "stdio.h"

int main()
{
	float num1,num2,num3;
	float largest_num;

    printf("Enter three numbers : ");
    fflush(stdout);
    scanf("%f %f %f",&num1,&num2,&num3);

    largest_num =num1;

    if(num1 > largest_num)
    	largest_num =num1;

    if(num2 > largest_num)
    	largest_num =num2;

    if(num3 > largest_num)
    	largest_num =num3;

    printf("largest number = %f",largest_num);

    return 0;
}
