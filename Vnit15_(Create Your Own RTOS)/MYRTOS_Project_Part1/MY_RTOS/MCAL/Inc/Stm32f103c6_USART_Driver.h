/*
 * Stm32f103c6_USART_Driver.h
 *
 *  Created on: Mar 27, 2023
 *      Author: Abdelaziz Maher
 */

#ifndef INC_STM32F103C6_USART_DRIVER_H_
#define INC_STM32F103C6_USART_DRIVER_H_

//-----------------------------------------------
//Includes
//-----------------------------------------------
#include"Stm32f103x6.h"
#include"Stm32f103c6_GPIO_Driver.h"
#include"Stm32f103c6_RCC_Driver.h"



/*
 *----------------------------------------------------------
 * 				  Generic Macros
 *----------------------------------------------------------
 */





//-----------------------------------------------
//User type definitions (structures)
//-----------------------------------------------

struct sUART_IRQ_SRC
{
	uint8_t TXE:1;        //TX Buffer Empty interrupt means write new date
	uint8_t RXNE:1;       //RX Buffer Not Empty interrupt means read it
	uint8_t TC:1;         //Transmission complete interrupt
	uint8_t PE:1;         //Parity Error interrupt
	uint8_t RESERVED:4;
};


typedef struct
{
	uint8_t			USART_Mode;    									//Specifies RX-TX Enable /Disable
																	//This parameter must be set based on @ref UART_MODE_Define

	uint32_t 		USART_BAUDRATE; 								//Specifies UART communication Baudrate
																	//This parameter must be set based on @ref UART_BAUDRATE_Define

	uint8_t 		PayLoad_Length;									//Specifies the number of data bits transmitted or received in a frame
																	//This parameter must be set based on @ref UART_PayLoad_Length_Define

	uint8_t			Parity;											//Specifies Parity
																	//This parameter must be set based on @ref UART_Parity_Define

	uint8_t 		StopBits;										//Specifies The Number of Stop Bits
																	//This parameter must be set based on @ref UART_StopBits_Define

	uint8_t 		HwFlowCTRL;										//Specifies Whether Flow Control is Enabled or not
																	//This parameter must be set based on @ref UART_HwFlowCTRL_Define

	uint8_t			IRQ_Enable;										//Specifies if RX or Tx Interrupt is Enabled or Disabled
																	//This parameter must be set based on @ref UART_IRQ_ENABLE_Define

	void(*P_IRQ_CallBack)(struct sUART_IRQ_SRC irq_src);			//Set the C Function() that will be called when the Interrupt Happens

}UART_Config_t;


//-----------------------------------------------
//Macros Configuration References
//-----------------------------------------------
//@ref UART_MODE_Define
#define UART_MODE_RX							(uint32_t)( 1 << 2) //Bit 2 RE: Receiver enable
#define UART_MODE_TX							(uint32_t)( 1 << 3 ) //Bit 3 TE: Transmitter enable
#define UART_MODE_RXTX							( (uint32_t)( 1<<2 | 1<<3 ) ) //Transmitter & Receiver Enable

//@ref UART_BAUDRATE_Define
#define UART_BAUDRATE_2400						2400
#define UART_BAUDRATE_9600						9600
#define UART_BAUDRATE_19200						19200
#define UART_BAUDRATE_57600						57600
#define UART_BAUDRATE_115200					115200
#define UART_BAUDRATE_230400					230400
#define UART_BAUDRATE_460800					460800
#define UART_BAUDRATE_921600					921600
#define UART_BAUDRATE_2250000					2250000
#define UART_BAUDRATE_4500000					4500000

//@ref UART_PayLoad_Length_Define
#define UART_PayLoad_Length_8bit				(uint32_t)(0)
#define UART_PayLoad_Length_9bit				(uint32_t)( 1 << 12 )

//@ref UART_Parity_Define
#define UART_Parity_NONE						(uint32_t)(0)
#define UART_Parity_EVEN						(uint32_t)( 1<<10 )
#define UART_Parity_ODD							( (uint32_t)( 1<<10 | 1<<9 ) )

