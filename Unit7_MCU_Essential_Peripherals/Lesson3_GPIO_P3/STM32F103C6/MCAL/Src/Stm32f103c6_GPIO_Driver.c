/*
 * Stm32f103c6_GPIO_Driver.c
 *
 *  Created on: Feb 28, 2023
 *      Author: Abdelaziz Maher
 */

#include "Stm32f103c6_GPIO_Driver.h"



/*
 * ----------------------------------------------------------
 * 				  Generic Functions
 *-----------------------------------------------------------
 */
uint8_t Get_CRLH_Position(uint16_t PinNumber)
{
	switch( PinNumber )
	{
	//CRL
	case GPIO_PIN_0:
		return 0;
		break;

	case GPIO_PIN_1:
		return 4;
		break;

	case GPIO_PIN_2:
		return 8;
		break;

	case GPIO_PIN_3:
		return 12;
		break;

	case GPIO_PIN_4:
		return 16;
		break;

	case GPIO_PIN_5:
		return 20;
		break;

	case GPIO_PIN_6:
		return 24;
		break;

	case GPIO_PIN_7:
		return 28;
		break;

		//CRH
	case GPIO_PIN_8:
		return 0;
		break;

	case GPIO_PIN_9:
		return 4;
		break;

	case GPIO_PIN_10:
		return 8;
		break;

	case GPIO_PIN_11:
		return 12;
		break;

	case GPIO_PIN_12:
		return 16;
		break;

	case GPIO_PIN_13:
		return 20;
		break;

	case GPIO_PIN_14:
		return 24;
		break;

	case GPIO_PIN_15:
		return 28;
		break;
	}
	return 0;
}



/*
 *-----------------------------------------------------------
 * 				APIs Functions Definitions
 *-----------------------------------------------------------
 */


/**================================================================
 * @Fn			- MCAL_GPIO_Init
 * @brief 		- Initialize the GPIOx PINy according to the specified parameters in the Pin_Config
 * @param [in]	- GPIOx: where x can be (A...E depending on the device used) to select the GPIO peripheral
 * @param [in] 	- Pin_Config: pointer to GPIO_Pin_Config_t structure which contains
 *                the configuration information for the specified GPIO Pin
 * @retval 		- None
 * Note			- STM32F103C6 MCU has GPIO A,B,C,D,E modules
 * 				  but LQFP48 package has only GPIO A,B, part of C/D exported as external Pins from the modules
 **================================================================*/
void MCAL_GPIO_Init(GPIO_TypeDef *GPIOx , GPIO_PinConfig_t *Pin_Config)
{
	volatile uint32_t *ConfigReg = NULL;
	uint8_t ConfigPin = 0;

	//Port configuration register low (GPIOx_CRL) Configure Pins from 0 --> 7
	//Port configuration register high (GPIOx_CRH) Configure Pins from 8 --> 15
	ConfigReg = ( Pin_Config->GPIO_PinNumber < GPIO_PIN_8 ) ? &(GPIOx->CRL) : &(GPIOx->CRH);

	//Clear  CNF[1:0] MODE[1:0]
	(*ConfigReg) &= ~( (0xF) << Get_CRLH_Position(Pin_Config->GPIO_PinNumber) );

	//If Pin is output
	if( (Pin_Config->GPIO_Mode == GPIO_PIN_MODE_OUTPUT_PP ) || (Pin_Config->GPIO_Mode == GPIO_PIN_MODE_OUTPUT_OD ) | (Pin_Config->GPIO_Mode == GPIO_PIN_MODE_ALTFN_OUTPUT_OD ) | (Pin_Config->GPIO_Mode == GPIO_PIN_MODE_ALTFN_OUTPUT_PP ) )
	{
		//Set CNF[1:0] MODE[1:0]
		ConfigPin = ( (( (Pin_Config->GPIO_Mode - 4) << 2 ) | ( Pin_Config->GPIO_Output_Speed ))  & 0x0F );
	}
	//If Pin is input
	else //MODE = 00 :Input Mode(reset state)
	{
		if( (Pin_Config->GPIO_Mode == GPIO_PIN_MODE_INPUT_FLOA ) || (Pin_Config->GPIO_Mode == GPIO_PIN_MODE_Analog ) )
		{
			//Set CNF[1:0] MODE[1:0]00
			ConfigPin = ( ( (Pin_Config->GPIO_Mode) << 2 ) & 0x0F );
		}
		else if( Pin_Config->GPIO_Mode == GPIO_PIN_MODE_ALTFN_INPUT ) //Consider it as Input Floating
		{
			//Set CNF[1:0] MODE[1:0]00
			ConfigPin = ( ( (GPIO_PIN_MODE_INPUT_FLOA) << 2 ) & 0x0F );
		}
		else // PU\PD Input
		{
			ConfigPin = ( ( (GPIO_PIN_MODE_INPUT_PU) << 2 ) & 0x0F );

			if ( Pin_Config->GPIO_Mode == GPIO_PIN_MODE_INPUT_PU )
			{
				//PxODR = 1 :Table 20. Port bit configuration table
				GPIOx->ODR |= (Pin_Config->GPIO_PinNumber );
			}
			else
			{
				//PxODR = 0 :Table 20. Port bit configuration table
				GPIOx->ODR &= ~(Pin_Config->GPIO_PinNumber);
			}
		}
	}
	// Write on CRH\CRL
	(*ConfigReg) |= ( ConfigPin << Get_CRLH_Position(Pin_Config->GPIO_PinNumber) );
}

