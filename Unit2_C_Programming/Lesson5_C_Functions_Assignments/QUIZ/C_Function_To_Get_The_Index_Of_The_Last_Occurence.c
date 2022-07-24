/*
 * main.c
 *
 *  Created on: July 24, 2022
 *      Author: Abdelaziz Maher
 */

#include "stdio.h"

int get_4th_least_bit(int arr[],int length,int num);

int main()
{
	int arr[50],size;
	int num,i;

    printf("Enter size of array : ");
    fflush(stdout);
    scanf("%d",&size);
     // enter array
    for(i=0 ; i<size ; i++)
    {
    	printf("Enter Number : ");
    	fflush(stdout);
    	scanf("%d",&arr[i]);
    }
    // enter number to find
    printf("Enter Number to find its last index : ");
    fflush(stdout);
    scanf("%d",&num);

    printf("result = %d ",get_4th_least_bit(arr,size,num));

    return 0;
}

int get_4th_least_bit(int arr[],int length, int num)
{
	int i;
	int flag = -1;
	for(i = 0 ; i< length ; i++)
	{
		if( num == arr[i])
			flag = i;
	}
	return flag;
}
