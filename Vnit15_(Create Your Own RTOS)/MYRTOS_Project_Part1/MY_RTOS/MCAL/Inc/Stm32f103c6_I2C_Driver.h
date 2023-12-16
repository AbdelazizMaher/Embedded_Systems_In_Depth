/*
 * Stm32f103c6_I2C_Driver.h
 *
 *  Created on: Nov 22, 2023
 *      Author: Abdelaziz Maher
 */

#ifndef INC_STM32F103C6_I2C_DRIVER_H_
#define INC_STM32F103C6_I2C_DRIVER_H_

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
//User type definitions (structures/enums)
//-----------------------------------------------

typedef enum
{
	WITH_STOP,
	WITHOUT_STOP
}eStopCondition;

typedef enum
{
	START,
	REPEATED_START
}eStartCondition;

typedef enum
{
	I2C_DISABLE,
	I2C_ENABLE
}eFunctionalState;

typedef enum
{
	I2C_RESET,
	I2C_SET
}eFlagStatus;

typedef enum
{
	I2C_Direction_Transmitter,
	I2C_Direction_Reciever
}eI2C_Direction;

typedef enum
{
	I2C_FLAG_BUSY=0,
	EV5,   								// EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address
	EV6,    							// EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
	EV7,								// EV7: RXNE=1, Cleared by reading DR
	EV8,								// EV8: TxE=1, shift register not empty, d . ata register empty, cleared by writing DR register
	EV8_1,
	MASTER_BYTE_TRANSMITTING = ((uint32_t)(0x00070080))   // TRA, BUSY, MSL, TXE
}eI2C_Events;

typedef enum
{
	I2C_EV_STOP,
	I2C_ERROR_AF,
	I2C_EV_ADDR_Matched,
	I2C_EV_DATA_REQ,	// The APP Layer should send the data (I2C_Slave_SendData) in this state
	I2C_EV_DATA_RCV     // The APP Layer should read the data (I2C_Slave_ReceiveData) in this state
}eI2C_Slave_State;

struct sI2C_Slave_Address
{
	uint16_t	Enable_Dual_Address;		    // 1- Enable   2- Disable
	uint16_t	Primary_Slave_Address;
	uint16_t	Secondary_Slave_Address;
	uint32_t	I2C_Addressing_Mode;			// @ref I2C_ADDRESSING_Mode
};

typedef struct
{
	uint32_t								Clock_Speed;                           	// Specifies the Clock Frequency of I2C @ref I2C_SCLK_Define

	uint32_t								Stretch_Mode;	                       	// Clock Stretching @ref I2C_CLK_Stretch_Define

	uint32_t								I2C_Mode;		                      	// Specifies I2C mode or SMBUS @ref I2C_MODE_Define

	struct sI2C_Slave_Address		        I2C_Slave_Address;

	uint32_t								ACK_Control;		                    // Acknowledge @ref I2C_Ack_Define

	uint32_t								General_Call_Address_Detection;			// @ref I2C_ENGC_Define

	void(*P_SlaveEvent_IRQ_CallBack)(eI2C_Slave_State State);                       //Set C Function() To call when IRQ happen

}I2C_Config_t;


//-----------------------------------------------
//Macros Configuration References
//-----------------------------------------------

/* @ref I2C_SCLK_Define*/
#define I2C_SCLK_SM_50K					(50000U)
#define I2C_SCLK_SM_100K				(100000U)
#define I2C_SCLK_FM_200K				(200000U)
#define I2C_SCLK_FM_400K				(400000U)

/*@ref I2C_CLK_Stretch_Define (Bit 7 NOSTRETCH: Clock stretching disable (Slave mode)*/
#define I2C_CLK_STRETCH_ENABLE			0x00000000U
#define I2C_CLK_STRETCH_DISABLE		    I2C_CR1_NOSTRETCH


/*@ref I2C_MODE_Define (Bit 1 SMBUS: SMBus mod)*/
#define I2C_MODE_I2C					0x00000000U
#define I2C_MODE_SMBUS					I2C_CR1_SMBUS

/*@ref I2C_ADDRESSING_BITS (Bit 15 ADDMODE Addressing mode (slave mode) in OAR1*/
#define I2C_ADDRESSING_7BIT				0x00000000U
#define I2C_ADDRESSING_10BIT			I2C_OAR1_ADDMODE

// @ref I2C_Ack_Define (Bit 19 ACK: Acknowledge enable)
#define I2C_ACK_ENABLE					I2C_CR1_ACK
#define I2C_ACK_DISABLE					((uint16_t)0x0000)


// @ref I2C_ENGC_Define (Bit 6 ENGC: General call enable)
#define I2C_ENGC_ENABLE					I2C_CR1_ENGC
#define I2C_ENGC_DISABLE				0x00000000U

/*
 * =======================================================================================
 *                         APIs Supported by "MCAL I2C DRIVER"
 * =======================================================================================
 */
/*** Initialization/De-Initialization Functions***/
void MCAL_I2C_Init(I2C_TypeDef* I2Cx, I2C_Config_t *I2C_Cfg);
void MCAL_I2C_DeInit(I2C_TypeDef* I2Cx, I2C_Config_t *I2C_Cfg);

void MCAL_I2C_GPIO_SetPins(I2C_TypeDef* I2Cx);

// Master Polling Mechanism
void MCAL_I2C_Master_Transmit(I2C_TypeDef *I2Cx, uint16_t SlaveAddress, uint8_t *DataOut, uint32_t DataLen, eStopCondition Stop, eStartCondition Start);
void MCAL_I2C_Master_Receive(I2C_TypeDef *I2Cx, uint16_t SlaveAddress, uint8_t *DataIn, uint32_t DataLen, eStopCondition Stop, eStartCondition Start);

// Slave interrupt Mechanism
void MCAL_I2C_Slave_Transmit_IT(I2C_TypeDef *I2Cx, uint8_t Data);
uint8_t MCAL_I2C_Slave_Recieve_IT(I2C_TypeDef *I2Cx);

void Slave_States(I2C_TypeDef* I2Cx  ,eI2C_Slave_State State);

// Generic APIs
void I2C_Generate_START(I2C_TypeDef *I2Cx, eFunctionalState NewState,eStartCondition Start);
void I2C_Generate_STOP(I2C_TypeDef *I2Cx, eFunctionalState NewState);
void I2C_SendAddress(I2C_TypeDef* I2Cx, uint16_t Address, eI2C_Direction Direction);
void I2C_AcknowledgeConfig(I2C_TypeDef* I2Cx, eFunctionalState NewState);
void I2C_ClearADDRFlag(I2C_TypeDef *pI2Cx);
eFlagStatus I2C_GetFlagStatus(I2C_TypeDef* I2Cx, eI2C_Events Event);

#endif /* INC_STM32F103C6_I2C_DRIVER_H_ */
