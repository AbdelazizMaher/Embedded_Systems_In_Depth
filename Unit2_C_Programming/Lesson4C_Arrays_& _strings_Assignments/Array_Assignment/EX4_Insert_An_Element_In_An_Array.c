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
	int size=5,element=6,Index=2,i,j;

    printf("Enter no of elements : ");
    fflush(stdout);fflush(stdin);
    scanf("%d",&size);

    // print array
    for(i=1 ; i<=size ; i++)
    {
    	arr[i-1] = i;
    	printf("%d\t  ", arr[i-1]);
    	fflush(stdout);
    }

    printf("\nEnter the element to be inserted : ");
    fflush(stdout);
    scanf("%d",&element);

    printf("\nEnter the location : ");
    fflush(stdout);
    scanf("%d",&Index);

    // print array with inserted element
    for(i=1 ; i<=(size+1) ; i++)
    {
    	if(i == Index)
    	{
    		// Reorganize
    		for(j=size ; j>=Index ; j--)
    			arr[j] = arr[j-1];
    		// add element
    		arr[i-1] = element;
    	}
    	printf("%d\t",arr[i-1]);
    }

    return 0;
}
