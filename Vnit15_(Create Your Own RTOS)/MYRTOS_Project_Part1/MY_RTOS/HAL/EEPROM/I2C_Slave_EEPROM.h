/*
 * I2C_Slave_EEPROM.h
 *
 *  Created on: Nov 27, 2023
 *      Author: Abdelaziz Maher
 */

#ifndef EEPROM_I2C_SLAVE_EEPROM_H_
#define EEPROM_I2C_SLAVE_EEPROM_H_

#include"Stm32f103c6_I2C_Driver.h"

/**
 * E2PROM is an I2C slave
 * Idle Mode : The Device is in High Impedance State and Waits for data
 * Master Transmitter Mode : The Device Transmits Data to slave receiver
 * Master Receiver Mode : The Device Receives Data from a slave transmitter
 */

#define EEPROM_Slave_I2Cx           I2C1
#define EEPROM_Slave_Address		0x2A


void EEPROM_Init(void);
uint8_t EEPROM_Write_nBytes(uint16_t Memory_Address, uint8_t *bytes,uint8_t DataLength);
uint8_t EEPROM_Read_nBytes(uint16_t Memory_Address, uint8_t *bytes,uint8_t DataLength);


#endif /* EEPROM_I2C_SLAVE_EEPROM_H_ */
