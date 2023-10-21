/*
 * keypad.h
 *
 * Created: 6/16/2023 11:33:16 PM
 *  Author: Abdelaziz Maher
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>

#define Keypad_PORT						PORTD
#define Keypad__PORT_DataDir			DDRD
#define Keypad_PIN					    PIND

#define R0 0
#define R1 1
#define R2 2
#define R3 3
#define C0 4
#define C1 5
#define C2 6
#define C3 7



void Keypad_Init(void);
char Keypad_GetKey(void);


#endif /* KEYPAD_H_ */