/*
 * lcd.h
 *
 * Created: 6/16/2023 9:28:53 PM
 *  Author: Abdelaziz Maher
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "Stm32f103c6_GPIO_Driver.h"

#define LCD_PORT                GPIOA
#define LCD_CTRL                GPIOA

#define DATA_0                  GPIO_PIN_0
#define DATA_1                  GPIO_PIN_1
#define DATA_2                  GPIO_PIN_2
#define DATA_3                  GPIO_PIN_3
#define DATA_4                  GPIO_PIN_4
#define DATA_5                  GPIO_PIN_5
#define DATA_6                  GPIO_PIN_6
#define DATA_7                  GPIO_PIN_7

#define RS_SWITCH 			    GPIO_PIN_8
#define RW_SWITCH               GPIO_PIN_9
#define EN_SWITCH               GPIO_PIN_10

#define EIGHT_BIT_MODE
//#define FOUR_BIT_MODE

#define LCD_FUNCTION_8BIT_2LINES	  					(0x38)
#define LCD_FUNCTION_4BIT_2LINES	  					(0x28)
#define LCD_MOVE_DISP_RIGHT			 					(0x1C)
#define LCD_MOVE_DISP_LEFT   							(0x18)
#define LCD_MOVE_CURSOR_RIGHT							(0x14)
#define LCD_MOVE_CURSOR_LEFT 		  					(0x10)
#define LCD_DISP_OFF   									(0x08)
#define LCD_DISP_ON_CURSOR   							(0x0E)
#define LCD_DISP_ON_CURSOR_BLINK	  					(0x0F)
#define LCD_DISP_ON_BLINK   							(0x0D)
#define LCD_DISP_ON   									(0x0C)
#define LCD_ENTRY_DEC   								(0x04)
#define LCD_ENTRY_DEC_SHIFT   							(0x05)
#define LCD_ENTRY_INC_   								(0x06)
#define LCD_ENTRY_INC_SHIFT   							(0x07)
#define LCD_BEGIN_AT_FIRST_ROW							(0x80)
#define LCD_BEGIN_AT_SECOND_ROW							(0xC0)
#define LCD_CLEAR_SCREEN								(0x01)
#define LCD_ENTRY_MODE									(0x06)


void LCD_INIT(void);
void LCD_WRITE_COMMAND(unsigned char command);
void LCD_WRITE_CHAR(unsigned char character);
void LCD_WRITE_STRING(char* string);
void LCD_Clear_Screen(void);
void LCD_GOTO_XY(unsigned char Newline, unsigned char NewPosition);
void LCD_Dispaly_Number(long int number);
void LCD_Dispaly_RealNumber(float number);

#endif /* LCD_H_ */
