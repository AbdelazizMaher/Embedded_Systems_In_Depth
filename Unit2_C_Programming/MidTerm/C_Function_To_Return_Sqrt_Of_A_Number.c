/*
 * main.c
 *
 *  Created on: July 26, 2022
 *      Author: Abdelaziz Maher
 */

#include "stdio.h"
#include "math.h"

float calc_sqrt(float num);

int main()
{
	float num;

    printf("Enter number : ");
    fflush(stdout);
    scanf("%f",&num);

    printf("square root of the number = %.3f  ",calc_sqrt(num));

    return 0;
}

float calc_sqrt(float num)
{
	 return sqrt(num);
}
