/*
 * main.c
 *
 *  Created on: July 26, 2022
 *      Author: Abdelaziz Maher
 */

#include "stdio.h"

int check_prime(int value);

int main()
{
    int min_value,max_value;
    int i,flag = 0;

    printf("Enter two numbers(intervals) : ");
    fflush(stdout);
    scanf("%d %d",&min_value,&max_value);

    printf("Prime numbers between %d and %d are : ",min_value,max_value);

    for( i = (min_value) ; i< max_value ; i++)
    {
    	flag = check_prime(i);
    	if( flag != 0)
    		printf("%d ",i);
    }

    return 0;
}

int check_prime(int value)
{
	int i;

//	if( value == 1)      1 is not a prime number but the test case
//		return 0;          contains 1

	for( i =2 ; i <= (value/2) ; i++)
	{
		if( value%i  == 0)
			return 0;
	}

    return 1;
}
