/*
 * main.c
 *
 *  Created on: July 31, 2022
 *      Author: Abdelaziz Maher
 */

#include "stdio.h"

int main()
{
	int m = 29;

	printf("Address of m : %p",&m);
	printf("\nvalue of m : %d\n",m);

	int* ab = &m;
	printf("\nNow ab is assigned with th address of m");

	printf("\nAddress of pointer ab : %p",ab);
	printf("\nContent of pointer ab : %d\n",*ab);

	m = 34;
	printf("\nThe value of m is assigned to 34 now");

	printf("\nAddress of pointer ab : %p",ab);
	printf("\nContent of pointer ab : %d\n",*ab);

	*ab = 7;
	printf("\nThe pointer variable ab is assigned to 7 now");

	printf("\nAddress of m : %p",&m);
	printf("\nvalue of m : %d",m);

    return 0;
}