//@ref UART_Stop_Bits_Define
#define UART_StopBits_HALF						(uint32_t)( 1 << 12 )
#define UART_StopBits_1							(uint32_t)(0)
#define UART_StopBits_1_HALF					(uint32_t)( 3 << 12 )
#define UART_StopBits_2							(uint32_t)( 2 << 12 )

//@ref UART_HwFlowCTRL_Define
#define UART_HwFlowCTL_NONE						(uint32_t)(0)
#define UART_HwFlowCTL_RTS						(uint32_t)( 1 << 8  )
#define UART_HwFlowCTL_CTS						(uint32_t)( 1 << 9 )
#define UART_HwFlowCTL_RTS_CTS					( (uint32_t)( 1<<8 | 1<<9 ) )

//@ref UART_IRQ_ENABLE_Define
#define UART_IRQ_ENABLE_NONE					(uint32_t)(0)
#define UART_IRQ_ENABLE_TXE						(uint32_t)( 1<<7 )
#define UART_IRQ_ENABLE_TC						(uint32_t)( 1<<6 )
#define UART_IRQ_ENABLE_RXNEIE					(uint32_t)( 1<<5 )
#define UART_IRQ_ENABLE_PE						(uint32_t)( 1<<8 )

enum UART_Polling_mechism {
	UART_ENABLE,
	UART_DISABLE
};


//Baudrate calculation
//USARTDIV = fclk /(16*Baudrate)
//USARTDIV_Mul100  = (uint32)(100*fclk)/(16*Baudrate)
//USARTDIV_Mul100  = (uint32)(25*fclk)/(4*Baudrate)
//DIV_Mantissa_MUL100 = Integar part (USARTDIV) *100
//DIV_Mantissa = Integar part (USARTDIV)
//DIV_Fraction = ((USARTDIV_Mul100 - DIV_Mantissa_MUL100 ) * 16 )/100)

#define USARTDIV(_PCLK_,_BAUD_)         		  (uint32_t)(_PCLK_/(16 * _BAUD_))
#define USARTDIV_Mul100(_PCLK_,_BAUD_)            (uint32_t)((25 * _PCLK_)/(4 * _BAUD_))
#define Mantissa_MUL100(_PCLK_,_BAUD_)            (uint32_t) (USARTDIV(_PCLK_,_BAUD_) * 100)
#define Mantissa(_PCLK_,_BAUD_)                   (uint32_t) (USARTDIV(_PCLK_,_BAUD_))
#define DIV_Fraction(_PCLK_,_BAUD_)               (uint32_t) (( USARTDIV_Mul100(_PCLK_,_BAUD_)  - Mantissa_MUL100(_PCLK_,_BAUD_)) * 16 )
#define UART_BRR_Register(_PCLK_,_BAUD_)          ( (Mantissa(_PCLK_,_BAUD_)) <<4 ) | ( (DIV_Fraction(_PCLK_,_BAUD_)) & 0xF)




/*
 * =======================================================================================
 *                         APIs Supported by "MCAL USART DRIVER"
 * =======================================================================================
 */

/*** Initialization/De-Initialization Functions***/
void MCAL_UART_Init(USART_TypeDef* USARTx,UART_Config_t* UART_Cfg);
void MCAL_UART_DeInit(USART_TypeDef * USARTx);


void MCAL_UART_GPIO_SetPins(USART_TypeDef * USARTx);
void MCAL_UART_SendData(USART_TypeDef * USARTx , uint16_t * pTXBuffer , enum UART_Polling_mechism PollingEn);
void MCAL_UART_ReceiveData(USART_TypeDef * USARTx,uint16_t * pRXBuffer , enum UART_Polling_mechism PollingEn);
void MCAL_UART_WAIT_TC (USART_TypeDef * USARTx);






#endif /* INC_STM32F103C6_USART_DRIVER_H_ */
