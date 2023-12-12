/*
 * Stm32f103c6_SPI_Driver.c
 *
 *  Created on: Mar 30, 2023
 *      Author: Abdelaziz Maher
 */


#include"Stm32f103c6_SPI_Driver.h"

/*
 * ======================================================================
 *                                          Generic variables
 *======================================================================
 */
SPI_Config_t* Global_SPI_Cfg[2]={NULL,NULL};
SPI_Config_t Global_SPI_Cfg1 ;
SPI_Config_t Global_SPI_Cfg2 ;


void(* P_SPI_IRQ_Callback_g[2])(struct sSPI_IRQ_SRC irq_src);


/*
 *=======================================================================
 *						Generic MACROS
 *=======================================================================
 *
*/

#define SPI1_INDEX             	 0
#define SPI2_INDEX            	 1

#define SPI_TXE_FLAG             ( 1<<1 )
#define SPI_RXNE_FLAG            ( 1<<0 )
#define SPI_ERRI_FLAG            ( 1<<4 )




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
 * @Fn			- MCAL_SPI_Init
 * @brief       -Initialize SPI
 * @param [in]  -SPIx :Where x can be (1...2 depending on device used)
 * @param [in]  -SPI_Config :All the SPI configuration
 * @retval      -None
 * Note         -Support for SPI Full Duplex Master/Slave Only & NSS HW/SW
 **================================================================*/
void MCAL_SPI_Init(SPI_TypeDef* SPIx,SPI_Config_t* SPI_Cfg)
{
	//Safety for registers
	uint16_t tempreg_CR1 = 0;
	uint16_t tempreg_CR2 = 0;

	//Check The number of SPIx
	if(SPIx == SPI1)
	{
		Global_SPI_Cfg1 = *SPI_Cfg;
		Global_SPI_Cfg[SPI1_INDEX] = &Global_SPI_Cfg1;
		RCC_SPI1_CLK_ENABLE();

	}
	else if(SPIx == SPI2)
	{
		Global_SPI_Cfg2 = *SPI_Cfg;
		Global_SPI_Cfg[SPI2_INDEX] = &Global_SPI_Cfg2;
		RCC_SPI2_CLK_ENABLE();
	}

	//Set Bit 6 SPE: SPI enable
	tempreg_CR1 = ( 1<<6 );

	//Master or Salve
	tempreg_CR1 |= SPI_Cfg->Device_Mode;

	//SPI Communication_Mode
	tempreg_CR1 |= SPI_Cfg->Communication_Mode;

	//SPI Frame_Format
	tempreg_CR1 |= SPI_Cfg->Frame_Format;

	//SPI Date_Size
	tempreg_CR1 |= SPI_Cfg->Date_Size;

	//SPI CLK_Polarity
	tempreg_CR1 |= SPI_Cfg->CLK_Polarity;

	//SPI CLK_Phase
	tempreg_CR1 |= SPI_Cfg->CLK_Phase;

	//====================SPI NSS======================
	if( SPI_Cfg->NSS == SPI_NSS_Hard_Master_SS_Out_ENABLE )
	{
		tempreg_CR2 |=SPI_Cfg->NSS;
	}
	else if( SPI_Cfg->NSS == SPI_NSS_Hard_Master_SS_Out_DISABLE )
	{
		tempreg_CR2 &=SPI_Cfg->NSS;
	}
	else
	{
		tempreg_CR1 |=SPI_Cfg->NSS;
	}
    //======================================================

	//SPI_BaudRate_Prescaler
	tempreg_CR1 |= SPI_Cfg->BaudRate_Prescaler;

	//SPI_IRQ_Enable
	if( SPI_Cfg->IRQ_Enable != SPI_IRQ_ENABLE_NONE )
	{
		//SPI_IRQ_Enable_define
		tempreg_CR2 |=SPI_Cfg->IRQ_Enable;
		if(SPIx == SPI1)
		{
			NVIC_IRQ35_SPI1_ENABLE();
			P_SPI_IRQ_Callback_g[0] = SPI_Cfg->P_IRQ_CallBack;
		}
		else if(SPIx == SPI2)
		{
			NVIC_IRQ36_SPI2_ENABLE();
			P_SPI_IRQ_Callback_g[1] = SPI_Cfg->P_IRQ_CallBack;
		}

	}

	SPIx->CR1 = tempreg_CR1;
	SPIx->CR2 = tempreg_CR2;
}


