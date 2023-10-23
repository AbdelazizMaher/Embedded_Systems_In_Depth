/*
 * lcd.c
 *
 * Created: 6/16/2023 9:29:15 PM
 *  Author: Abdelaziz Maher
 */ 

#include "lcd.h"
#include <stdio.h>
#include <string.h>

int Position = 0;

GPIO_PinConfig_t cfg;

void LCD_isbusy(void);
void LCD_Kick(void);
void LCD_IsValid_Position(void);

void _delay_ms(unsigned int t)
{
	unsigned int i , j;
	for( i = 0 ; i < t ; i++ )
		for( j = 0 ; j < 255 ; j++ );
}


void LCD_INIT(void)
{
	//Enable clock
	GPIOA_CLOCK_ENABLE();

	_delay_ms(20);         // LCD power ON delay

	cfg.GPIO_Mode = GPIO_PIN_MODE_OUTPUT_PP;
	cfg.GPIO_Output_Speed = GPIO_PIN_SPEED_10MHZ;
    // CTRL PINS as output
	cfg.GPIO_PinNumber = RS_SWITCH ;
	MCAL_GPIO_Init(LCD_CTRL, &cfg);

	cfg.GPIO_PinNumber = RW_SWITCH ;
	MCAL_GPIO_Init(LCD_CTRL, &cfg);

	cfg.GPIO_PinNumber = EN_SWITCH ;
	MCAL_GPIO_Init(LCD_CTRL, &cfg);
	//Output 0 on ctrl pins
	MCAL_GPIO_WritePin(LCD_CTRL, RS_SWITCH, GPIO_PIN_STATE_RESET);
	MCAL_GPIO_WritePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_STATE_RESET);
	MCAL_GPIO_WritePin(LCD_CTRL, EN_SWITCH, GPIO_PIN_STATE_RESET);

	// Data PINS as output
	cfg.GPIO_PinNumber = DATA_0 ;
	MCAL_GPIO_Init(LCD_PORT, &cfg);

	cfg.GPIO_PinNumber = DATA_1 ;
	MCAL_GPIO_Init(LCD_PORT, &cfg);

	cfg.GPIO_PinNumber = DATA_2 ;
	MCAL_GPIO_Init(LCD_PORT, &cfg);

	cfg.GPIO_PinNumber = DATA_3 ;
	MCAL_GPIO_Init(LCD_PORT, &cfg);

	#ifdef EIGHT_BIT_MODE

		   cfg.GPIO_PinNumber = DATA_4 ;
		   MCAL_GPIO_Init(LCD_PORT, &cfg);

		   cfg.GPIO_PinNumber = DATA_5 ;
		   MCAL_GPIO_Init(LCD_PORT, &cfg);

		   cfg.GPIO_PinNumber = DATA_6 ;
		   MCAL_GPIO_Init(LCD_PORT, &cfg);

		   cfg.GPIO_PinNumber = DATA_7 ;
		   MCAL_GPIO_Init(LCD_PORT, &cfg);


	       LCD_WRITE_COMMAND(LCD_FUNCTION_8BIT_2LINES);
	#endif
	#ifdef FOUR_BIT_MODE
	       LCD_WRITE_COMMAND(0x02);
		   LCD_WRITE_COMMAND(LCD_FUNCTION_4BIT_2LINES);
	#endif
	
	LCD_Clear_Screen();
	LCD_WRITE_COMMAND(LCD_ENTRY_MODE);
	LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW);
	LCD_WRITE_COMMAND(LCD_DISP_ON_CURSOR_BLINK);
}

void LCD_WRITE_COMMAND(unsigned char command)
{
	LCD_isbusy();
	
	#ifdef EIGHT_BIT_MODE
		   MCAL_GPIO_WritePort(LCD_PORT,(uint16_t) command);
		   MCAL_GPIO_WritePin(LCD_CTRL, RS_SWITCH, GPIO_PIN_STATE_RESET);
		   MCAL_GPIO_WritePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_STATE_RESET);

		   LCD_Kick();		
	#endif
	#ifdef FOUR_BIT_MODE
	      // LCD_PORT = (LCD_PORT & 0x0F) | (command & 0xF0);   // Higher Nibble
		   MCAL_GPIO_WritePin(LCD_CTRL, RS_SWITCH, GPIO_PIN_STATE_RESET);
		   MCAL_GPIO_WritePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_STATE_RESET);
	       LCD_Kick();
	      // LCD_PORT = (LCD_PORT & 0x0F) | (command << 4);   // Lower Nibble
		   MCAL_GPIO_WritePin(LCD_CTRL, RS_SWITCH, GPIO_PIN_STATE_RESET);
		   MCAL_GPIO_WritePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_STATE_RESET);
	       LCD_Kick();		   	       
	#endif	
}

