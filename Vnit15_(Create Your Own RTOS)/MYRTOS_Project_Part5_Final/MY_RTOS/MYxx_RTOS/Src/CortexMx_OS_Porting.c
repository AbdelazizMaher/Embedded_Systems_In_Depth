/*
 * CortexMx_OS_Porting.c
 *
 *  Created on: Dec 13, 2023
 *      Author: Abdelaziz Maher
 */



#include "CortexMx_OS_Porting.h"


void NMI_Handler()
{
	while(1);
}

void HardFault_Handler()
{
	while(1);
}

void MemManage_Handler()
{
	while(1);
}

void BusFault_Handler()
{
	while(1);
}

void UsageFault_Handler()
{
	while(1);
}


 __attribute(( naked )) void SVC_Handler()
{
 	__asm("TST lr,0x4   \n\t"
 		  "ITE EQ       \n\t"
 		  "MRSEQ r0,MSP \n\t"
 		  "MRSNE r0,PSP \n\t"
 		  "b OS_SVC_Services");
}

void OS_Trigger_PendSV()
{
	 // Set PendSV
	 SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk ;
}

void HW_Init()
{
	//Initialize Clock Tree (RCC -> SysTick Timer & CPU) Where RCC Default Values -> CPU Clock & SySTick Timer clock = 8 MHZ
	//	8 MHZ
	//	1 count -> 0.125 us
	//	X count -> 1 ms
	//	X = 8000 Count

	// Init HW

	// Decrease PendSV interrupt priority to be smaller than or equal SysticTimer
	//SysTICK has a priority of 15
	__NVIC_SetPriority(PendSV_IRQn, 15);

	__NVIC_SetPriority(SysTick_IRQn, 12);
}


void Start_Ticker()
{
	//	This Clock Tree should be defined in HW_init()
	//	8 MHZ
	//	1 count -> 0.125 us
	//	X count -> 1 ms
	//	X = 8000 Count

	 SysTick_Config(8000);
}


