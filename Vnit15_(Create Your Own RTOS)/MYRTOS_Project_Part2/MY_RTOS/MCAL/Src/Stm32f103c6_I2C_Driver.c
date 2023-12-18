/*
 * Stm32f103c6_I2C_Driver.c
 *
 *  Created on: Nov 22, 2023
 *      Author: Abdelaziz Maher
 */

#include"Stm32f103c6_I2C_Driver.h"

/*
 * ======================================================================
 *                                          Generic variables
 *======================================================================
 */

I2C_Config_t Global_I2C_Config[2] = { {0},{0} };

/*
 *=======================================================================
 *						Generic MACROS
 *=======================================================================
 *
 */


#define I2C1_INDEX			0
#define I2C2_INDEX			1


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
 * @Fn			- MCAL_I2C_Init
 * @brief       -Initialize I2C
 * @param [in]  -I2Cx :Where x can be (1...2 depending on device used)
 * @param [in]  -I2C_Config :All the I2C configuration
 * @retval      -None
 * Note         -Supports Master in Polling Mechanism & Slave in Interrupt Mechanism
 **================================================================*/
void MCAL_I2C_Init(I2C_TypeDef* I2Cx, I2C_Config_t *I2C_Cfg)
{
	uint16_t tempreg = 0, freqrange = 0 , SM_Speed = 0;
	uint32_t pclk1 = 8000000;

	// Enable RCC clock
	if( I2Cx == I2C1 )
	{
		Global_I2C_Config[I2C1_INDEX] = *I2C_Cfg;
		RCC_I2C1_CLK_ENABLE();
	}
	else
	{
		Global_I2C_Config[I2C2_INDEX] = *I2C_Cfg;
		RCC_I2C2_CLK_ENABLE();
	}

	// Mode
	if( I2C_Cfg->I2C_Mode == I2C_MODE_I2C )
	{
		/******************   Init Time   ******************/
		// I2C_CR2.FREQ[5:0] : Peripheral clock frequency from APB1
		// Get the I2Cx CR2 Value
		tempreg = I2Cx->CR2;
		// Clear Frequency FREQ[5:0] bits
		tempreg &= ~(I2C_CR2_FREQ_Msk);
		// Get pclk1 Frequency Value
		pclk1 = MCAL_RCC_GetPClk1Freq();
		// Set the Frequency Bits Depending on pclk1 value
		freqrange = (uint16_t)(pclk1 / 1000000);

		tempreg |= freqrange;
		// Write to I2Cx CR2 register
		I2Cx->CR2 = tempreg;

		//Configure the clock control register I2C_CCR
		// Disable The Selected I2C Peripheral To Configure Time
		I2Cx->CR1 &= ~(I2C_CR1_PE);

		tempreg = 0;
		// Configure Speed In Standard Mode
		if( I2C_Cfg->Clock_Speed == I2C_SCLK_SM_50K || I2C_Cfg->Clock_Speed == I2C_SCLK_SM_100K )
		{
			// Standard Mode Speed Calculations
			//					 Tclk / 2 = CCR * Tpclk1
			// 					 CCR = Tclk / (2 * Tpclk1)
			//					 CCR = Fpclk1 / (2 * I2C_ClockFrequency)

			SM_Speed = (uint16_t)( pclk1 / ( I2C_Cfg->Clock_Speed << 1 ) );
			tempreg |= SM_Speed;
			// Write to CCR
			I2Cx->CCR = tempreg;

			/******************   TRISE_Configuration   ******************/
			//	If, in the I2C_CR2 register, the value of FREQ[5:0] bits is equal to 0x08 and TPCLK1 = 125 ns
			//	therefore the TRISE[5:0] bits must be programmed with 09h.

			I2Cx->TRISE = freqrange + 1;
		}
		else
		{
			//TODO  Fast Mode Is Not Implemented
		}

		/******************  I2Cx CR1_Configuration   ******************/
		tempreg = 0;
		// Get The I2Cx CR1 value
		tempreg = I2Cx->CR1;

		tempreg |= (uint16_t)( I2C_Cfg->ACK_Control | I2C_Cfg->General_Call_Address_Detection | I2C_Cfg->I2C_Mode | I2C_Cfg->Stretch_Mode );
		// Write to I2Cx CR1 register
		I2Cx->CR1 = tempreg;

		/******************  I2Cx OAR1 & OAR2 Configuration   ******************/
		tempreg = 0;
		if(I2C_Cfg->I2C_Slave_Address.Enable_Dual_Address == 1)
		{
			tempreg = I2C_OAR2_ENDUAL;
			tempreg |= I2C_Cfg->I2C_Slave_Address.Secondary_Slave_Address << I2C_OAR2_ADD2_Pos;
			I2Cx->OAR2 = tempreg;
		}

		tempreg = 0;

		tempreg |= I2C_Cfg->I2C_Slave_Address.Primary_Slave_Address << I2C_OAR1_ADD_Pos;
		tempreg |= I2C_Cfg->I2C_Slave_Address.I2C_Addressing_Mode;
		// Write to I2Cx OAR1 register
		I2Cx->OAR1 = tempreg;
	}
	else
	{
		//TODO  SMBUS Not Implemented
	}

	// Interrupt mode (Slave mode) // Check CallBack Pointer != NULL
	if( I2C_Cfg->P_SlaveEvent_IRQ_CallBack != NULL )
	{
		// Enable IRQs
		I2Cx->CR2 |= (I2C_CR2_ITERREN);
		I2Cx->CR2 |= (I2C_CR2_ITEVTEN);
		I2Cx->CR2 |= (I2C_CR2_ITBUFEN);

		if( I2Cx == I2C1 )
		{
			NVIC_IRQ31_I2C1_EV_ENABLE();
			NVIC_IRQ32_I2C1_ER_ENABLE();

		}
		else if( I2Cx == I2C2 )
		{
			NVIC_IRQ33_I2C2_EV_ENABLE();
			NVIC_IRQ34_I2C2_ER_ENABLE();
		}
		I2Cx->SR1 = 0;
		I2Cx->SR2 = 0;
	}
	// Enable The Selected I2C Peripheral
	I2Cx->CR1 |= I2C_CR1_PE;
}