/**================================================================
 * @Fn			- MCAL_SPI_DeInit
 * @brief       -DeInitialize SPI
 * @param [in]  -SPIx :Where x can be (1...2 depending on device used)
 * @retval      -None
 * Note         -Support for SPI Full Duplex Master/Slave Only & NSS HW/SW
 **================================================================*/
void MCAL_SPI_DeInit(SPI_TypeDef* SPIx)
{
	if(SPIx == SPI1)
	{
		NVIC_IRQ35_SPI1_DISABLE();
		RCC_SPI1_RESET();
	}
	else if(SPIx == SPI2)
	{
		NVIC_IRQ36_SPI2_DISABLE();
		RCC_SPI2_RESET();
	}
}

/**================================================================
 * @Fn			- MCAL_SPI_GPIO_SetPins
 * @brief 		- Initialize GPIO pins forSPI
 * @param [in]	- SPIx :Where x can be (1...3 depending on device used)
 * @retval 		- None
 * Note			- Should Enable the corresponding GPIO/AFIO In RCC
 **================================================================*/
void MCAL_SPI_GPIO_SetPins(SPI_TypeDef* SPIx)
{
	GPIO_PinConfig_t PinCfg ;

		if(SPIx == SPI1)
		{
			//PA4 : SPI1_NSS
			//PA5 : SPI1_SCK
			//PA6 : SPI1_MISO
			//PA7 : SPI1_MOSI
			if( Global_SPI_Cfg[SPI1_INDEX]->Device_Mode == SPI_Device_Mode_Master )
			{
				//PA4 : SPI1_NSS
				switch (Global_SPI_Cfg[SPI1_INDEX]->NSS)
				{
				// Input
				case SPI_NSS_Hard_Master_SS_Out_DISABLE:
					//  Master-Slave Input Floating
					PinCfg.GPIO_PinNumber = GPIO_PIN_4;
					PinCfg.GPIO_Mode = GPIO_PIN_MODE_INPUT_FLOA;
					MCAL_GPIO_Init(GPIOA, &PinCfg);
					break;

				// Output
				case SPI_NSS_Hard_Master_SS_Out_ENABLE:
					// NNS Output Alternate function pp
					PinCfg.GPIO_PinNumber = GPIO_PIN_4;
					PinCfg.GPIO_Mode = GPIO_PIN_MODE_ALTFN_OUTPUT_PP;
					PinCfg.GPIO_Output_Speed = GPIO_PIN_SPEED_10MHZ;
					MCAL_GPIO_Init(GPIOA, &PinCfg);
					break;
				}

				//PA5 : SPI1_SCK
				//Master AF Push-Pull
				PinCfg.GPIO_PinNumber = GPIO_PIN_5 ;
				PinCfg.GPIO_Mode = GPIO_PIN_MODE_ALTFN_OUTPUT_PP;
				PinCfg.GPIO_Output_Speed = GPIO_PIN_SPEED_10MHZ;
				MCAL_GPIO_Init(GPIOA, &PinCfg);

				//PA6 : SPI1_MISO (supported only full duplex)
				//full duplex / master Input floating
				PinCfg.GPIO_PinNumber = GPIO_PIN_6;
				PinCfg.GPIO_Mode = GPIO_PIN_MODE_INPUT_FLOA;
				MCAL_GPIO_Init(GPIOA, &PinCfg);

				//PA7 : SPI1_MOSI
				//Full duplex / Master AF Push-Pull
				PinCfg.GPIO_PinNumber = GPIO_PIN_7 ;
				PinCfg.GPIO_Mode = GPIO_PIN_MODE_ALTFN_OUTPUT_PP;
				PinCfg.GPIO_Output_Speed = GPIO_PIN_SPEED_10MHZ;
				MCAL_GPIO_Init(GPIOA, &PinCfg);


			}else //Slave
			{
				//PA4 : SPI1_NSS
				if(Global_SPI_Cfg[SPI1_INDEX]->NSS == SPI_NSS_Hard_Slave)
				{
					/* Hardware Master/Slave Input Floating */
					PinCfg.GPIO_PinNumber = GPIO_PIN_4;
					PinCfg.GPIO_Mode = GPIO_PIN_MODE_INPUT_FLOA;
					MCAL_GPIO_Init(GPIOA, &PinCfg);
				}

				//PA5 : SPI1_SCK
				//Slave Input Floating
				PinCfg.GPIO_PinNumber = GPIO_PIN_5;
				PinCfg.GPIO_Mode = GPIO_PIN_MODE_INPUT_FLOA;
				MCAL_GPIO_Init(GPIOA, &PinCfg);

				//PA6 : SPI1_MISO (supported only Full Duplex)
				//full Duplex /Slave AF Push-Pull
				PinCfg.GPIO_PinNumber = GPIO_PIN_6 ;
				PinCfg.GPIO_Mode = GPIO_PIN_MODE_ALTFN_OUTPUT_PP;
				PinCfg.GPIO_Output_Speed = GPIO_PIN_SPEED_10MHZ;
				MCAL_GPIO_Init(GPIOA, &PinCfg);

				//PA7 : SPI1_MOSI
				//full duplex / Slave Input floating
				PinCfg.GPIO_PinNumber = GPIO_PIN_7;
				PinCfg.GPIO_Mode = GPIO_PIN_MODE_INPUT_FLOA;
				MCAL_GPIO_Init(GPIOA, &PinCfg);
			}


		}else if(SPIx == SPI2)
		{
			//PB12 : SPI1_NSS
			//PB13 : SPI1_SCK
			//PB14 : SPI1_MISO
			//PB15 : SPI1_MOSI
			if( Global_SPI_Cfg[SPI2_INDEX]->Device_Mode == SPI_Device_Mode_Master )
			{
				//PB12 : SPI1_NSS
				switch (Global_SPI_Cfg[SPI1_INDEX]->NSS)
				{
				// Input
				case SPI_NSS_Hard_Master_SS_Out_DISABLE:
					//  Master-Slave Input Floating
					PinCfg.GPIO_PinNumber = GPIO_PIN_12;
					PinCfg.GPIO_Mode = GPIO_PIN_MODE_INPUT_FLOA;
					MCAL_GPIO_Init(GPIOB, &PinCfg);
					break;

				// Output
				case SPI_NSS_Hard_Master_SS_Out_ENABLE:
					// NNS Output Alternate function pp
					PinCfg.GPIO_PinNumber = GPIO_PIN_12;
					PinCfg.GPIO_Mode = GPIO_PIN_MODE_ALTFN_OUTPUT_PP;
					PinCfg.GPIO_Output_Speed = GPIO_PIN_SPEED_10MHZ;
					MCAL_GPIO_Init(GPIOB, &PinCfg);
					break;
				}
				//PB13 : SPI1_SCK
				//Master AF push-pull
				PinCfg.GPIO_PinNumber = GPIO_PIN_13 ;
				PinCfg.GPIO_Mode = GPIO_PIN_MODE_ALTFN_OUTPUT_PP;
				PinCfg.GPIO_Output_Speed = GPIO_PIN_SPEED_10MHZ;
				MCAL_GPIO_Init(GPIOB, &PinCfg);

				//PB14 : SPI1_MISO (supported only full duplex)
				//full duplex / master Input floating
				PinCfg.GPIO_PinNumber = GPIO_PIN_14;
				PinCfg.GPIO_Mode = GPIO_PIN_MODE_INPUT_FLOA;
				MCAL_GPIO_Init(GPIOB, &PinCfg);

				//PB15 : SPI1_MOSI
				//full duplex / master AF push-pull
				PinCfg.GPIO_PinNumber = GPIO_PIN_15 ;
				PinCfg.GPIO_Mode = GPIO_PIN_MODE_ALTFN_OUTPUT_PP;
				PinCfg.GPIO_Output_Speed = GPIO_PIN_SPEED_10MHZ;
				MCAL_GPIO_Init(GPIOB, &PinCfg);


			}else //Slave
			{
				//PB12 : SPI1_NSS
				if(Global_SPI_Cfg[SPI1_INDEX]->NSS == SPI_NSS_Hard_Slave)
				{
					/* Hardware Master/Slave Input Floating */
					PinCfg.GPIO_PinNumber = GPIO_PIN_12;
					PinCfg.GPIO_Mode = GPIO_PIN_MODE_INPUT_FLOA;
					MCAL_GPIO_Init(GPIOB, &PinCfg);
				}

    			//PB13 : SPI1_SCK
				//Slave Input floating
				PinCfg.GPIO_PinNumber = GPIO_PIN_13;
				PinCfg.GPIO_Mode = GPIO_PIN_MODE_INPUT_FLOA;
				MCAL_GPIO_Init(GPIOB, &PinCfg);

				//PB14 : SPI1_MISO (supported only full duplex)
				//full duplex /Slave AF push-pull
				PinCfg.GPIO_PinNumber = GPIO_PIN_14 ;
				PinCfg.GPIO_Mode = GPIO_PIN_MODE_ALTFN_OUTPUT_PP;
				PinCfg.GPIO_Output_Speed = GPIO_PIN_SPEED_10MHZ;
				MCAL_GPIO_Init(GPIOB, &PinCfg);

				//PB15 : SPI1_MOSI
				//full duplex / Slave Input floating
				PinCfg.GPIO_PinNumber = GPIO_PIN_15;
				PinCfg.GPIO_Mode = GPIO_PIN_MODE_INPUT_FLOA;
				MCAL_GPIO_Init(GPIOB, &PinCfg);
			}
		}
}

