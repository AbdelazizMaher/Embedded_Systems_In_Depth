/*
 * main.c
 *
 *  Created on: July 31, 2022
 *      Author: Abdelaziz Maher
 */

#include "stdio.h"

int main()
{
	int arr[15] , Rev[15];
	int* parr =arr;
	int* pRev = Rev;
	int i , size;

	printf("Input the number of elements to store in the array (max 15) : ");
	fflush(stdout);
	scanf("%d",&size);

	printf("Input %d numbers of elements in the array : \n", size);
    for(i=0 ; i<size ; i++)
    {
    	printf("Enter Number - %d : ", i+1);
    	fflush(stdout);
    	scanf("%d", (parr + i) );
    }

    for(i = 0 ; i <size ; i++)
    	*(pRev + i) = *(parr + size-i-1 );

    printf("The elements of array in reverse order are : \n");
    for(i = 0 ; i < size ; i++)
    	printf("Enter Number - %d : %d \n", size -i , *(pRev + i) );


    return 0;
}


