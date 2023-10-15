/*
 * Lab1.c
 *
 * Created: 3/24/2023 10:27:44 AM
 * Author : Abdelaziz Maher
 */ 


#include "MemMap.h"
#include "Utils.h"
#define F_CPU 8000000UL
#include <util/delay.h>


int main(void)
{
   DDRA = 0xFF;
   
    while (1) 
    {
		for(int i = 0 ; i < 8 ; i++)
		{
			SET_BIT(PORTA , i);
			_delay_ms(500);
		}
		for(int i = 7 ; i >= 0 ; i--)
		{
			RESET_BIT(PORTA , i);
			_delay_ms(500);
		}		
    }
}

