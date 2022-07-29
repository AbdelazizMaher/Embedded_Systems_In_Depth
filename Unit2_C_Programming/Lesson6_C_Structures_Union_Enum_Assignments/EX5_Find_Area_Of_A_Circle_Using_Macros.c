/*
 * main.c
 *
 *  Created on: July 29, 2022
 *      Author: Abdelaziz Maher
 */

#include "stdio.h"

#define pi 3.142857
#define Area(x)   pi*(x)*(x)

int main()
{
	int radius;

	printf("Enter the radius: ");
	fflush(stdout);
	scanf("%d",&radius);

	printf("Area = %.3f ", Area(radius));

    return 0;
}
