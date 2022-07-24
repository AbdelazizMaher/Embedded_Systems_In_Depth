/*
 * main.c
 *
 *  Created on: July 24, 2022
 *      Author: Abdelaziz Maher
 */

#include "stdio.h"

int check(int num);

int main()
{
	int num;

    printf("Enter number :  ");
    fflush(stdout);
    scanf("%d",&num);

    // Check values
    printf("%d ---> %d", num, check(num));

    return 0;
}

int check(int num)
{
	int power;

	while( num != 1 )
	{
		power= num %3;
		if(power != 0)
			return 1;
		else
			num /= 3;
	}
	return 0;
}
