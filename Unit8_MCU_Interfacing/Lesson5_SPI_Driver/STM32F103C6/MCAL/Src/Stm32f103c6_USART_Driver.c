/*
 * Stm32f103c6_USART_Driver.c
 *
 *  Created on: Mar 27, 2023
 *      Author: Abdelaziz Maher
 */

#include"Stm32f103c6_USART_Driver.h"


/*
 * ======================================================================
 *                                          Generic variables
 *======================================================================
 */
UART_Config_t* Global_UART_Cfg[3] = {NULL,NULL,NULL} ;
UART_Config_t Global_UART_Cfg1 ;
UART_Config_t Global_UART_Cfg2 ;
UART_Config_t Global_UART_Cfg3 ;

void(* P_UART_IRQ_Callback_g[3])(struct sUART_IRQ_SRC irq_src);


/*
 *=======================================================================
 *						Generic MACROS
 *=======================================================================
 *
*/

#define UART1_Index				0
#define UART2_Index				1
#define UART3_Index				2

#define UART_PE_FLAG            ( 1<<1 )
#define UART_RXNE_FLAG          ( 1<<5 )
#define UART_TC_FLAG            ( 1<<6 )
#define UART_TXE_FLAG           ( 1<<7 )




/*
 * ======================================================================
 *                                          Generic Functions
 *======================================================================
 */






/*
 *-----------------------------------------------------------
 * 				APIs Functions Definitions
 *-----------------------------------------------------------
 */


/**================================================================
 * @Fn			- MCAL_UART_Init
 * @brief       -Initialize UART (Asynchronous Only)
 * @param [in]  -USARTx :Where x can be (1...3 depending on device used)
 * @param [in]  -UART_Cfg :All the UART configuration
 * @retval      -None
 * Note         -support for now ASynch mode and clock 8 HZ
 **================================================================*/
void MCAL_UART_Init(USART_TypeDef* USARTx,UART_Config_t* UART_Cfg)
{
	uint32_t pclk,BRR;

	//Enable the Clock for given USART Peripheral
	if( USARTx == USART1 )
	{
		Global_UART_Cfg1 = *UART_Cfg;
		Global_UART_Cfg[UART1_Index] = &Global_UART_Cfg1;

		RCC_USART1_CLK_ENABLE();
	}

	else if ( USARTx == USART2 )
	{
		Global_UART_Cfg2 = *UART_Cfg;
		Global_UART_Cfg[UART2_Index] = &Global_UART_Cfg2;

		RCC_USART2_CLK_ENABLE();
	}


	else if ( USARTx == USART3 )
	{
		Global_UART_Cfg3 = *UART_Cfg;
		Global_UART_Cfg[UART3_Index] = &Global_UART_Cfg3;

		RCC_USART3_CLK_ENABLE();
	}


	//Enable USART Module
	//Bit 13 UE: USART enable
	USARTx->CR1 |= (1<<13) ;

	//Mode TX-RX
	USARTx->CR1 |= UART_Cfg->USART_Mode ;

	// PayLoad width
	//Bit 12 M:Word length
	USARTx->CR1 |= UART_Cfg->PayLoad_Length ;

	//Parity Bits
	USARTx->CR1 |= UART_Cfg->Parity ;

	//Stop Bits
	USARTx->CR2 |= UART_Cfg->StopBits;

	//Hardware Flow Control
	USARTx->CR3 |= UART_Cfg->HwFlowCTRL ;

	//Configure baud rate
	//PCLK2 For USART1
	//PCLK1 for USART2 ,3
	if(USARTx == USART1)
		pclk = MCAL_RCC_GetPClk2Freq();
	else
		pclk = MCAL_RCC_GetPClk1Freq();

	BRR = UART_BRR_Register(pclk ,UART_Cfg->USART_BAUDRATE ) ;

	USARTx->BRR =BRR ;

	//Enable/Disable Interrupt
	if(UART_Cfg->IRQ_Enable != UART_IRQ_ENABLE_NONE)
	{
		USARTx->CR1 |= UART_Cfg->IRQ_Enable ;

		//enable NVIC for USART IRQ
		if(USARTx == USART1)
		{
			NVIC_IRQ37_USART1_ENABLE();
			P_UART_IRQ_Callback_g[0] = UART_Cfg->P_IRQ_CallBack;
		}


		else if (USARTx == USART2)
		{
			NVIC_IRQ38_USART2_ENABLE();
			P_UART_IRQ_Callback_g[1] = UART_Cfg->P_IRQ_CallBack;
		}


		else if (USARTx == USART3)
		{
			NVIC_IRQ39_USART3_ENABLE();
			P_UART_IRQ_Callback_g[2] = UART_Cfg->P_IRQ_CallBack;
		}

	}
}