/**================================================================
 * @Fn			- MCAL_I2C_DeInit
 * @brief        -DeInitialize I2C
 * @param [in]  -I2Cx :Where x can be (1...2 depending on device used)
 * @param [in]  -I2C_Config :All the I2C configuration
 * @retval      -None
 * Note         -Supports Master in Polling Mechanism & Slave in Interrupt Mechanism
 **================================================================*/
void MCAL_I2C_DeInit(I2C_TypeDef* I2Cx, I2C_Config_t *I2C_Cfg)
{
	if( I2Cx == I2C1 )
	{
		NVIC_IRQ31_I2C1_EV_DISABLE();
		NVIC_IRQ32_I2C1_ER_DISABLE();
		RCC_I2C1_RESET();

	}
	else if( I2Cx == I2C2 )
	{
		NVIC_IRQ33_I2C2_EV_DISABLE();
		NVIC_IRQ34_I2C2_ER_DISABLE();
		RCC_I2C2_RESET();
	}
}

/**================================================================
 * @Fn			- MCAL_I2C_GPIO_SetPins
 * @brief 		- Initialize GPIO pins for I2C
 * @param [in]	- I2Cx :Where x can be (1...3 depending on device used)
 * @retval 		- None
 * Note			- Should Enable the Corresponding GPIO/AFIO In RCC
 **================================================================*/
