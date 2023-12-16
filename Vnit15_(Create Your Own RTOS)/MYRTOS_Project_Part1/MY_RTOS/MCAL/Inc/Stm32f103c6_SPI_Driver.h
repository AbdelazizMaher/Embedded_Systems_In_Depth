/*
 * Stm32f103c6_SPI_Driver.h
 *
 *  Created on: Mar 30, 2023
 *      Author: Abdelaziz Maher
 */

#ifndef INC_STM32F103C6_SPI_DRIVER_H_
#define INC_STM32F103C6_SPI_DRIVER_H_

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

struct sSPI_IRQ_SRC
{
	uint8_t TXE:1;        //TX Buffer Empty interrupt means write new data
	uint8_t RXNE:1;       //RX Buffer Not Empty interrupt means read it
	uint8_t ERRI:1;       //ERROR interrupt
	uint8_t RESERVED:5;
};

typedef struct
{
    uint16_t 		Device_Mode;         					//Specifies the SPI operating mode @ref SPI_Device_Mode_Define

    uint16_t 		Communication_Mode; 					//Specifies the SPI Bidirectional Mode state @ref SPI_Direction_Define

    uint16_t  	    Frame_Format;        					//Specifies LSB or MSB @ref SPI_Frame_Format_Define

    uint16_t  	    Date_Size;          					//Specifies Data Size @ref SPI_Data_Size_Define

    uint16_t        CLK_Polarity;        					//Specifies CLK_Polarity @ref SPI_CPOL_Define

    uint16_t        CLK_Phase;          			 		//Specifies CLK_Phase @ref SPI_CPHA_Define

    uint16_t        NSS;                 					//Specifies NSS @ref SPI_NSS_Mode_Define

    uint16_t        BaudRate_Prescaler; 					//Specifies BaudRate_Prescaler value which will be used to configure the
                                      	  	  	  	  	  	//Transmit and Receiver SCK Clock. Set This Parameter form @ref SPI_BaudRate_Prescaler_Define


    uint16_t       IRQ_Enable;                              //@ref SPI_IRQ_Enable

    void (*P_IRQ_CallBack )(struct sSPI_IRQ_SRC irq_src);   //Set C Function() To call when IRQ happen

}SPI_Config_t;


//-----------------------------------------------
//Macros Configuration References
//-----------------------------------------------
/*ref SPI_Device_Mode_Define*/
#define SPI_Device_Mode_Slave                        (uint32_t)(0)
#define SPI_Device_Mode_Master                       (uint32_t)( 1<<2 )     //CR1.MSTR: Master selection



/*@ref SPI_Direction_Define*/
#define SPI_Direction_2Lines                         (uint32_t)(0)
#define SPI_Direction_2Lines_RXONLY                  ( 1<<10 )
#define SPI_Direction_1Line_RXONLY                   (uint32_t)(0)
#define SPI_Direction_1Line_TXONLY                   ( 1<<15 ) | ( 1<<14 )



/*@ref SPI_Frame_Format_Define*/
#define SPI_Frame_Format_MSB_First         	         (uint32_t)(0)         //CR1 .Bit 7 LSBFIRST: Frame format 0: MSB transmitted first
#define SPI_Frame_Format_LSB_First                   (uint32_t)( 1<<7 )    //CR1. Bit 7 LSBFIRST: Frame format 1: LSB transmitted first



/*@ref SPI_Data_Size_Define*/
#define SPI_Data_Size_8Bit_Mode                      (uint32_t)(0)         //CR1 Bit 11 DFF: Data frame format 0: 8-bit data frame format
#define SPI_Data_Size_16Bit_Mode                     (uint32_t)( 1<<11 )   //CR1 Bit 11 DFF: Data frame format 0: 16-bit data frame format



/*@ref SPI_CPOL_Define*/
#define SPI_CPOL_Low           	                     (uint32_t)(0)        //CR1 .Bit1 CPOL: Clock polarity 0: CK to 0 when idle
#define SPI_CPOL_High                                (uint32_t)( 1<<1 )   //CR1 .Bit1 CPOL: Clock polarity 1: CK to 1 when idle