/**================================================================
 * @Fn			- MCAL_UART_DeInit
 * @brief 		- Initialize EXTI from specific GPIO PIN and specify the Mask/Trigger Conditions and IRQ Callback
 * @param [in]	- USARTx :Where x can be (1...3 depending on device used)
 * @retval 		- None
 * Note			- STM32F103C6 MCU has GPIO A,B,C,D,E modules
 * 				  but LQFP48 package has only GPIO A,B, part of C/D exported as external Pins from the modules
 * 				- Also Mandatory to Enable RCC Clock for AFIO and the Corresponding GPIO
 **================================================================*/
void MCAL_UART_DeInit(USART_TypeDef * USARTx)
{
	if(USARTx == USART1)
	{
		RCC_USART1_RESET();
		NVIC_IRQ37_USART1_DISABLE();
	}

	else if (USARTx == USART2)
	{
		RCC_USART2_RESET();
		NVIC_IRQ38_USART2_DISABLE();
	}

	else if (USARTx == USART3)
	{
		RCC_USART3_RESET();
		NVIC_IRQ39_USART3_DISABLE();
	}
}

/**================================================================
 * @Fn			- MCAL_UART_GPIO_SetPins
 * @brief 		- Initialize GPIO pins for UART
 * @param [in]	- USARTx :Where x can be (1...3 depending on device used)
 * @retval 		- None
 * Note			- Should Enable the corresponding GPIO/AFIO In RCC
 **================================================================*/
