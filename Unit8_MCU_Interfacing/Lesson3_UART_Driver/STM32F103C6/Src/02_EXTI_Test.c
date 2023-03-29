/*
 * 02_EXTI_Test.c
 *
 *  Created on: Mar 24, 2023
 *      Author: Abdelaziz Maher
 */

#include <stdint.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include"Stm32f103x6.h"
#include"Stm32f103c6_GPIO_Driver.h"

void Wait(unsigned int x)
{
	int i,j;

	for(i = 0 ; i < x ; i++)
		for(j = 0 ; j < 255 ; j++);
}

void Clock_Init()
{
	// enable PORTA ,PORTB clock
	GPIOA_CLOCK_ENABLE();
	GPIOB_CLOCK_ENABLE();
}


void GPIO_Init()
{
	GPIO_PinConfig_t GPIO_PinConfig;

	//PIN A1 as floating input (reset state)
	GPIO_PinConfig.GPIO_Mode = GPIO_PIN_MODE_INPUT_FLOA;
	GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_1;
	MCAL_GPIO_Init(GPIOA , &GPIO_PinConfig);
	//PIN A13 as floating input (reset state)
	GPIO_PinConfig.GPIO_Mode = GPIO_PIN_MODE_INPUT_FLOA;
	GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_13;
	MCAL_GPIO_Init(GPIOA , &GPIO_PinConfig);

	//PIN B1 as General purpose output push-pull,max speed 10 MHz.
	GPIO_PinConfig.GPIO_Mode = GPIO_PIN_MODE_OUTPUT_PP;
	GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_1;
	GPIO_PinConfig.GPIO_Output_Speed = GPIO_PIN_SPEED_10MHZ;
	MCAL_GPIO_Init(GPIOB , &GPIO_PinConfig);
	//PIN B13 as General purpose output push-pull,max speed 10 MHz.
	GPIO_PinConfig.GPIO_Mode = GPIO_PIN_MODE_OUTPUT_PP;
	GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_13;
	GPIO_PinConfig.GPIO_Output_Speed = GPIO_PIN_SPEED_10MHZ;
	MCAL_GPIO_Init(GPIOB , &GPIO_PinConfig);
}


int main(void)
{
	Clock_Init();
	GPIO_Init();

	while(1)
	{
		if(  MCAL_GPIO_ReadPin(GPIOA , GPIO_PIN_1 ) == 0 )  //Press
		{
			MCAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1);

			while( MCAL_GPIO_ReadPin(GPIOA , GPIO_PIN_1 ) == 0 );  //Single press
		}

		if( MCAL_GPIO_ReadPin(GPIOA , GPIO_PIN_13 ) != 0 )  //Press
		{
			MCAL_GPIO_TogglePin(GPIOB, GPIO_PIN_13);
		}

		Wait(1);
	}
}



