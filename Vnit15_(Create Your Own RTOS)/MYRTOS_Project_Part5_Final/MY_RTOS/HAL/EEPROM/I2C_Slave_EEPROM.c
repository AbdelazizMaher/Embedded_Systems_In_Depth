/*
 * I2C_Slave_EEPROM.c
 *
 *  Created on: Nov 27, 2023
 *      Author: Abdelaziz Maher
 */

#include "I2C_Slave_EEPROM.h"



void EEPROM_Init(void)
{
	//-----------------------I2C_init-----------------------
	// 					  PB6: I2C1_SCL
	// 					  PB7: I2C1_SDA

	I2C_Config_t I2C_Cfg;

	// I2C Controller Acts as a Master
	I2C_Cfg.General_Call_Address_Detection = I2C_ENGC_ENABLE;
	I2C_Cfg.ACK_Control = I2C_ACK_ENABLE;
	I2C_Cfg.Clock_Speed = I2C_SCLK_SM_100K;
	I2C_Cfg.I2C_Mode = I2C_MODE_I2C;
	I2C_Cfg.P_SlaveEvent_IRQ_CallBack = NULL;
	I2C_Cfg.Stretch_Mode = I2C_CLK_STRETCH_ENABLE;

	MCAL_I2C_Init(EEPROM_Slave_I2Cx, &I2C_Cfg);
	MCAL_I2C_GPIO_SetPins(EEPROM_Slave_I2Cx);

}



uint8_t EEPROM_Write_nBytes(uint16_t Memory_Address, uint8_t *bytes,uint8_t DataLength)
{
	uint8_t i=0;

	uint8_t Buffer[256];

	Buffer[0] = (uint8_t)(Memory_Address >> 8);			// Upper Byte Memory Address
	Buffer[1] = (uint8_t)(Memory_Address);				// Lower Byte Memory Address

	for(i=2;i<(DataLength+2);i++)
		Buffer[i] = bytes[i-2];

	MCAL_I2C_Master_Transmit(EEPROM_Slave_I2Cx, EEPROM_Slave_Address, Buffer, (DataLength+2) , WITH_STOP, START);

	return 0;
}



uint8_t EEPROM_Read_nBytes(uint16_t Memory_Address, uint8_t *bytes,uint8_t DataLength)
{
	uint8_t Buffer[2];
	Buffer[0] = (uint8_t)(Memory_Address >> 8);			// Upper Byte Memory Address
	Buffer[1] = (uint8_t)(Memory_Address);				// Lower Byte Memory Address


	// Write Address Only
	MCAL_I2C_Master_Transmit(EEPROM_Slave_I2Cx, EEPROM_Slave_Address, Buffer, 2, WITHOUT_STOP, START);

	// Read Data
	MCAL_I2C_Master_Receive(EEPROM_Slave_I2Cx, EEPROM_Slave_Address, bytes, DataLength, WITH_STOP, REPEATED_START);

	return 0;
}