void LCD_WRITE_CHAR(unsigned char character)
{
	LCD_isbusy();

	#ifdef EIGHT_BIT_MODE
		   MCAL_GPIO_WritePort(LCD_PORT,(uint16_t) character);
	       MCAL_GPIO_WritePin(LCD_CTRL, RS_SWITCH, GPIO_PIN_STATE_SET);
	       MCAL_GPIO_WritePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_STATE_RESET);

		   LCD_Kick();
	#endif
	#ifdef FOUR_BIT_MODE
	      // LCD_PORT = (LCD_PORT & 0x0F) | (character & 0xF0);   // Higher Nibble
	       MCAL_GPIO_WritePin(LCD_CTRL, RS_SWITCH, GPIO_PIN_STATE_SET);
	       MCAL_GPIO_WritePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_STATE_RESET);
	       LCD_Kick();
	     //  LCD_PORT = (LCD_PORT & 0x0F) | (character << 4);   // Lower Nibble
	       MCAL_GPIO_WritePin(LCD_CTRL, RS_SWITCH, GPIO_PIN_STATE_SET);
	       MCAL_GPIO_WritePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_STATE_RESET);
	       LCD_Kick();	
	#endif

	LCD_IsValid_Position();
}

void LCD_WRITE_STRING(char* string)
{
	while (*string > 0)
		LCD_WRITE_CHAR(*string++);
}

void LCD_isbusy(void)
{
	// Make 7th bit of LCD data port as input
	cfg.GPIO_Mode = GPIO_PIN_MODE_INPUT_FLOA;
	cfg.GPIO_PinNumber = GPIO_PIN_7 ;
	MCAL_GPIO_Init(LCD_PORT, &cfg);

    MCAL_GPIO_WritePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_STATE_SET);       // Read Mode
    MCAL_GPIO_WritePin(LCD_CTRL, RS_SWITCH, GPIO_PIN_STATE_RESET);	   // Select command register

	LCD_Kick();
	#ifdef FOUR_BIT_MODE
		   LCD_Kick();
	#endif

	// Make 7th bit of LCD data port as output
	cfg.GPIO_Mode = GPIO_PIN_MODE_OUTPUT_PP;
	cfg.GPIO_PinNumber = GPIO_PIN_7 ;
	cfg.GPIO_Output_Speed = GPIO_PIN_SPEED_10MHZ;
	MCAL_GPIO_Init(LCD_PORT, &cfg);

	MCAL_GPIO_WritePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_STATE_RESET);      // Write Mode
}

void LCD_Kick(void)
{
	MCAL_GPIO_WritePin(LCD_CTRL, EN_SWITCH, GPIO_PIN_STATE_SET);
	_delay_ms(30);
	MCAL_GPIO_WritePin(LCD_CTRL, EN_SWITCH, GPIO_PIN_STATE_RESET);
}

void LCD_Clear_Screen(void)
{
	Position = 0;
	LCD_WRITE_COMMAND(LCD_CLEAR_SCREEN);
}

void LCD_GOTO_XY(unsigned char Newline, unsigned char NewPosition)
{
	if ( Newline == 0 )
	{
		Position = NewPosition;

		if ( NewPosition < 16 && NewPosition >= 0 )
		{
			LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW + NewPosition);
		}
	}
	else if ( Newline == 1 )
	{
		Position = NewPosition + 16;

		if ( NewPosition < 16 && NewPosition >= 0 )
		{
			LCD_WRITE_COMMAND(LCD_BEGIN_AT_SECOND_ROW + NewPosition);
		}
	}
}

void LCD_IsValid_Position(void)
{
	Position++;

	if (Position == 16)
	{
		LCD_GOTO_XY(1,0);
	}
	else if (Position == 32 )
	{
		LCD_Clear_Screen();
		LCD_GOTO_XY(0,0);
		Position = 0;
	}
}

void LCD_Dispaly_Number(long int number)
{
	char str[16];
	
	sprintf(str,"%li",number);
	
	LCD_WRITE_STRING(str);	
}

void LCD_Dispaly_RealNumber(float number)
{
	char str[16];
	
	char *tmpsign = (number < 0) ? "-" : "";
	float tmpval = (number < 0) ? -number : number;
	
	int tmpint1 = tmpval;
	float tmpfrac = tmpval - tmpint1;
	int tmpint2 = tmpfrac * 1000;
	
	sprintf(str,"%s%d.%03d",tmpsign,tmpint1,tmpint2);
	
	LCD_WRITE_STRING(str);	
}
