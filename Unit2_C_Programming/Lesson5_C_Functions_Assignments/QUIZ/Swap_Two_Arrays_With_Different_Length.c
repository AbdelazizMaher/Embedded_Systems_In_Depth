/*
 * main.c
 *
 *  Created on: July 24, 2022
 *      Author: Abdelaziz Maher
 */

#include "stdio.h"

void Swap_array(int arr1[],int length1,int arr2[],int length2);

int main()
{
	int arr1[50],size1;
	int arr2[50],size2;
	int i;

	// enter first array
    printf("Enter size of array1 : ");
    fflush(stdout);
    scanf("%d",&size1);

    for(i=0 ; i<size1 ; i++)
    {
    	fflush(stdout);
    	scanf("%d",&arr1[i]);
    }

    // enter second array
    printf("Enter size of array2 : ");
    fflush(stdout);
    scanf("%d",&size2);

    for(i=0 ; i<size2 ; i++)
    {
    	fflush(stdout);
    	scanf("%d",&arr2[i]);
    }
    // print first array before swapping
    printf("\n\nfirst array before swapping: ");
    for(i=0 ; i<size1 ; i++)
    {
    	printf("%d  ",arr1[i]);
    	fflush(stdout);
    }
    // print second array before swapping
    printf("\n\nsecond array before swapping: ");
    for(i=0 ; i<size2 ; i++)
    {
    	printf("%d  ",arr2[i]);
    	fflush(stdout);
    }

    // calculate values
    Swap_array(arr1,size1,arr2,size2);

    // print first array after swapping
    printf("\n\nfirst array after swapping: ");
    for(i=0 ; i<size2 ; i++)
    {
    	printf("%d  ",arr1[i]);
    	fflush(stdout);
    }
    // print second array after swapping
    printf("\n\nsecond array after swapping: ");
    for(i=0 ; i<size1 ; i++)
    {
    	printf("%d  ",arr2[i]);
    	fflush(stdout);
    }

    return 0;
}

void Swap_array(int arr1[],int length1,int arr2[],int length2)
{
	int i,j;
	int length = ( length1 > length2) ?  length1:length2;

	for( i = 0 , j = 0 ; i< length ; i++,j++)
	{
		arr1[i] = arr1[i] + arr2[j];
		arr2[j] = arr1[i] - arr2[j];
		arr1[i] = arr1[i] - arr2[j];
	}
}
