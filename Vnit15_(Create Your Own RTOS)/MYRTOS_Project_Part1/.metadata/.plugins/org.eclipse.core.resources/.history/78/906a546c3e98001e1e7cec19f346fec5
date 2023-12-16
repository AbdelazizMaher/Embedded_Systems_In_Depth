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


uint8_t IRQ_Flag;

enum eCPU_AccessLevel{ privileged , unprivileged };

void SwitchCPU_AccessLevel(enum eCPU_AccessLevel Access_Level)
{
	switch( Access_Level )
	{
	case privileged:
		__asm(" mrs r3,CONTROL \n\t"
			  " lsr r3,r3,#0x1 \n\t"
			  " lsl r3,r3,#0x1 \n\t"
			  " msr CONTROL,r0 "    );
		break;
	case unprivileged:
		__asm(" mrs r3,CONTROL \n\t"
			  " orr r3,r3,#0x1 \n\t"
			  " msr CONTROL,r0 "    );
		break;
	}
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
    // Switch to privileged can only be done in Handler mode
	SwitchCPU_AccessLevel(privileged);
}


int main(void)
{
	Clock_Init();

	EXTI_Pinconfig_t cfg;

	cfg.EXTI_PIN = EXTI9B9;
	cfg.IRQ_EN = EXTI_IRQ_ENABLE;
	cfg.P_IRQ_Callback = EXTI9_CallBack;
	cfg.Trigger_Case = EXTI_Trigger_RISING;
	MCAL_EXTI_GPIO_INIT(&cfg);

	IRQ_Flag = 1;

    // Switch to unprivileged can be done in privileged & Thread modes
	SwitchCPU_AccessLevel(unprivileged);

	while(1)
	{
		if(IRQ_Flag)
		{
			IRQ_Flag = 0;
		}
	}
	return 0;
}



