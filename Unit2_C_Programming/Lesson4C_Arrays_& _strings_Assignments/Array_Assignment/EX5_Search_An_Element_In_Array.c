/*
 * main.c
 *
 *  Created on: July 20, 2022
 *      Author: Abdelaziz Maher
 */

#include "stdio.h"

int main()
{
	int arr[50];
	int size,element,i;
	int loc = 0;   // if location stays zero, then the no doesn't exist in the array

    printf("Enter no of elements : ");
    fflush(stdout);fflush(stdin);
    scanf("%d",&size);

    // print array
    for(i=1 ; i<=size ; i++)
    {
    	arr[i-1] = 11*i;
    	printf("%d\t  ", arr[i-1]);
    	fflush(stdout);
    }

    printf("\nEnter the element to be searched : ");
    fflush(stdout);
    scanf("%d",&element);
    // Searching
    for(i=0 ; i<size ; i++)
    {
    	if(arr[i] == element)
    	{
    		loc = i+1;
    		break;
    	}
    }

    if( loc == 0)
    	printf("Number is not in the array");
    else
    	printf("Number found at location = %d  ", loc);


    return 0;
}
