/*
 * keypad.h
 *
 * Created: 6/16/2023 11:33:16 PM
 *  Author: Abdelaziz Maher
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "Stm32f103c6_GPIO_Driver.h"


#define KeyPad_PORT		          		 GPIOB


#define KeyPad_R0						 GPIO_PIN_15
#define KeyPad_R1						 GPIO_PIN_3
#define KeyPad_R2						 GPIO_PIN_4
#define KeyPad_R3						 GPIO_PIN_5
#define KeyPad_C0 						 GPIO_PIN_6
#define KeyPad_C1 						 GPIO_PIN_7
#define KeyPad_C2 						 GPIO_PIN_8
#define KeyPad_C3                        GPIO_PIN_9



void Keypad_Init(void);
char Keypad_GetKey(void);


#endif /* KEYPAD_H_ */
