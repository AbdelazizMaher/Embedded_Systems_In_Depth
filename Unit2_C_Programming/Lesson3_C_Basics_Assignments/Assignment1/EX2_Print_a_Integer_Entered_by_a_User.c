/*
 * main.c
 *
 *  Created on: July 20, 2022
 *      Author: Abdelaziz Maher
 */

#include "stdio.h"

int main()
{
   int ivalue;

   printf("Enter a integer: ");
   fflush(stdout);

   scanf("%d",&ivalue);
   printf("you entered: %d",ivalue);

   return 0;
}