void MCAL_UART_GPIO_SetPins(USART_TypeDef * USARTx)
{
	GPIO_PinConfig_t PinCfg;
	if(USARTx == USART1)
	{
		//from alternative pin table for LQF and see recommended gpio pins configuration table
		//PA9 TX
		//PA10 RX
		//PA11 CTS
		//PA12 RTS

		//PA9 TX
		PinCfg.GPIO_PinNumber = GPIO_PIN_9 ;
		PinCfg.GPIO_Mode = GPIO_PIN_MODE_ALTFN_OUTPUT_PP;
		PinCfg.GPIO_Output_Speed = GPIO_PIN_SPEED_10MHZ;
		MCAL_GPIO_Init(GPIOA, &PinCfg) ;

		//PA10 RX
		PinCfg.GPIO_PinNumber = GPIO_PIN_10 ;
		PinCfg.GPIO_Mode = GPIO_PIN_MODE_INPUT_FLOA;
		MCAL_GPIO_Init(GPIOA, &PinCfg) ;

		//PA11 CTS
		if(Global_UART_Cfg[UART1_Index]->HwFlowCTRL == UART_HwFlowCTL_CTS || Global_UART_Cfg[UART1_Index]->HwFlowCTRL == UART_HwFlowCTL_RTS_CTS)
		{
			PinCfg.GPIO_PinNumber = GPIO_PIN_11 ;
			PinCfg.GPIO_Mode = GPIO_PIN_MODE_INPUT_FLOA;
			MCAL_GPIO_Init(GPIOA, &PinCfg) ;
		}

		//PA12 RTS
		if(Global_UART_Cfg[UART1_Index]->HwFlowCTRL == UART_HwFlowCTL_RTS || Global_UART_Cfg[UART1_Index]->HwFlowCTRL == UART_HwFlowCTL_RTS_CTS)
		{
			PinCfg.GPIO_PinNumber = GPIO_PIN_12 ;
			PinCfg.GPIO_Mode = GPIO_PIN_MODE_ALTFN_OUTPUT_PP;
			PinCfg.GPIO_Output_Speed = GPIO_PIN_SPEED_10MHZ;
			MCAL_GPIO_Init(GPIOA, &PinCfg) ;
		}
	}
	if(USARTx == USART2)
	{
		//from alternative pin table for LQF and see recommended gpio pins configuration table
		//PA2 TX
		//PA3 RX
		//PA0 CTS
		//PA1 RTS

		//PA2 TX
		PinCfg.GPIO_PinNumber = GPIO_PIN_2 ;
		PinCfg.GPIO_Mode = GPIO_PIN_MODE_ALTFN_OUTPUT_PP;
		PinCfg.GPIO_Output_Speed = GPIO_PIN_SPEED_10MHZ;
		MCAL_GPIO_Init(GPIOA, &PinCfg) ;

		//PA3 RX
		PinCfg.GPIO_PinNumber = GPIO_PIN_3 ;
		PinCfg.GPIO_Mode = GPIO_PIN_MODE_INPUT_FLOA;
		MCAL_GPIO_Init(GPIOA, &PinCfg) ;

		//PA0 CTS
		if(Global_UART_Cfg[UART2_Index]->HwFlowCTRL == UART_HwFlowCTL_CTS || Global_UART_Cfg[UART2_Index]->HwFlowCTRL == UART_HwFlowCTL_RTS_CTS)
		{
			PinCfg.GPIO_PinNumber = GPIO_PIN_0 ;
			PinCfg.GPIO_Mode = GPIO_PIN_MODE_INPUT_FLOA;
			MCAL_GPIO_Init(GPIOA, &PinCfg) ;

		}

		//PA1 RTS
		if(Global_UART_Cfg[UART2_Index]->HwFlowCTRL == UART_HwFlowCTL_RTS || Global_UART_Cfg[UART2_Index]->HwFlowCTRL == UART_HwFlowCTL_RTS_CTS)
		{
			PinCfg.GPIO_PinNumber = GPIO_PIN_1 ;
			PinCfg.GPIO_Mode = GPIO_PIN_MODE_ALTFN_OUTPUT_PP;
			PinCfg.GPIO_Output_Speed = GPIO_PIN_SPEED_10MHZ;
			MCAL_GPIO_Init(GPIOA, &PinCfg) ;
		}
	}
	if(USARTx == USART3)
	{
		//from alternative pin table for LQF and see recommended gpio pins configuration table
		//PB10 TX
		//PB11 RX
		//PB13 CTS
		//PA14 RTS

		//PB10 TX
		PinCfg.GPIO_PinNumber = GPIO_PIN_10 ;
		PinCfg.GPIO_Mode = GPIO_PIN_MODE_ALTFN_OUTPUT_PP;
		PinCfg.GPIO_Output_Speed = GPIO_PIN_SPEED_10MHZ;
		MCAL_GPIO_Init(GPIOA, &PinCfg) ;

		//PB11 RX
		PinCfg.GPIO_PinNumber = GPIO_PIN_11 ;
		PinCfg.GPIO_Mode = GPIO_PIN_MODE_INPUT_FLOA;
		MCAL_GPIO_Init(GPIOA, &PinCfg) ;

		//PB13 CTS
		if(Global_UART_Cfg[UART3_Index]->HwFlowCTRL == UART_HwFlowCTL_CTS || Global_UART_Cfg[UART3_Index]->HwFlowCTRL == UART_HwFlowCTL_RTS_CTS)
		{
			PinCfg.GPIO_PinNumber = GPIO_PIN_13 ;
			PinCfg.GPIO_Mode = GPIO_PIN_MODE_INPUT_FLOA;
			MCAL_GPIO_Init(GPIOA, &PinCfg) ;
		}

		//PA14 RTS
		if(Global_UART_Cfg[UART3_Index]->HwFlowCTRL == UART_HwFlowCTL_RTS || Global_UART_Cfg[UART3_Index]->HwFlowCTRL == UART_HwFlowCTL_RTS_CTS)
		{
			PinCfg.GPIO_PinNumber = GPIO_PIN_14 ;
			PinCfg.GPIO_Mode = GPIO_PIN_MODE_ALTFN_OUTPUT_PP;
			PinCfg.GPIO_Output_Speed = GPIO_PIN_SPEED_10MHZ;
			MCAL_GPIO_Init(GPIOA, &PinCfg) ;
		}
	}
}

/**================================================================
 * @Fn			- MCAL_UART_SendData
 * @brief 		- Send Data Buffer on UART
 * @param [in]	- USARTx :Where x can be (1...3 depending on device used)
 * @param [in]	- pTXBuffer: The Data Buffer that will be transmitted
 * @param [in]	- PollingEn: Enable or Disable UART polling
 * @retval 		- None
 * Note			- Should Initialize UART first
 **================================================================*/
void MCAL_UART_SendData(USART_TypeDef * USARTx , uint16_t * pTXBuffer , enum UART_Polling_mechism PollingEn)
{
    uint8_t index;

	if( USARTx == USART1 )
		index = UART1_Index;
	else if ( USARTx == USART2 )
		index = UART2_Index;
	else if ( USARTx == USART3 )
		index = UART3_Index;

	//Wait Until TXE is set in SR
	if ( PollingEn == UART_ENABLE )
		while(! ( USARTx->SR & ( UART_TXE_FLAG ) ) );

	//Check the data Word length ( 9BIT - 8BIT) Frame
	//	When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
	//	the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
	//	because it is replaced by the parity->
	//	When receiving with the parity enabled, the value read in the MSB bit is the received parity bit
	if( Global_UART_Cfg[index]->PayLoad_Length == UART_PayLoad_Length_9bit )
	{
		USARTx->DR = ( *pTXBuffer & (uint16_t)0x01FF );
	}
	else
	{
		USARTx->DR = ( *pTXBuffer & (uint16_t)0xFF );
	}

}