void MCAL_I2C_GPIO_SetPins(I2C_TypeDef* I2Cx)
{
	GPIO_PinConfig_t PinCfg;

	if( I2Cx == I2C1 )
	{
		//			 PB6: I2C1_SCL
		// 			 PB7: I2C1_SDA

		PinCfg.GPIO_Mode = GPIO_PIN_MODE_ALTFN_OUTPUT_OD;
		PinCfg.GPIO_Output_Speed = GPIO_PIN_SPEED_10MHZ;

		PinCfg.GPIO_PinNumber = GPIO_PIN_6;
		MCAL_GPIO_Init(GPIOB, &PinCfg);

		PinCfg.GPIO_PinNumber = GPIO_PIN_7;
		MCAL_GPIO_Init(GPIOB, &PinCfg);
	}
	else if( I2Cx == I2C2 )
	{
		// 			  PB10: I2C2_SCL
		//			  PB11: I2C2_SDA

		PinCfg.GPIO_PinNumber = GPIO_PIN_10;
		MCAL_GPIO_Init(GPIOB, &PinCfg);

		PinCfg.GPIO_PinNumber = GPIO_PIN_11;
		MCAL_GPIO_Init(GPIOB, &PinCfg);
	}
}

/**================================================================
 * @Fn			- MCAL_I2C_Master_Transmit
 * @brief 		- None
 * @param [in] 	- I2Cx: where x can be (1 or 2) depending on the device used
 * @param [in] 	- SlaveAddress: the address of slave you want to transmit to
 * @param [in] 	- DataOut: A buffer holds the data to be sent
 * @param [in] 	- DataLen: Length of data in bytes
 * @param [in] 	- Stop: Enabling or disabling stop condition
 * @param [in] 	- Start: If you want to send a Start or repeated start
 * @retval 		- None
 * Note			- Master Transmit Data In Polling Mode
 **================================================================*/
void MCAL_I2C_Master_Transmit(I2C_TypeDef *I2Cx, uint16_t SlaveAddress, uint8_t *DataOut, uint32_t DataLen, eStopCondition Stop, eStartCondition Start)
{
	// Todo
	// Support Timeout (Configure timer working for specific duration)

	// 1- Set The START bit in I2C_CRQ to generate a start condition
	I2C_Generate_START(I2Cx, I2C_ENABLE, Start);

	// 2- Wait for EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address
	while(!I2C_GetFlagStatus(I2Cx, EV5));

	// 3- Send Address
	I2C_SendAddress(I2Cx, SlaveAddress, I2C_Direction_Transmitter);

	// Wait for EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
	while(!I2C_GetFlagStatus(I2Cx, EV6));

	// 4- Check : TRA, BUSY, MSL, TXE Flags
	while(!I2C_GetFlagStatus(I2Cx, MASTER_BYTE_TRANSMITTING));

	// 5- Send Data
	while( DataLen >0 )
	{
		// Write in the DR register the data to be sent
		I2Cx->DR = *DataOut;
		DataOut++;
		DataLen--;

		// Wait EV8: TxE=1, shift register not empty, d . ata register empty, cleared by writing DR register
		while(!I2C_GetFlagStatus(I2Cx, EV8));
	}
	// Already the last byte checked in the for loop
	//	EV8_2: TxE=1, BTF = 1, Program Stop request. TxE and BTF are cleared by hardware by the Stop condition
	//	while(!I2C_GetFlagStatus(I2Cx, EV8_2));

	// 6- Stop Condition
	if(Stop == WITH_STOP)
	{
		I2C_Generate_STOP(I2Cx,I2C_ENABLE);
	}
}


