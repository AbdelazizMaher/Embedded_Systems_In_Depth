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

 	//3 Leds as output
 	SET_BIT(DDRD,5);
 	SET_BIT(DDRD,6);
 	SET_BIT(DDRD,7);
	   
    while (1) 
    {
		for(int i = 5 ; i < 8 ; i++)
		{
			SET_BIT(PORTD , i);
			_delay_ms(500);
		}
		for(int i = 7 ; i >= 5 ; i--)
		{
			RESET_BIT(PORTD , i);
			_delay_ms(500);
		}		
    }
}

