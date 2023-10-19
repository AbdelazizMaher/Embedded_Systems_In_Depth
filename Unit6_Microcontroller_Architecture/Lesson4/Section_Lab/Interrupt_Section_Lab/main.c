/*
 * Interrupt_Section_Lab.c
 *
 * Created: 2/26/2023 10:21:38 PM
 * Author : Abdelaziz Maher
 */ 

#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void GPIO_Leds_Init();
void GPIO_Int_Init();

int main(void)
{
	GPIO_Leds_Init();
	GPIO_Int_Init();
	
	MCUCR |= (1 << ISC00) | (1 << ISC10) | (1 << ISC11);
	MCUCSR &= ~(1 << ISC2);
	
	GICR |= (1 << INT0) | (1 << INT1) | (1 << INT2);
	
	sei();
    /* Replace with your application code */
    while (1) 
    {
		PORTD &= (1<<PD5) | (1<<PD6) | (1<<PD7);
    }
}

void GPIO_Leds_Init()
{
	DDRD |= (1<<PD5) | (1<<PD6) | (1<<PD7);// PIN 5,6,7 AS OUTPUT

}

void GPIO_Int_Init()
{
	DDRD &= ~ ( (1<<PD2) | (1<<PD3) );
	DDRB &= ~(1<<PB2);
}

ISR(INT0_vect)
{
	PORTD |= (1<<PD5);
	_delay_ms(1000);
	PORTD &= ~(1<<PD5);	
}

ISR(INT1_vect)
{
	PORTD |= (1<<PD6);
	_delay_ms(1000);
	PORTD &= ~(1<<PD6);
}

ISR(INT2_vect)
{
    PORTD |= (1<<PD7);
	_delay_ms(1000);
	PORTD &= ~(1<<PD7);
}