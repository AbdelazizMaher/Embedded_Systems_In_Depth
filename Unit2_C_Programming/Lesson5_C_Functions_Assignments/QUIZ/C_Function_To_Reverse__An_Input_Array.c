/*
 * main.c
 *
 *  Created on: July 24, 2022
 *      Author: Abdelaziz Maher
 */

#include "stdio.h"


void Reverse_array(int arr[],int length);

int main()
{
	int arr[50],size;
	int i;

    printf("Enter size of array : ");
    fflush(stdout);
    scanf("%d",&size);

    for(i=0 ; i<size ; i++)
    {
    	printf("Enter Number : ");
    	fflush(stdout);
    	scanf("%d",&arr[i]);
    }

    for(i=0 ; i<size ; i++)
    {
    	printf("%d  ",arr[i]);
    	fflush(stdout);
    }
    printf("\n");

    // calculate values
    Reverse_array(arr,size);

    for(i=0 ; i<size ; i++)
    {
    	printf("%d  ",arr[i]);
    	fflush(stdout);
    }
    return 0;
}

void Reverse_array(int arr[],int length)
{
	int i,j;
	for( i = 0 , j = (length-1) ; i< length-1 ; i++,j--)
	{
		arr[i] = arr[i] + arr[j];
		arr[j] = arr[i] - arr[j];
		arr[i] = arr[i] - arr[j];
	}
}
