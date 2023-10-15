/*
 * MemMap.h
 *
 * Created: 3/24/2023 11:02:11 AM
 *  Author: Abdel
 */ 


#ifndef MEMMAP_H_
#define MEMMAP_H_

// DIO port A Registers
#define DDRA				  *((volatile unsigned char *)(0x3A))
#define PORTA				  *((volatile unsigned char *)(0x3B))
#define PINA				  *((volatile unsigned char *)(0x39))

// DIO port B Registers
#define DDRB				  *((volatile unsigned char *)(0x37))
#define PORTB			      *((volatile unsigned char *)(0x38))
#define PINB				  *((volatile unsigned char *)(0x36))

// DIO port C Registers
#define DDRC				  *((volatile unsigned char *)(0x34))
#define PORTC				  *((volatile unsigned char *)(0x35))
#define PINC				  *((volatile unsigned char *)(0x33))

// DIO port D Registers
#define DDRD				  *((volatile unsigned char *)(0x31))
#define PORTD				  *((volatile unsigned char *)(0x32))
#define PIND				  *((volatile unsigned char *)(0x30))





#endif /* MEMMAP_H_ */