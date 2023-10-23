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
#include "Stm32f103c6_EXTI_Driver.h"
#include "lcd.h"

uint8_t IRQ_Flag;

void Wait(unsigned int x)
{
	int i,j;

	for(i = 0 ; i < x ; i++)
		for(j = 0 ; j < 255 ; j++);
}

void Clock_Init()
{
	// Enable PORTA ,PORTB clock
	GPIOA_CLOCK_ENABLE();
	GPIOB_CLOCK_ENABLE();

	//Enable  AFIO clock
	AFIO_CLOCK_ENABLE();
}

void EXTI9_CallBack(void)
{
	IRQ_Flag = 1;
	LCD_WRITE_STRING("  IRQ EXTI9 has  happened _|- ");
	Wait(1000);
}


int main(void)
{
	Clock_Init();
	LCD_INIT();

	EXTI_Pinconfig_t cfg;

	cfg.EXTI_PIN = EXTI9B9;
	cfg.IRQ_EN = EXTI_IRQ_ENABLE;
	cfg.P_IRQ_Callback = EXTI9_CallBack;
	cfg.Trigger_Case = EXTI_Trigger_RISING;
	MCAL_EXTI_GPIO_INIT(&cfg);

	IRQ_Flag = 1;

	while(1)
	{
		if(IRQ_Flag)
		{
			LCD_Clear_Screen();
			IRQ_Flag = 0;
		}
	}
}



