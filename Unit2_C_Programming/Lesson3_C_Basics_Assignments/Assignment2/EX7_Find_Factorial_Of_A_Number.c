/*
 * main.c
 *
 *  Created on: July 20, 2022
 *      Author: Abdelaziz Maher
 */

#include "stdio.h"

int main()
{
   int value,i;
   int factorial=1;

   printf("Enter an integer: ");
   fflush(stdout);
   scanf("%d",&value);

   if( value < 0)
	   printf("ERROR!! Factorial of negative number doesn't exist");
   else
   {
	   for( i=1 ; i<=value ; i++)
		   factorial *= i;

	   printf("Factorial = %d",factorial);
   }



   return 0;
}
