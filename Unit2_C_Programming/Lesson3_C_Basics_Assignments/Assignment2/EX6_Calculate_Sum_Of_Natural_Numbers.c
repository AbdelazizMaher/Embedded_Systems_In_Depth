/*
 * main.c
 *
 *  Created on: July 20, 2022
 *      Author: Abdelaziz Maher
 */

#include "stdio.h"

int main()
{
	int value,i;
	int sum =0;


    printf("Enter an integer : ");
    fflush(stdout);
    scanf("%d",&value);

    for( i=0 ; i<=value ; i++ )
    	sum += i ;

    printf("Sum = %d",sum);

    return 0;
}