/**================================================================
 * @Fn			- MCAL_SPI_SendData
 * @brief       -Send Data Buffer on SPI
 * @param [in]  -SPIx :Where x can be (1...2 depending on device used)
 * @param [in]	- pTXBuffer: The Data Buffer that will be transmitted
 * @param [in]	- PollingEn: Enable or Disable SPI polling
 * @retval      -None
 * Note         -None
 **================================================================*/
void MCAL_SPI_SendData(SPI_TypeDef* SPIx,uint16_t* pTxBuffer,enum SPI_PollingMechism PollingEn)
{
	if (PollingEn == SPI_ENABLE)
		while(! (SPIx->SR & SPI_TXE_FLAG) );
	SPIx->DR = *pTxBuffer;
}

/**================================================================
 * @Fn			-MCAL_SPI_ReceiveData
 * @brief       -Receive Data Buffer on SPI
 * @param [in]  -SPIx :Where x can be (1...2 depending on device used)
 * @param [in]	-pRXBuffer: The Data Buffer that will be transmitted
 * @param [in]	-PollingEn: Enable or Disable SPI polling
 * @retval      -None
 * Note         -None
 **================================================================*/
void MCAL_SPI_ReceiveData(SPI_TypeDef* SPIx,uint16_t* pRxBuffer,enum SPI_PollingMechism PollingEn)
{
	if (PollingEn == SPI_ENABLE)
		while(! (SPIx->SR & SPI_RXNE_FLAG));
	*pRxBuffer = SPIx->DR;
}

