/*
 * Stm32f103c6_EXTI_Driver.c
 *
 *  Created on: Mar 1, 2023
 *      Author: Abdelaziz Maher
 */


#include "Stm32f103c6_EXTI_Driver.h"


/*
 *----------------------------------------------------------
 * 				  Generic Variables
 *----------------------------------------------------------
 */

void(* P_IRQ_Callback_g[16])(void);

/*
 *----------------------------------------------------------
 * 				  Generic Macros
 *----------------------------------------------------------
 */

#define AFIO_EXTI_GPIO_Mapping(x)              ( x == GPIOA ? 0:\
		                                         x == GPIOB ? 1:\
		                                         x == GPIOC ? 2:\
		                                         x == GPIOD ? 3:0 )

/*
 *-----------------------------------------------------------
 * 				  Generic Functions
 *-----------------------------------------------------------
 */

void Enable_NVIC(uint16_t IRQ)
{
	switch(IRQ)
	{
	case 0:
		NVIC_IRQ6_EXTI0_ENABLE();
		break;

	case 1:
		NVIC_IRQ7_EXTI1_ENABLE();
		break;

	case 2:
		NVIC_IRQ8_EXTI2_ENABLE();
		break;

	case 3:
		NVIC_IRQ9_EXTI3_ENABLE();
		break;

	case 4:
		NVIC_IRQ10_EXTI4_ENABLE();
		break;

	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_EXTI5_9_ENABLE();
		break;

	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ40_EXTI10_15_ENABLE();
		break;
	}
}

void Disable_NVIC(uint16_t IRQ)
{
	switch(IRQ)
	{
	case 0:
		NVIC_IRQ6_EXTI0_DISABLE();
		break;

	case 1:
		NVIC_IRQ7_EXTI1_DISABLE();
		break;

	case 2:
		NVIC_IRQ8_EXTI2_DISABLE();
		break;

	case 3:
		NVIC_IRQ9_EXTI3_DISABLE();
		break;

	case 4:
		NVIC_IRQ10_EXTI4_DISABLE();
		break;

	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_EXTI5_9_DISABLE();
		break;

	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ40_EXTI10_15_DISABLE();
		break;
	}
}


void Update_EXTI(EXTI_Pinconfig_t* EXTI_config)
{
	//1 Configure GPIO to be AF Input->Floating Input
	GPIO_PinConfig_t PinCfg;

	PinCfg.GPIO_Mode = GPIO_PIN_MODE_INPUT_FLOA;
	PinCfg.GPIO_PinNumber = EXTI_config->EXTI_PIN.GPIO_PIN;

	MCAL_GPIO_Init( EXTI_config->EXTI_PIN.GPIO_Port , &PinCfg );

	//2 Update AFIO to Route Between EXTI Line with PORT A,B,C,D
	uint8_t AFIO_EXTICR_Index = EXTI_config->EXTI_PIN.EXTI_InputLineNumber / 4;
	uint8_t AFIO_EXTICR_Pos = ( EXTI_config->EXTI_PIN.EXTI_InputLineNumber % 4 ) * 4;

	//Clear Then Set The 4 bits
	AFIO->EXTICR[AFIO_EXTICR_Index] &= ~( 0xF << AFIO_EXTICR_Pos );
	AFIO->EXTICR[AFIO_EXTICR_Index] |= ( ( AFIO_EXTI_GPIO_Mapping(EXTI_config->EXTI_PIN.GPIO_Port) & 0x0F ) << AFIO_EXTICR_Pos );

	//3 Update Falling and Rising Edge
	EXTI->FTSR &= ~(1 << EXTI_config->EXTI_PIN.EXTI_InputLineNumber );
	EXTI->RTSR &= ~(1 << EXTI_config->EXTI_PIN.EXTI_InputLineNumber );

	if(EXTI_config->Trigger_Case == EXTI_Trigger_RISING )
	{
		EXTI->RTSR |= (1 << EXTI_config->EXTI_PIN.EXTI_InputLineNumber );
	}
	else if( EXTI_config->Trigger_Case == EXTI_Trigger_FALLING )
	{
		EXTI->FTSR |= (1 << EXTI_config->EXTI_PIN.EXTI_InputLineNumber );
	}
	else if( EXTI_config->Trigger_Case == EXTI_Trigger_RisingANDFalling )
	{
		EXTI->FTSR |= (1 << EXTI_config->EXTI_PIN.EXTI_InputLineNumber );
		EXTI->RTSR |= (1 << EXTI_config->EXTI_PIN.EXTI_InputLineNumber );
	}

	//4 Update IRQ Handling CALLBACK
	P_IRQ_Callback_g[EXTI_config->EXTI_PIN.EXTI_InputLineNumber] = EXTI_config->P_IRQ_Callback;

	//5 Enable/Disable IRQ & NVIC
	if(EXTI_config->IRQ_EN == EXTI_IRQ_ENABLE)
		{
			//Enable Interrupt Mask Register
			EXTI->IMR |= 1<<EXTI_config->EXTI_PIN.EXTI_InputLineNumber;

			//Enable NVIC
			Enable_NVIC(EXTI_config->EXTI_PIN.EXTI_InputLineNumber);
		}
		else if(EXTI_config->IRQ_EN == EXTI_IRQ_DISABLE)
		{
			//Disable Interrupt Mask Register
			EXTI->IMR &= ~(1<<EXTI_config->EXTI_PIN.EXTI_InputLineNumber);

			//Disable NVIC
			Disable_NVIC(EXTI_config->EXTI_PIN.EXTI_InputLineNumber);
		}
}

