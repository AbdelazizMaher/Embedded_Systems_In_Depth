/*
 * main.c
 *
 *  Created on: July 20, 2022
 *      Author: Abdelaziz Maher
 */

#include "stdio.h"

int main()
{
	float a,b;

    printf("Enter value of a :");
    fflush(stdout);
    scanf("%f",&a);

    printf("Enter value of b :");
    fflush(stdout);
    scanf("%f",&b);

    a = a+b;
    b = a-b;
    a = a-b;

    printf("After swapping, value of a = %f\n",a);
    printf("After swapping, value of b = %f",b);

    return 0;
}