/**================================================================
 * @Fn			-MCAL_SPI_TXRX
 * @brief       -Send Data Buffer and Receive Data Buffer on SPI
 * @param [in]  -SPIx :Where x can be (1...2 depending on device used)
 * @param [in]	-pTXRXBuffer: The Data Buffer that will be transmitted
 * @param [in]	-PollingEn: Enable or Disable SPI polling
 * @retval      -None
 * Note         -None
 **================================================================*/
void MCAL_SPI_TXRX(SPI_TypeDef* SPIx,uint16_t* pTxRxBuffer,enum SPI_PollingMechism PollingEn)
{
	if (PollingEn == SPI_ENABLE)
		while(! (SPIx->SR & SPI_TXE_FLAG) );
	SPIx->DR = *pTxRxBuffer;

	if (PollingEn == SPI_ENABLE)
		while(! (SPIx->SR & SPI_RXNE_FLAG) );
	*pTxRxBuffer = SPIx->DR;

}


/*
* =======================================================================================
* =======================================================================
* ======================        ISR FUNCTIONS                 ==============================
* =======================================================================================
*/

void SPI1_IRQHandler(void)
{
	struct sSPI_IRQ_SRC irq_src;

	irq_src.RXNE  = ( ( SPI1->SR & (SPI_RXNE_FLAG) ) >> 0   );
	irq_src.TXE   = ( ( SPI1->SR & (SPI_TXE_FLAG) )  >> 1   );
	irq_src.ERRI  = ( ( SPI1->SR & (SPI_ERRI_FLAG) )  >> 4   );

	P_SPI_IRQ_Callback_g[0](irq_src);
}

void SPI2_IRQHandler(void)
{
	struct sSPI_IRQ_SRC irq_src;

	irq_src.RXNE  = ( ( SPI2->SR & (SPI_RXNE_FLAG) ) >> 0   );
	irq_src.TXE   = ( ( SPI2->SR & (SPI_TXE_FLAG) )  >> 1   );
	irq_src.ERRI  = ( ( SPI2->SR & (SPI_ERRI_FLAG) )  >> 4   );

	P_SPI_IRQ_Callback_g[1](irq_src);
}


