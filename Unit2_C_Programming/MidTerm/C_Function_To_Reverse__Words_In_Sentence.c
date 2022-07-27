/*
 * main.c
 *
 *  Created on: July 26, 2022
 *      Author: Abdelaziz Maher
 */

#include "stdio.h"
#include "string.h"

void Reverse_string(char arr[],int length, char rev[]);

int main()
{
	char str[50] , rev[50];

    printf("Enter a string : ");
    fflush(stdout);
    gets(str);

    // calculate values
    Reverse_string( str,strlen(str) ,rev );

    printf("reversed string %s ",rev);

    return 0;
}

void Reverse_string(char arr[],int length, char rev[])
{
	int flag =1, i =0 , j , temp1 , count =0 , temp2;
	int size = length;

	while( flag )
	{
		for( j = size-1 ; j >= 0 ; j--)
		{
			if( arr[j] == ' ' || &arr[j] == &arr[0]) // if  found space or first char
			{
				if( arr[j] == arr[0 ] )  // if first char reset flag
				{
					flag = 0;
					count++;  // count holds the size of word
				}
				else
					j++;  // to let j contain the index of the first char in word
				break;
		    }
			count++;
		}

		temp1=i;    // to hold the last index in  reversed arr
		temp2=j;   //  to hold the last index in arr

		for( ; i < temp1+count ; i++ ) // holds the last index in reverse arr plus size of word
		{
			rev[i] = arr[temp2++];
		}
		if( flag != 0)
			rev[i] = ' ';
		i++;
		size = j-1;
		count = 0;
	}
	rev[length] = 0;
}
