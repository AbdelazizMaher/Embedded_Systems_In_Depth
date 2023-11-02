/*
 * Lab3.c
 *
 * Created: 4/24/2023 2:26:32 PM
 * Author : Abdelaziz Maher
 */ 


#include "MemMap.h"
#include "Utils.h"
#define F_CPU 8000000UL
#include <util/delay.h>

	
	
int main(void)
{
	int i , j;
	
	DDRC = 0xFF; 
	
    while (1) 
    {
		for ( i = 0 ; i < 10 ; i++ )
		{
			for( j = 0 ; j < 10 ; j++ )
			{
				PORTC = 0b1011 | (i<<4);
				_delay_ms(300);
				PORTC = 0b0111 | (j<<4);
				_delay_ms(300);
			}
		}		
	}
		 
	return 0;
}

