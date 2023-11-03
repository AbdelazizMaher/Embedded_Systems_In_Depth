/*
 * sevensegment.h
 *
 *  Created on: Oct 22, 2023
 *      Author: Abdelaziz Maher
 */

#ifndef SEVENSEGMENT_SEVENSEGMENT_H_
#define SEVENSEGMENT_SEVENSEGMENT_H_

#include "Stm32f103c6_GPIO_Driver.h"

#define SevSeg_Port  		GPIOB

//PINS
#define A	 	  		 	GPIO_PIN_0
#define B 					GPIO_PIN_1
#define C 					GPIO_PIN_10
#define D 					GPIO_PIN_11
#define E 					GPIO_PIN_12
#define F 					GPIO_PIN_13
#define G 					GPIO_PIN_14



void SevSegment_Init(void);
void SevSegment_Write_Num(int num);

#endif /* SEVENSEGMENT_SEVENSEGMENT_H_ */
