/*
 * Stm32f103c6_GPIO_Driver.h
 *
 *  Created on: Feb 28, 2023
 *      Author: Abdelaziz Maher
 */

#ifndef INC_STM32F103C6_GPIO_DRIVER_H_
#define INC_STM32F103C6_GPIO_DRIVER_H_

//-----------------------------------------------
//Includes
//-----------------------------------------------
#include "Stm32f103x6.h"



//-----------------------------------------------
//User type definitions (structures)
//-----------------------------------------------
typedef struct
{
	uint16_t GPIO_PinNumber; 	 //Specifies the GPIO Pins to be configured
							  	 //This parameter can be a value of @ref GPIO_PINS_define

	uint8_t GPIO_Mode;  	     //Specifies the GPIO Pins possible modes
							 	 //This parameter can be a value of @ref GPIO_PIN_MODE_define

	uint8_t GPIO_Output_Speed;   //Specifies the GPIO Pins output speed
								 //This parameter can be a value of @ref GPIO_PIN_SPEED_define

}GPIO_PinConfig_t;



//-----------------------------------------------
//Macros Configuration References
//-----------------------------------------------

//@ref GPIO_PIN_STATE_define
#define GPIO_PIN_STATE_SET						1
#define GPIO_PIN_STATE_RESET					0

//@ref GPIO_RETURN_LOCK_define
#define GPIO_RETURN_LOCK_ENABLED				1
#define GPIO_RETURN_LOCK_ERORR					0

//@ref GPIO_PINS_define

#define  GPIO_PIN_0								( ( uint16_t )0x0001 )   /*Pin 0 selected*/
#define  GPIO_PIN_1								( ( uint16_t )0x0002 )   /*Pin 1 selected*/
#define  GPIO_PIN_2								( ( uint16_t )0x0004 )   /*Pin 2 selected*/
#define  GPIO_PIN_3								( ( uint16_t )0x0008 )   /*Pin 3 selected*/
#define  GPIO_PIN_4								( ( uint16_t )0x0010 )   /*Pin 4 selected*/
#define  GPIO_PIN_5								( ( uint16_t )0x0020 )   /*Pin 5 selected*/
#define  GPIO_PIN_6								( ( uint16_t )0x0040 )   /*Pin 6 selected*/
#define  GPIO_PIN_7								( ( uint16_t )0x0080 )   /*Pin 7 selected*/
#define  GPIO_PIN_8								( ( uint16_t )0x0100 )   /*Pin 8 selected*/
#define  GPIO_PIN_9								( ( uint16_t )0x0200 )   /*Pin 9 selected*/
#define  GPIO_PIN_10							( ( uint16_t )0x0400 )   /*Pin 10 selected*/
#define  GPIO_PIN_11							( ( uint16_t )0x0800 )   /*Pin 11 selected*/
#define  GPIO_PIN_12							( ( uint16_t )0x1000 )   /*Pin 12 selected*/
#define  GPIO_PIN_13							( ( uint16_t )0x2000 )   /*Pin 13 selected*/
#define  GPIO_PIN_14							( ( uint16_t )0x4000 )   /*Pin 14 selected*/
#define  GPIO_PIN_15							( ( uint16_t )0x8000 )   /*Pin 15 selected*/

#define  GPIO_ALL_PINS							( ( uint16_t )0xFFFF )   /*All Pins selected*/
#define  GPIO_PIN_MASK                          ( 0x0000FFFFUL )   		 /*Pin MASK for assert test */

//@ref GPIO_PIN_MODE_define
/*
 0: Analog mode
 1: Floating input (reset state)
 2: Input with pull-up
 3: Input with pull-down
 4: General purpose output push-pull
 5: General purpose output Open-drain
 6: Alternate function output Push-pull
 7: Alternate function output Open-drain
 8: Alternate function input (Floating input)
 */

#define GPIO_PIN_MODE_Analog						(0x00000000UL)   /*Analog mode*/
#define GPIO_PIN_MODE_INPUT_FLOA					(0x00000001UL)   /*Floating input mode*/
#define GPIO_PIN_MODE_INPUT_PU						(0x00000002UL)   /*Input with pull-up mode*/
#define GPIO_PIN_MODE_INPUT_PD						(0x00000003UL)   /*Input with pull-down mode*/
#define GPIO_PIN_MODE_OUTPUT_PP						(0x00000004UL)   /*General purpose output push-pull mode*/
#define GPIO_PIN_MODE_OUTPUT_OD						(0x00000005UL)   /*General purpose output Open-drain mode*/
#define GPIO_PIN_MODE_ALTFN_OUTPUT_PP				(0x00000006UL)   /*Alternate function output Push-pull mode*/
#define GPIO_PIN_MODE_ALTFN_OUTPUT_OD				(0x00000007UL)   /*Alternate function output Open-drain mode*/
#define GPIO_PIN_MODE_ALTFN_INPUT			   	    (0x00000008UL)   /*Alternate function input mode*/

//@ref GPIO_PIN_SPEED_define
/*
 1: Output mode, max speed 10 MHz.
 2: Output mode, max speed 2 MHz.
 3: Output mode, max speed 50 MHz.
 */

#define GPIO_PIN_SPEED_10MHZ						(0x00000001UL)    /*max speed 10 MHz*/
#define GPIO_PIN_SPEED_2MHZ							(0x00000002UL)    /*max speed 2 MHz*/
#define GPIO_PIN_SPEED_50MHZ						(0x00000003UL)    /*max speed 50 MHz*/

/*
 * =======================================================================================
 *                         APIs Supported by "MCAL GPIO DRIVER"
 * =======================================================================================
 */

void MCAL_GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_PinConfig_t *Pin_Config);
void MCAL_GPIO_DeInit(GPIO_TypeDef *GPIOx);

uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16_t PinNumber);
uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef *GPIOx);

void MCAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t PinNumber, uint8_t Value);
void MCAL_GPIO_WritePort(GPIO_TypeDef *GPIOx, uint16_t Value);

void MCAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t PinNumber);
uint8_t MCAL_GPIO_LockPin(GPIO_TypeDef *GPIOx, uint16_t PinNumber);

#endif /* INC_STM32F103C6_GPIO_DRIVER_H_ */
