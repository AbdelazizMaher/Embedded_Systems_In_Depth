/*
 * main.c
 *
 *  Created on: July 21, 2022
 *      Author: Abdelaziz Maher
 */

#include "stdio.h"

int main()
{
	float arr[50];
	int size,i;
	float sum =0;

    printf("Enter the Numbers of data : ");
    fflush(stdout);
    scanf("%d",&size);

    for(i=0 ; i<size ; i++)
    {
    	printf("Enter Number : ");
    	fflush(stdout);
    	scanf("%f",&arr[i]);

    	sum += arr[i];
    }

    printf("Average : %.2f ", sum/size );


    return 0;
}