void MCAL_I2C_Master_Receive(I2C_TypeDef *I2Cx, uint16_t SlaveAddress, uint8_t *DataIn, uint32_t DataLen, eStopCondition Stop, eStartCondition Start)
{
	uint8_t index = (I2Cx == I2C1) ? I2C1_INDEX : I2C2_INDEX;

	// 1- Set START bit in I2C_CRQ to generate a start condition
	I2C_Generate_START(I2Cx, I2C_ENABLE, REPEATED_START);

	// 2- Wait for EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address
	while(!I2C_GetFlagStatus(I2Cx, EV5));

	// 3- Send Address
	I2C_SendAddress(I2Cx, SlaveAddress, I2C_Direction_Reciever);

	//Wait for EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
	while(!I2C_GetFlagStatus(I2Cx, EV6));

	//procedure to read only 1 byte from slave
	if( DataLen == 1 )
	{
		//Disable Acking
		I2C_AcknowledgeConfig(I2Cx,I2C_DISABLE);

		// Wait for EV7: RXNE=1, Cleared by reading DR
		while(!I2C_GetFlagStatus(I2Cx, EV7));

		if( Stop == WITH_STOP )
		{
			I2C_Generate_STOP(I2Cx, I2C_ENABLE);
		}

		// Read data from register
		*DataIn = I2Cx->DR;
		DataLen--;
	}
	else
	{
		while( DataLen > 0 )
		{
			// Wait for EV7: RXNE=1, Cleared by reading DR
			while(!I2C_GetFlagStatus(I2Cx, EV7));

			if( DataLen == 2 )
			{
				*DataIn = I2Cx->DR;
				DataIn++;
				DataLen--;

				// Wait for EV7: RXNE=1, Cleared by reading DR
				while(!I2C_GetFlagStatus(I2Cx, EV7));

				//Disable Acking
				I2C_AcknowledgeConfig(I2Cx,I2C_DISABLE);

				if( Stop == WITH_STOP )
				{
					I2C_Generate_STOP(I2Cx, I2C_ENABLE);
				}

			}
			*DataIn = I2Cx->DR;
			DataIn++;
			DataLen--;
		}
	}

	// Re-enabling the acknowledge According to the original configuration
	if( Global_I2C_Config[index].ACK_Control == I2C_ACK_ENABLE )
	{
		I2C_AcknowledgeConfig(I2Cx,I2C_ENABLE);
	}
}

void MCAL_I2C_Slave_Transmit_IT(I2C_TypeDef *I2Cx, uint8_t DataOut)
{
	I2Cx->DR = DataOut;
}

uint8_t MCAL_I2C_Slave_Recieve_IT(I2C_TypeDef *I2Cx)
{
	return ((uint8_t)(I2Cx->DR));
}

void I2C_Generate_START(I2C_TypeDef *I2Cx, eFunctionalState NewState,eStartCondition Start)
{
	// Check if Start or Repeated Start
	if( Start != REPEATED_START )
	{
		// Check if The Bus is Idle
		while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));
	}

	//	Bit 8 START: Start generation
	//	This bit is set and cleared by software and cleared by hardware when start is sent or PE=0.
	//	In Master Mode:
	//	0: No Start generation
	//	1: Repeated start generation
	//	In Slave mode:
	//	0: No Start generation
	//	1: Start generation when the bus is free

	if( NewState != I2C_DISABLE )
	{
		// Generate a Start Condition
		I2Cx->CR1 |= I2C_CR1_START;
	}
	else
	{
		// Disable The Start Condition Generation
		I2Cx->CR1 &= ~(I2C_CR1_START);
	}
}

void I2C_Generate_STOP(I2C_TypeDef *I2Cx, eFunctionalState NewState)
{
	if( NewState != I2C_DISABLE)
	{
		// Generate a Stop Condition
		I2Cx->CR1 |= I2C_CR1_STOP;
	}
	else
	{
		// Disable The Stop Condition Generation
		I2Cx->CR1 &= ~(I2C_CR1_STOP);
	}
}

void I2C_SendAddress(I2C_TypeDef* I2Cx, uint16_t Address, eI2C_Direction Direction)
{
	uint8_t index = (I2Cx == I2C1) ? I2C1_INDEX : I2C2_INDEX;

	// Check if 7-bit address or 10-bit address
	if(Global_I2C_Config[index].I2C_Slave_Address.I2C_Addressing_Mode == I2C_ADDRESSING_7BIT)
	{
		Address = (Address << 1);

		if( Direction != I2C_Direction_Transmitter )
		{
			// Set The Address bit0 For Read
			Address |= 1<<0;
		}
		else
		{
			// Reset The Address bit0 For write
			Address &= ~(1<<0);
		}

		// Send The Address
		I2Cx->DR = Address;
	}
	else
	{
		//Todo Not Implemented
	}
}

