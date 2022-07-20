/*
 * main.c
 *
 *  Created on: July 20, 2022
 *      Author: Abdelaziz Maher
 */

#include "stdio.h"

int main()
{
	float POSorNEG;

    printf("Enter an integer you want to check : ");
    fflush(stdout);
    scanf("%f",&POSorNEG);

    if( POSorNEG > 0 )
    	printf("%.2f is positive ",POSorNEG);
    else if(POSorNEG == 0)
    	printf("You entered zero");
    else
    	printf("%.2f is negative ",POSorNEG);

    return 0;
}
