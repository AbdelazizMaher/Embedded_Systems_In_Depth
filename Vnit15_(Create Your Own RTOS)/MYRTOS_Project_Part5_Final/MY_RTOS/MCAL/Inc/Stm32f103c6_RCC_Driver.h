/*
 * Stm32f103c6_RCC_Driver.h
 *
 *  Created on: Mar 27, 2023
 *      Author: Abdelaziz Maher
 */

#ifndef INC_STM32F103C6_RCC_DRIVER_H_
#define INC_STM32F103C6_RCC_DRIVER_H_


//-----------------------------------------------
//Includes
//-----------------------------------------------
#include"Stm32f103x6.h"
#include"Stm32f103c6_GPIO_Driver.h"

/*
 *----------------------------------------------------------
 * 				  Generic Macros
 *----------------------------------------------------------
 */

#define HSE_CLK					(uint32_t)( 16000000 )
#define HSI_RC_CLK				(uint32_t)( 8000000 )


/*
 * =======================================================================================
 *                         APIs Supported by "MCAL RCC DRIVER"
 * =======================================================================================
 */
uint32_t MCAL_RCC_GetSysClkFreq(void);
uint32_t MCAL_RCC_GetHClkFreq(void);
uint32_t MCAL_RCC_GetPClk1Freq(void);
uint32_t MCAL_RCC_GetPClk2Freq(void);

#endif /* INC_STM32F103C6_RCC_DRIVER_H_ */
