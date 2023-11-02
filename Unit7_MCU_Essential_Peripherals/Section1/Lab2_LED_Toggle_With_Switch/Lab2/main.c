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
	RESET_BIT(DDRD,0); // PushButton 0 as input
	RESET_BIT(DDRD,1); // PushButton 1 as input
	RESET_BIT(DDRD,2); // PushButton 2 as input
	SET_BIT(DDRD,4); //Buzzer as Output push/pull
	//3 Leds as output
	SET_BIT(DDRD,5);
	SET_BIT(DDRD,6);
	SET_BIT(DDRD,7);
		
    while (1) 
    {
		if( READ_BIT(PIND , 0) == 1 )
		{
			SET_BIT(PORTD,4);
			SET_BIT(PORTD,5);
			_delay_ms(500);
			RESET_BIT(PORTD,4);
			RESET_BIT(PORTD,5);
		}
		if( READ_BIT(PIND , 1) == 1 )
		{
			SET_BIT(PORTD,4);
			SET_BIT(PORTD,6);
			_delay_ms(500);
			RESET_BIT(PORTD,4);
			RESET_BIT(PORTD,6);
		}
		if( READ_BIT(PIND , 2) == 1 )
		{
			SET_BIT(PORTD,4);
			SET_BIT(PORTD,7);
			_delay_ms(500);
			RESET_BIT(PORTD,4);
			RESET_BIT(PORTD,7);
		}						
	} 
	
}

