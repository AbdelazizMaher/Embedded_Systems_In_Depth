/*
 * main.c
 *
 *  Created on: July 20, 2022
 *      Author: Abdelaziz Maher
 */

#include "stdio.h"

int main()
{
	int EVorOD;

    printf("Enter an integer you want to check : ");
    fflush(stdout);
    scanf("%d",&EVorOD);

    if( (EVorOD % 2) == 0 )
    	printf("%d is even ",EVorOD);
    else
    	printf("%d is odd ",EVorOD);

    return 0;
}