/*ref SPI_CPHA_Define*/
#define SPI_CPHA_1Edge_First_Data_Capture_Edge       (uint32_t)(0)         //CR1. Bit 0 CPHA: Clock phase
#define SPI_CPHA_2Edge_First_Data_Capture_Edge       (uint32_t)( 1<<0 )    //CR1. Bit 0 CPHA: Clock phase



/*@ref SPI_NSS_Mode*/
//HardWare
#define SPI_NSS_Hard_Slave                           (uint32_t)(0)        //CR1. Bit 9 SSM: Software slave management 0: Software slave management disabled
#define SPI_NSS_Hard_Master_SS_Out_ENABLE            ( 1<<2 )             //CR2. Bit 2 SSOE: SS output enable 1: SS output is enabled in master mode and when the cell is enabled
#define SPI_NSS_Hard_Master_SS_Out_DISABLE           (uint32_t)(0)        //CR2. Bit 2 SSOE: SS Output Disable
//SoftWare(MASTER OR SLAVE)
#define SPI_NSS_Soft_NSSInternal_RESET               ( 1<<9 ) | (uint32_t)(0)
#define SPI_NSS_Soft_NSSInternal_SET                 ( 1<<9 ) | ( 1<<8 )


/*ref SPI_BaudRate_Prescaler*/
//Bits 5:3 BR[2:0]: Baud rate control
#define SPI_BaudRate_Prescaler_2                     ( 0b000<<3 )
#define SPI_BaudRate_Prescaler_4                     ( 0b001<<3 )
#define SPI_BaudRate_Prescaler_8                     ( 0b010<<3 )
#define SPI_BaudRate_Prescaler_16                    ( 0b011<<3 )
#define SPI_BaudRate_Prescaler_32                    ( 0b100<<3 )
#define SPI_BaudRate_Prescaler_64                    ( 0b101<<3 )
#define SPI_BaudRate_Prescaler_128                   ( 0b110<<3 )
#define SPI_BaudRate_Prescaler_256                   ( 0b111<<3 )

//@ref SPI_IRQ_Enable
#define SPI_IRQ_ENABLE_NONE                          (uint16_t)(0)
#define SPI_IRQ_ENABLE_TXEIE                         ( 1<<7 )             //CR2 .Bit 7 TXEIE: Tx buffer empty interrupt enable
#define SPI_IRQ_ENABLE_RXNEIE                        ( 1<<6 )             //CR2 .Bit 6 RXNEIE: RX buffer not empty interrupt enable
#define SPI_IRQ_ENABLE_ERRIE                         ( 1<<5 )             //CR2 .Bit 5 ERRIE: Error interrupt enable

enum SPI_PollingMechism
{
	SPI_ENABLE,
	SPI_DISABLE
};

/*
 * =======================================================================================
 *                         APIs Supported by "MCAL SPI DRIVER"
 * =======================================================================================
 */
/*** Initialization/De-Initialization Functions***/
void MCAL_SPI_Init(SPI_TypeDef* SPIx,SPI_Config_t* SPI_Cfg);
void MCAL_SPI_DeInit(SPI_TypeDef* SPIx);

void MCAL_SPI_GPIO_SetPins(SPI_TypeDef* SPIx);

void MCAL_SPI_SendData(SPI_TypeDef* SPIx,uint16_t* pTxBuffer,enum SPI_PollingMechism PollingEn);
void MCAL_SPI_ReceiveData(SPI_TypeDef* SPIx,uint16_t* pRxBuffer,enum SPI_PollingMechism PollingEn);
void MCAL_SPI_TXRX(SPI_TypeDef* SPIx,uint16_t* pTxRxBuffer,enum SPI_PollingMechism PollingEn);
























#endif /* INC_STM32F103C6_SPI_DRIVER_H_ */