/*
 *-----------------------------------------------------------
 * 				APIs Functions Definitions
 *-----------------------------------------------------------
 */


/**================================================================
 * @Fn			- MCAL_EXTI_GPIO_INIT
 * @brief 		- Initialize EXTI from specific GPIO PIN and specify the Mask/Trigger Conditions and IRQ Callback
 * @param [in]	- EXTI_Config: Set by @ref EXTI_define, EXTI_Trigger_define and EXTI_IRQ_define
 * @retval 		- None
 * Note			- STM32F103C6 MCU has GPIO A,B,C,D,E modules
 * 				  but LQFP48 package has only GPIO A,B, part of C/D exported as external Pins from the modules
 * 				- Also Mandatory to Enable RCC Clock for AFIO and the Corresponding GPIO
 **================================================================*/
void MCAL_EXTI_GPIO_INIT(EXTI_Pinconfig_t* EXTI_config)
{
	Update_EXTI(EXTI_config);
}


/**================================================================
 * @Fn			- MCAL_EXTI_GPIO_DEINIT
 * @brief 		- Reset EXTI registers and NVIC Corresponding IRQ Mask
 * @param [in]	- None
 * @retval 		- None
 * Note			- None
 **================================================================*/
void MCAL_EXTI_GPIO_DEINIT(void)
{
	EXTI->IMR   = 0x00000000;
	EXTI->EMR   = 0x00000000;
	EXTI->RTSR  = 0x00000000;
	EXTI->FTSR  = 0x00000000;
	EXTI->SWIER = 0x00000000;
	//rc_w1 cleared by writing a '1' into the PR
	EXTI->PR    = 0xFFFFFFFF;

	//Disable EXTI IRQ From NVIC
	NVIC_IRQ6_EXTI0_DISABLE();
	NVIC_IRQ7_EXTI1_DISABLE();
	NVIC_IRQ8_EXTI2_DISABLE();
	NVIC_IRQ9_EXTI3_DISABLE();
	NVIC_IRQ10_EXTI4_DISABLE();
	NVIC_IRQ23_EXTI5_9_DISABLE();
	NVIC_IRQ40_EXTI10_15_DISABLE();
}

/**================================================================
 * @Fn			- MCAL_EXTI_GPIO_UPDATE
 * @brief 		- Initialize EXTI from specific GPIO PIN and specify the Mask/Trigger Conditions and IRQ Callback
 * @param [in]	- EXTI_Config: Set by @ref EXTI_define, EXTI_Trigger_define and EXTI_IRQ_define
 * @retval 		- None
 * Note			- STM32F103C6 MCU has GPIO A,B,C,D,E modules
 * 				  but LQFP48 package has only GPIO A,B, part of C/D exported as external Pins from the modules
 * 				- Also Mandatory to Enable RCC Clock for AFIO and the Corresponding GPIO
 **================================================================*/
void MCAL_EXTI_GPIO_UPDATE(EXTI_Pinconfig_t* EXTI_config)
{
	Update_EXTI(EXTI_config);
}



/*
* =======================================================================================
* =======================================================================
* ======================        ISR FUNCTIONS                 ==============================
* =======================================================================================
*/

void EXTI0_IRQHandler()
{
	EXTI->PR |= ( 1 << 0 );

	P_IRQ_Callback_g[0]();
}

void EXTI1_IRQHandler(void)
{
	EXTI->PR |= 1<<1;
	P_IRQ_Callback_g[1]();
}

void EXTI2_IRQHandler(void)
{
	EXTI->PR |= 1<<2;
	P_IRQ_Callback_g[2]();
}

void EXTI3_IRQHandler(void)
{
	EXTI->PR |= 1<<3;
	P_IRQ_Callback_g[3]();
}

void EXTI4_IRQHandler(void)
{
	EXTI->PR |= 1<<4;
	P_IRQ_Callback_g[4]();
}

void EXTI9_5_IRQHandler(void)
{
	if( EXTI->PR & 1<<5 ) { EXTI->PR |= 1<<5 ; P_IRQ_Callback_g[5](); };
	if( EXTI->PR & 1<<6 ) { EXTI->PR |= 1<<6 ; P_IRQ_Callback_g[6](); };
	if( EXTI->PR & 1<<7 ) { EXTI->PR |= 1<<7 ; P_IRQ_Callback_g[7](); };
	if( EXTI->PR & 1<<8 ) { EXTI->PR |= 1<<8 ; P_IRQ_Callback_g[8](); };
	if( EXTI->PR & 1<<9 ) { EXTI->PR |= 1<<9 ; P_IRQ_Callback_g[9](); };
}

void EXTI15_10_IRQHandler(void)
{
	if( EXTI->PR & 1<<10 ) { EXTI->PR |= 1<<10 ; P_IRQ_Callback_g[10](); };
	if( EXTI->PR & 1<<11 ) { EXTI->PR |= 1<<11 ; P_IRQ_Callback_g[11](); };
	if( EXTI->PR & 1<<12 ) { EXTI->PR |= 1<<12 ; P_IRQ_Callback_g[12](); };
	if( EXTI->PR & 1<<13 ) { EXTI->PR |= 1<<13 ; P_IRQ_Callback_g[13](); };
	if( EXTI->PR & 1<<14 ) { EXTI->PR |= 1<<14 ; P_IRQ_Callback_g[14](); };
	if( EXTI->PR & 1<<15 ) { EXTI->PR |= 1<<15 ; P_IRQ_Callback_g[15](); };
}