void I2C_AcknowledgeConfig(I2C_TypeDef* I2Cx, eFunctionalState NewState)
{
	if (NewState != I2C_DISABLE)
	{
		/* Enable the acknowledgment */
		I2Cx->CR1 |= I2C_CR1_ACK;
	}
	else
	{
		/* Disable the acknowledgment */
		I2Cx->CR1 &= ~(I2C_CR1_ACK);
	}
}

void I2C_ClearADDRFlag(I2C_TypeDef *pI2Cx)
{
	uint32_t dummy_read;
	dummy_read = pI2Cx->SR1;
	dummy_read = pI2Cx->SR2;
	(void)dummy_read;
}

eFlagStatus I2C_GetFlagStatus(I2C_TypeDef* I2Cx, eI2C_Events Event)
{
	uint32_t flag1 = 0 , flag2 = 0 , lastEvent = 0;
	eFlagStatus BitStatus = I2C_RESET;
	switch( Event )
	{
	case I2C_FLAG_BUSY:
	{
		//      Bit 1 BUSY: Bus busy in SR2
		//		0: No communication on the bus
		//		1: Communication ongoing on the bus
		//		– Set by hardware on detection of SDA or SCL low
		//		– cleared by hardware on detection of a Stop condition.
		//		It indicates a communication in progress on the bus. This information is still updated when the interface is disabled (PE=0)
		if(I2Cx->SR2 & (I2C_SR2_BUSY))
			BitStatus = I2C_SET;
		else
			BitStatus = I2C_RESET;
		break;
	}
	case EV5:
	{
		//		Bit 0 SB: Start bit (Master mode)
		//		0: No Start condition
		//		1: Start condition generated.
		//		– Set when a Start condition generated.
		//		– Cleared by software by reading the SR1 register followed by writing the DR register, or by hardware when PE=0
		if(I2Cx->SR1 & (I2C_SR1_SB))
			BitStatus = I2C_SET;
		else
			BitStatus = I2C_RESET;
		break;
	}
	case EV6:
	{
		//		Bit 1 ADDR: Address sent (Master mode)/matched(Slave mode)
		//		0: No end of address transmission
		//		1: End of address transmission
		if(I2Cx->SR1 & (I2C_SR1_ADDR))
			BitStatus = I2C_SET;
		else
			BitStatus = I2C_RESET;
		break;
	}
	case EV7:
	{
		//		Bit 6 RxNE: Data register not empty (receivers)
		//		0: Data register empty
		//		1: Data register not empty
		if((I2Cx->SR1)& (I2C_SR1_RXNE))
			BitStatus = I2C_SET;
		else
			BitStatus = I2C_RESET;
		break;
	}
	case EV8_1:
	case EV8:
	{
		//		EV8_1: TxE=1, shift register empty, data register empty, write Data1 in DR.
		//		EV8: TxE=1, shift register not empty, d . ata register empty, cleared by writing DR register
		if((I2Cx->SR1)& (I2C_SR1_TXE))
			BitStatus = I2C_SET;
		else
			BitStatus = I2C_RESET;
		break;
	}
	case MASTER_BYTE_TRANSMITTING:
	{
		// Read I2Cx status register
		flag1 = I2Cx->SR1;
		flag2 = I2Cx->SR2;

		flag2 = flag2 << 16;
		// Get The Last event value from status registers
		lastEvent = (flag1 | flag2) & ((uint32_t)(0x00FFFFFF));
		// Check whether the last event contains I2C_Event
		if( ( lastEvent &  Event ) == Event )
			BitStatus = I2C_SET;
		else
			BitStatus = I2C_RESET;
		break;
	}
	}

	return BitStatus;
}

