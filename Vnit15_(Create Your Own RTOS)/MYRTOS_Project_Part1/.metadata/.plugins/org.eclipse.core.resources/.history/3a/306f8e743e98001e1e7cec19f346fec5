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
uint8_t VAL1 = 3;
uint8_t VAL2 = 7;
uint8_t VAL3 = 0;
uint32_t CPU_CONTROL_Register = 0;
uint32_t CPU_IPSR_Register = 0;

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

	__asm("nop \n\t  nop \n\t nop \n\t");
   // Read and store IPSR register in c variable
	__asm("mrs %[out],IPSR"
		  :[out] "=r" (CPU_IPSR_Register) );

	__asm("nop \n\t  nop \n\t nop \n\t");

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

	__asm("nop \n\t  nop \n\t nop \n\t");
    // Write 5 to VAL3
	__asm("mov %0,#0x5"
		  : "=r" (VAL3) );

	__asm("nop \n\t  nop \n\t");

    // Write value of VAL3
	__asm("mov r0,%0"
		  :
		  : "r" (VAL3) );

	__asm("nop \n\t  nop \n\t");

	// ADD value of VAL1 and VAL2 and put it in VAL3
	__asm("add %[out], %[in1], %[in2]"
		  :[out] "=r" (VAL3)
		  :[in1] "r"  (VAL1) ,
		   [in2] "r"  (VAL2)
		  :      "r2"       );

	__asm("nop \n\t  nop \n\t  nop \n\t");

	// Read and store CONTROL register in c variable
	__asm("mrs %[out],CONTROL"
		  :[out] "=r" (CPU_CONTROL_Register) );

	__asm("nop \n\t  nop \n\t  nop \n\t");

	while(1)
	{
		if(IRQ_Flag)
		{
			IRQ_Flag = 0;
		}
	}
	return 0;
}



