/*
 * Lab2.c
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
	int i = 0;
	
	DDRA = 0xFF;  // PORTA (output-leds)
    RESET_BIT(DDRC,0);  // PIN 0 - PORTC (input-button)
	
    while (1) 
    {
		if( READ_BIT(PINC , 0) == 1 &&  i<8 )
		{
			SET_BIT(PORTA, i);
			_delay_ms(500);
			i++;
		}		
	} 
	
}