void I2C1_EV_IRQHandler(void)
{
	I2C_TypeDef *I2Cx = I2C1;
	// Interrupt Handling for both master and slave
	uint32_t temp1,temp2,temp3;

	temp1 = I2Cx->CR2 & (I2C_CR2_ITEVTEN);
	temp2 = I2Cx->CR2 & (I2C_CR2_ITBUFEN);
	temp3 = I2Cx->SR1 & (I2C_SR1_STOPF);

	// Handle For interrupt generated by STOPF event
	// Note : Stop detection flag is applicable only slave mode
	if(temp1 && temp3)
	{
		//STOF flag is set
		//Clear the STOPF ( i.e 1) read SR1 2) Write to CR1 )
		I2Cx->CR1 |= 0x0000;
		Slave_States(I2Cx,I2C_EV_STOP);
	}
	//----------------------------------------------------------
	temp3 = I2Cx->SR1 & (I2C_SR1_ADDR);
	// Handle For interrupt generated by ADDR event
	//Note : When master mode  : Address is sent
	//		 When Slave mode   : Address matched with own address
	if(temp1 && temp3)
	{
		// interrupt is generated because of ADDR event
		//check for device mode
		if(I2Cx->SR2 & ( I2C_SR2_MSL))
		{
			//master
		}
		else
		{
			//slave mode
			//clear the ADDR flag ( read SR1 , read SR2)
			I2C_ClearADDRFlag(I2Cx);
			Slave_States(I2Cx,I2C_EV_ADDR_Matched);

		}
	}
	//----------------------------------------------------------

	temp3 = I2Cx->SR1 & ( I2C_SR1_TXE);
	// Handle For interrupt generated by TXE event
	if(temp1 && temp2 && temp3)
	{
		//Check for device mode
		if(I2Cx->SR2 & (I2C_SR2_MSL))
		{

		}
		else
		{
			//slave
			Slave_States(I2Cx,I2C_EV_DATA_REQ);
		}
	}

	//----------------------------------------------------------

	temp3 = I2Cx->SR1 & ( I2C_SR1_RXNE);
	// Handle For interrupt generated by SB=1, cleared by reading SR1 register followed by writing DR register with Address.
	if(temp1 && temp2 && temp3)
	{
		//check device mode .
		if(I2Cx->SR2 & ( I2C_SR2_MSL))
		{
			//The device is master
		}
		else
		{
			//slave
			Slave_States(I2Cx,I2C_EV_DATA_RCV);
		}
	}

}


void I2C1_ER_IRQHandler(void)
{

}


void I2C2_EV_IRQHandler(void)
{

}


void I2C2_ER_IRQHandler(void)
{

}



void Slave_States(I2C_TypeDef* I2Cx  ,eI2C_Slave_State State)
{
	uint8_t index =    I2Cx == I2C1 ? I2C1_INDEX: I2C2_INDEX ;

	switch ( State )
	{

	case I2C_ERROR_AF:
	{
		//make sure that the slave is really in transmitter mode
		if(I2Cx->SR2 & ( I2C_SR2_TRA))
		{
			//Slave Shouldn't Send anything else
		}

		break ;
	}

	case I2C_EV_STOP:
	{
		//make sure that the slave is really in transmitter mode
		if(I2Cx->SR2 & ( I2C_SR2_TRA))
		{
			//Notify APP that the Stop Condition is sent by the master
			Global_I2C_Config [index].P_SlaveEvent_IRQ_CallBack (I2C_EV_STOP) ;
		}

		break ;
	}

	case I2C_EV_ADDR_Matched:
	{
		//Notify APP that the Stop Condition is sent by the master
		Global_I2C_Config [index].P_SlaveEvent_IRQ_CallBack (I2C_EV_ADDR_Matched) ;

		break ;
	}

	case I2C_EV_DATA_REQ:
	{
		//make sure that the slave is really in transmitter mode
		if(I2Cx->SR2 & ( I2C_SR2_TRA))
		{
			//the APP layer should send the data (MCAL_I2C_SlaveSendData ) in this state
			Global_I2C_Config [index].P_SlaveEvent_IRQ_CallBack (I2C_EV_DATA_REQ) ;
		}

		break ;
	}
	case I2C_EV_DATA_RCV:
	{
		//make sure that the slave is really in receiver mode
		if(!(I2Cx->SR2 & ( I2C_SR2_TRA)))
		{
			//the APP layer should read the data (MCAL_I2C_SlaveReceiveData ) in this state
			Global_I2C_Config [index].P_SlaveEvent_IRQ_CallBack (I2C_EV_DATA_RCV) ;
		}

		break ;
	}
	}

}
