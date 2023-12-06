/*
 * Stm32f103c6_RCC_Driver.c
 *
 *  Created on: Mar 27, 2023
 *      Author: Abdelaziz Maher
 */


#include"Stm32f103c6_RCC_Driver.h"



/*
 * ----------------------------------------------------------
 * 				  Generic Functions
 *-----------------------------------------------------------
 */


/*
 *----------------------------------------------------------
 * 				  Generic Variables
 *----------------------------------------------------------
 */


//Set and cleared by software to control the division factor of the APB1-APB2.
//0xx: HCLK not divided
//100: HCLK divided by 2
//101: HCLK divided by 4
//110: HCLK divided by 8
//111: HCLK divided by 1
const uint8_t  APBPrescTable[8U] = {0,0,0,0,1,2,3,4};

//Set and cleared by software to control AHB clock division factor.
//0xxx: SYSCLK not divided
//1000: SYSCLK divided by 2
//1001: SYSCLK divided by 4
//1010: SYSCLK divided by 8
//1011: SYSCLK divided by 16
//1100: SYSCLK divided by 64
//1101: SYSCLK divided by 128
//1110: SYSCLK divided by 256
//1111: SYSCLK divided by 512
const uint8_t  AHBPrescTable[16U] = {0,0,0,0,0,0,0,1,2,3,4,5,6,7,8,9};

/*
 *-----------------------------------------------------------
 * 				APIs Functions Definitions
 *-----------------------------------------------------------
 */


uint32_t MCAL_RCC_GetSysClkFreq(void)
{
	//Bits 3:2 SWS[1:0]: System clock switch status
	//Set and cleared by hardware to indicate which clock source is used as system clock.
	//00: HSI oscillator used as system clock
	//01: HSE oscillator used as system clock
	//10: PLL used as system clock
	//11: Not applicable
	switch( (RCC->CFGR >> 2) & 0b11 )
	{

	case 0:
		return HSI_RC_CLK;
		break;

	case 1:
		//TODO User should specify it
		return HSE_CLK;
		break;

	case 2:
		//TODO Should Be calculated
		return 16000000;
		break;

	}
	return HSI_RC_CLK;
}

uint32_t MCAL_RCC_GetHClkFreq(void)
{
	//Bits 7:4 HPRE[3:0]: AHB prescaler
	return (    MCAL_RCC_GetSysClkFreq() >> (  AHBPrescTable[ (RCC->CFGR >> 4) & 0xF ]  )    );

}

uint32_t MCAL_RCC_GetPClk1Freq(void)
{
	//Bits 10:8 PPRE1[2:0]: APB Low-speed prescaler (APB1)
	return (    MCAL_RCC_GetHClkFreq() >> (  APBPrescTable[ (RCC->CFGR >> 8) & 0b111 ]  )    );
}

uint32_t MCAL_RCC_GetPClk2Freq(void)
{
	//Bits 13:11 PPRE2[2:0]: APB High-speed prescaler (APB2)
	return (    MCAL_RCC_GetHClkFreq() >> (  APBPrescTable[ (RCC->CFGR >> 11) & 0b111 ]  )    );
}
