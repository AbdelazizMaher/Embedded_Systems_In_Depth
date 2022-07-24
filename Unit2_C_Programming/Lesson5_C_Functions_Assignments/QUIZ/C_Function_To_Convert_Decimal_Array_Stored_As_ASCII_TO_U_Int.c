/*
 * main.c
 *
 *  Created on: July 24, 2022
 *      Author: Abdelaziz Maher
 */

#include "stdio.h"
#include "stdlib.h"

int ASCII_to_INT(char arr[]);

int main()
{
	char arr[50];
	int cnv;

    printf("Enter decimal number : ");
    fflush(stdout);
    gets(arr);

    // calculate values
    cnv = ASCII_to_INT(arr);

    printf("%d  ",cnv);

    return 0;
}

int ASCII_to_INT(char arr[])
{
	return atoi(arr);

}