/**================================================================
 * @Fn			- MCAL_GPIO_DeInit
 * @brief 		- Reset all GPIOx registers
 * @param [in]	- GPIOx: where x can be (A...E depending on the device used) to select the GPIO peripheral
 * @retval 		- None
 * Note			- None
 **================================================================*/
void MCAL_GPIO_DeInit(GPIO_TypeDef *GPIOx)
{

	//	GPIOx->CRL   = 0x44444444;
	//	GPIOx->CRH   = 0x44444444;
	//	GPIOx->IDR     (READ ONLY)
	//	GPIOx->ODR   = 0x00000000;
	//	GPIOx->BSRR  = 0x00000000;
	//	GPIOx->BRR   = 0x00000000;
	//	GPIOx->LCKR  = 0x00000000;


	//Using Reset Controller
	//APB2 peripheral reset register (RCC_APB2RSTR)
	//Set and cleared by software.

	if( GPIOx == GPIOA )
	{
		RCC->APB2RSTR |= ( 1<<2 );
		RCC->APB2RSTR &= ~( 1<<2 );
	}
	else if( GPIOx == GPIOB )
	{
		RCC->APB2RSTR |= ( 1<<3 );
		RCC->APB2RSTR &= ~( 1<<3 );
	}
	else if( GPIOx == GPIOC )
	{
		RCC->APB2RSTR |= ( 1<<4 );
		RCC->APB2RSTR &= ~( 1<<4 );
	}
	else if( GPIOx == GPIOD )
	{
		RCC->APB2RSTR |= ( 1<<5 );
		RCC->APB2RSTR &= ~( 1<<5 );
	}
	else if( GPIOx == GPIOE )
	{
		RCC->APB2RSTR |= ( 1<<6 );
		RCC->APB2RSTR &= ~( 1<<6 );
	}
}

/**================================================================
 * @Fn			- MCAL_GPIO_ReadPin
 * @brief 		- Read specific Pin value
 * @param [in]	- GPIOx: where x can be (A...E depending on the device used) to select the GPIO peripheral
 * @param [in]	- PinNumber: Set Pin number according to @ref GPIO_PINS_define
 * @retval 		- The input Pin value according to @ref GPIO_PIN_STATE_define
 * Note			- None
 **================================================================*/
uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16_t PinNumber)
{
	uint8_t bitstatus;

	if( ( (GPIOx->IDR & PinNumber) != (uint32_t)GPIO_PIN_STATE_RESET ) )
	{
		bitstatus = GPIO_PIN_STATE_SET;
	}
	else
	{
		bitstatus = GPIO_PIN_STATE_RESET;
	}

	return bitstatus;
}

/**================================================================
 * @Fn			- MCAL_GPIO_ReadPort
 * @brief 		- Read the whole Port value
 * @param [in]	- GPIOx: where x can be (A...E depending on the device used) to select the GPIO peripheral
 * @retval 		- The input Port value
 * Note			- None
 **================================================================*/
uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef *GPIOx)
{
	uint16_t portvalue;

	portvalue = (uint16_t) GPIOx->IDR;

	return portvalue;
}

/**================================================================
 * @Fn			- MCAL_GPIO_WritePin
 * @brief 		- Write on specific output Pin
 * @param [in]	- GPIOx: where x can be (A...E depending on the device used) to select the GPIO peripheral
 * @param [in]	- PinNumber: set pin number according to @ref GPIO_PINS_define
 * @param [in]	- Value: Pin value
 * @retval 		- None
 * Note			- None
 **================================================================*/
void MCAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t PinNumber, uint8_t Value)
{
	if( (Value != GPIO_PIN_STATE_RESET) )
	{
		//1)Write to Port output data register (GPIOx_ODR)
		//GPIOx->ODR |= PinNumber;

		//2)Write to Port bit set/reset register (GPIOx_BSRR)
		/*Bits 15:0 BSy: Port x Set bit y (y= 0 .. 15)
		 *These bits are write-only and can be accessed in Word mode only.
		 *0: No action on the corresponding ODRx bit
		 *1: Set the corresponding ODRx bit */

		GPIOx->BSRR = (uint32_t)PinNumber;
	}
	else
	{
		//1)Write to Port output data register (GPIOx_ODR)
		//GPIOx->ODR &= ~PinNumber;

		//2)Write to Port bit reset register (GPIOx_BRR)
		/*Bits 15:0 BRy: Port x Reset bit y (y= 0 .. 15)
		 *These bits are write-only and can be accessed in Word mode only.
		 *0: No action on the corresponding ODRx bit
		 *1: Reset the corresponding ODRx bit */

		GPIOx->BRR = (uint32_t)PinNumber;
	}

}

/**================================================================
 * @Fn			- MCAL_GPIO_WritePort
 * @brief 		- Write on specific output port
 * @param [in]	- GPIOx: where x can be (A...E depending on the device used) to select the GPIO peripheral
 * @param [in]	- Value: Port value
 * @retval 		- None
 * Note			- None
 **================================================================*/
void MCAL_GPIO_WritePort(GPIO_TypeDef *GPIOx, uint16_t Value)
{
	GPIOx->ODR = Value;
}

/**================================================================
 * @Fn			- MCAL_GPIO_TogglePin
 * @brief 		- Toggle a specific output pin
 * @param [in]	- GPIOx: where x can be (A...E depending on the device used) to select the GPIO peripheral
 * @param [in]	- PinNumber: Set Pin number according to @ref GPIO_PINS_define
 * @retval 		- None
 * Note			- None
 **================================================================*/
void MCAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t PinNumber)
{
	GPIOx->ODR ^= (PinNumber);
}

/**================================================================
 * @Fn			- MCAL_GPIO_LockPin
 * @brief 		- Lock a specific pin which allow the IO Configuration to be frozen
 * @param [in]	- GPIOx: where x can be (A...E depending on the device used) to select the GPIO peripheral
 * @param [in]	- PinNumber: set pin number according to @ref GPIO_PINS_define
 * @retval 		- OK if Pin is Locked or Error if pin is not locked (according to @ref GPIO_RETURN_LOCK_define)
 * Note			- None
 **================================================================*/
uint8_t MCAL_GPIO_LockPin(GPIO_TypeDef *GPIOx, uint16_t PinNumber)
{
	//	 Bit 16 LCKK[16]: Lock key
	//	 *This bit can be read any time. It can only be modified using the Lock Key Writing Sequence.
	//	 *0: Port configuration lock key not active
	//	 *1: Port configuration lock key active. GPIOx_LCKR register is locked until the next reset.
	//	 *LOCK key writing sequence:
	//	 *Write 1
	//	 *Write 0
	//	 *Write 1
	//	 *Read 0
	//	 *Read 1 (this read is optional but confirms that the lock is active)
	//	 *Note: During the LOCK Key Writing sequence, the value of LCK[15:0] must not change.
	//	 *Any error in the lock sequence will abort the lock.
	//	 *Bits 15:0 LCKy: Port x Lock bit y (y= 0 .. 15)
	//	 *These bits are read write but can only be written when the LCKK bit is 0.
	//	 *0: Port configuration not locked
	//	 *1: Port configuration locked.

	//set LCKK[16]
	volatile uint32_t temp = ( 1<<16 );
	//set LCKy
	temp |= PinNumber;

	//LOCK key writing sequence:
	//Write 1
	GPIOx->LCKR = temp;
	//Write 0
	GPIOx->LCKR &= ~( 1<<16 );
	//Write 1
	GPIOx->LCKR = temp;
	//Read 0
	temp = GPIOx->LCKR;

	//Read 1
	if(( (uint32_t)GPIOx->LCKR & (1<<16) ) )
	{
		return GPIO_RETURN_LOCK_ENABLED;
	}
	else
	{
		return GPIO_RETURN_LOCK_ERORR;
	}

}
