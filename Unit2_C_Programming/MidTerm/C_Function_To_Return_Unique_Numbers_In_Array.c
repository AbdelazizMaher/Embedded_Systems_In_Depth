/*
 * main.c
 *
 *  Created on: July 26, 2022
 *      Author: Abdelaziz Maher
 */

#include "stdio.h"

int unique_numbers(int arr[], int length,int arr1[]);

int main()
{
	int arr[50] , arr1[50] , size1  , size2;
	int i;

    printf("Enter size of array : ");
    fflush(stdout);
    scanf("%d",&size1);

    for(i=0 ; i<size1 ; i++)
    {
    	printf("Enter Number : ");
    	fflush(stdout);
    	scanf("%d",&arr[i]);
    }

    size2 = unique_numbers( arr , size1 ,arr1);

    if( size2 == 0 )
    	printf("No unique number ");

    for(i=0 ; i<size2 ; i++)
    {
    	fflush(stdout);
    	printf("%d ",arr1[i]);
    }

    return 0;
}

int unique_numbers(int arr[], int length , int arr1[])
{
	int j;
	static int i = 0;
	static int size = 0;

	if( i == length )
		return size;

	for( j = 0 ; j < length ; j++)
	{
		if( i == j && j!= length-1 ) // not to check same number
			j++;

		if( i == length-1  &&  j == length-1)  // for last digit
			continue;

		if( arr[i] == arr[j]) //check
			break;
	}

	if( j == length ) // if we are here,there is no duplication
	{
		arr1[size] = arr[i];
		size++; // size of non duplicated elements
	}

	i++;
	return unique_numbers(arr,length ,arr1);
}
