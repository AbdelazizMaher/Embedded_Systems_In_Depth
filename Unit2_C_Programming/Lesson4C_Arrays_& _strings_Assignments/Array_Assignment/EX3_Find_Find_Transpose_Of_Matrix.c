/*
 * main.c
 *
 *  Created on: July 21, 2022
 *      Author: Abdelaziz Maher
 */

#include "stdio.h"

int main()
{
	int Matrix[50][50];
	int rows,columns;
	int i,j;

    printf("Enter rows and columns of a matrix : ");
    fflush(stdout);
    scanf("%d %d",&rows,&columns);

    printf("Enter elements of Matrix :\n");
    // Matrix
    for(i=0 ; i<rows ; i++)
    {
    	for(j=0 ; j<columns ; j++)
    	{
    		printf("a%d%d : ", i+1 , j+1);
    		fflush(stdout);
    		scanf("%d",&Matrix[i][j]);
    	}
    }

    printf("Entered Matrix :\n");
    fflush(stdout);
    // print Matrix
    for(i=0 ; i<rows ; i++)
    {
    	for(j=0 ; j<columns ; j++)
    	{
    		printf("%d\t  ", Matrix[i][j]);
    		fflush(stdout);
    	}
    	printf("\n");
    }

    printf("\nTranspose of Matrix :\n");
    fflush(stdout);
    // Transpose
    for(i=0 ; i<columns ; i++)
    {
    	for(j=0 ; j<rows ; j++)
    	{
    		printf("%d\t  ", Matrix[j][i]);
    		fflush(stdout);
    	}
    	printf("\n");
    }

    return 0;
}