/**================================================================
 * @Fn			- MCAL_UART_ReceiveData
 * @brief 		- Receive Data Buffer on UART
 * @param [in]	- USARTx :Where x can be (1...3 depending on device used)
 * @param [in]	- pRXBuffer: The Data Buffer that will be Received
 * @param [in]	- PollingEn: Enable or Disable UART polling
 * @retval 		- None
 * Note			- Should Initialize UART first
 **================================================================*/
void MCAL_UART_ReceiveData(USART_TypeDef * USARTx,uint16_t * pRXBuffer , enum UART_Polling_mechism PollingEn)
{

    uint8_t index;

	if( USARTx == USART1 )
		index = UART1_Index;
	else if ( USARTx == USART2 )
		index = UART2_Index;
	else if ( USARTx == USART3 )
		index = UART3_Index;


	//Wait Until RXNE is set in SR
	if ( PollingEn == UART_ENABLE )
		while(! ( USARTx->SR & ( UART_RXNE_FLAG ) ) );

	//Check the data Word length ( 9BIT - 8BIT) Frame
	if( Global_UART_Cfg[index]->PayLoad_Length == UART_PayLoad_Length_9bit )
	{
		if(Global_UART_Cfg[index]->Parity == UART_Parity_NONE)
		{
			//No Parity so all 9bits are data
			*( (uint16_t*)pRXBuffer ) = USARTx->DR ;

		}
		else
		{
			//Parity is used, 8bit is data and the last one is parity
			*( (uint16_t*)pRXBuffer ) =( USARTx->DR & (uint8_t)0xFF );
		}
	}

	else //8 bit data
	{
		if(Global_UART_Cfg[index]->Parity == UART_Parity_NONE)
		{
			//no parity so all 8bits are data
			*( (uint16_t*)pRXBuffer ) = (USARTx->DR   & (uint8_t)0xFF );

		}
		else
		{
			//Parity is used, 7bit is data and the last one is parity
			*( (uint16_t*)pRXBuffer ) =( USARTx->DR & (uint8_t)0x7F );
		}
	}
}

/**================================================================
 * @Fn			- MCAL_UART_WAIT_TC
 * @brief 		- Initialize EXTI from specific GPIO PIN and specify the Mask/Trigger Conditions and IRQ Callback
 * @param [in]	- USARTx :Where x can be (1...3 depending on device used)
 * @retval 		- None
 * Note			- None
 **================================================================*/
void MCAL_UART_WAIT_TC (USART_TypeDef * USARTx)
{
	//Wait Until TXE is set in SR
	while(! ( USARTx->SR & ( UART_TC_FLAG ) ) );
}



/*
* =======================================================================================
* =======================================================================
* ======================        ISR FUNCTIONS                 ==============================
* =======================================================================================
*/

void USART1_IRQHandler(void)
{
	struct sUART_IRQ_SRC irq_src;

	irq_src.PE    = ( ( USART1->SR & (UART_PE_FLAG) )   >> 1   );
	irq_src.RXNE  = ( ( USART1->SR & (UART_RXNE_FLAG) ) >> 5   );
	irq_src.TC    = ( ( USART1->SR & (UART_TC_FLAG) )   >> 6   );
	irq_src.TXE   = ( ( USART1->SR & (UART_TXE_FLAG) )  >> 7   );

	P_UART_IRQ_Callback_g[0](irq_src);
}

void USART2_IRQHandler(void)
{
	struct sUART_IRQ_SRC irq_src;

	irq_src.PE    = ( ( USART2->SR & (UART_PE_FLAG) )   >> 1   );
	irq_src.RXNE  = ( ( USART2->SR & (UART_RXNE_FLAG) ) >> 5   );
	irq_src.TC    = ( ( USART2->SR & (UART_TC_FLAG) )   >> 6   );
	irq_src.TXE   = ( ( USART2->SR & (UART_TXE_FLAG) )  >> 7   );

	P_UART_IRQ_Callback_g[1](irq_src);
}

void USART3_IRQHandler(void)
{
	struct sUART_IRQ_SRC irq_src;

	irq_src.PE    = ( ( USART3->SR & (UART_PE_FLAG) )   >> 1   );
	irq_src.RXNE  = ( ( USART3->SR & (UART_RXNE_FLAG) ) >> 5   );
	irq_src.TC    = ( ( USART3->SR & (UART_TC_FLAG) )   >> 6   );
	irq_src.TXE   = ( ( USART3->SR & (UART_TXE_FLAG) )  >> 7   );

	P_UART_IRQ_Callback_g[2](irq_src);
}
