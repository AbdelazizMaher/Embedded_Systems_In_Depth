/*
 * main.c
 *
 *  Created on: July 20, 2022
 *      Author: Abdelaziz Maher
 */

#include "stdio.h"

int main()
{
	char check;

    printf("Enter an alphabet : ");
    fflush(stdout);
    scanf("%c",&check);

    if( ( check == 'a' ) || ( check == 'e' ) || ( check == 'i' ) || ( check == 'o' ) || ( check == 'u' ) )
    	printf("%c is a Vowel ",check);
    else if(( check == 'A' ) || ( check == 'E' ) || ( check == 'I' ) || ( check == 'O' ) || ( check == 'U' ))
    	printf("%c is a Vowel ",check);
    else
    	printf("%c is a Constant ",check);

    return 0;
}
