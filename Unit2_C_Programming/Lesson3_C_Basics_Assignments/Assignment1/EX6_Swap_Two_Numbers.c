/*
 * main.c
 *
 *  Created on: July 20, 2022
 *      Author: Abdelaziz Maher
 */

#include "stdio.h"

int main()
{
	float a,b,temp;

    printf("Enter value of a :");
    fflush(stdout);
    scanf("%f",&a);

    printf("Enter value of b :");
    fflush(stdout);
    scanf("%f",&b);

    temp = a;
    a = b;
    b = temp;

    printf("After swapping, value of a = %.2f\n",a);
    printf("After swapping, value of b = %.1f",b);

    return 0;
}
