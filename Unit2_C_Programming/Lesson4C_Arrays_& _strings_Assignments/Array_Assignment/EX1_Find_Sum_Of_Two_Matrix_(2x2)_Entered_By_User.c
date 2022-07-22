/*
 * main.c
 *
 *  Created on: July 21, 2022
 *      Author: Abdelaziz Maher
 */

#include "stdio.h"

int main()
{
	float a[2][2];
	float b[2][2];
	int i,j;

    printf("Enter the elements of the 1st matrix :\n");
    fflush(stdout);
    // First Matrix
    for(i=0 ; i<2 ; i++)
    {
    	for(j=0 ; j<2 ; j++)
    	{
    		printf("a%d%d : ", i+1 , j+1);
    		fflush(stdout);
    		scanf("%f",&a[i][j]);
    	}
    }


    printf("Enter the elements of the 2nd matrix :\n");
    fflush(stdout);
    // Second Matrix
    for(i=0 ; i<2 ; i++)
    {
    	for(j=0 ; j<2 ; j++)
    	{
    		printf("b%d%d : ", i+1 , j+1);
    		fflush(stdout);
    		scanf("%f",&b[i][j]);
    	}
    }

    printf("\nSum of Matrix :\n");
    fflush(stdout);
    // Sum
    for(i=0 ; i<2 ; i++)
    {
    	for(j=0 ; j<2 ; j++)
    	{
    		printf("%.1f\t ", a[i][j] + b[i][j]);
    		fflush(stdout);
    	}
    	printf("\n");
    }

    return 0;
}
