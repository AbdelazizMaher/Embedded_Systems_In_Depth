/*
 * lcd.c
 *
 * Created: 6/16/2023 9:29:15 PM
 *  Author: Abdelaziz Maher
 */ 

#include "lcd.h"
#include<stdio.h>
#include <string.h>

int Position = 0;

void LCD_isbusy(void);
void LCD_Kick(void);
void LCD_IsValid_Position(void);

void LCD_INIT(void)
{
	_delay_ms(50);         // LCD power ON delay
	
	LCD_CTRL_DataDir |= ( (1<<RS_SWITCH) | (1<<RW_SWITCH) | (1<<EN_SWITCH) );  
	LCD_CTRL &= ~ ( (1<<RS_SWITCH) | (1<<RW_SWITCH) | (1<<EN_SWITCH) );
	
	#ifdef EIGHT_BIT_MODE	
	        LCD_PORT_DataDir = 0xFF;
	        LCD_WRITE_COMMAND(LCD_FUNCTION_8BIT_2LINES);	
	#endif
	#ifdef FOUR_BIT_MODE
		   LCD_PORT_DataDir |= 0xF0;
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
	       LCD_PORT = command;
	       LCD_CTRL &= ~((1 << RS_SWITCH) | (1<<RW_SWITCH)); 
		   LCD_Kick();		
	#endif
	#ifdef FOUR_BIT_MODE
	       LCD_PORT = (LCD_PORT & 0x0F) | (command & 0xF0);   // Higher Nibble
	       LCD_CTRL &= ~((1 << RS_SWITCH) | (1<<RW_SWITCH));
	       LCD_Kick();
	       LCD_PORT = (LCD_PORT & 0x0F) | (command & 0xF0);   // Lower Nibble
	       LCD_CTRL &= ~((1 << RS_SWITCH) | (1<<RW_SWITCH));
	       LCD_Kick();		   	       
	#endif	
}

void LCD_WRITE_CHAR(unsigned char character)
{
	LCD_isbusy();

	#ifdef EIGHT_BIT_MODE
	       LCD_PORT = character;
		   LCD_CTRL &= ~(1 << RW_SWITCH);
		   LCD_CTRL |= (1 << RS_SWITCH);
		   LCD_Kick();
	#endif
	#ifdef FOUR_BIT_MODE
	       LCD_PORT = (LCD_PORT & 0x0F) | (character & 0xF0);   // Higher Nibble
	       LCD_CTRL &= ~((1 << RS_SWITCH) | (1<<RW_SWITCH));
	       LCD_Kick();
	       LCD_PORT = (LCD_PORT & 0x0F) | (character & 0xF0);   // Lower Nibble
	       LCD_CTRL &= ~((1 << RS_SWITCH) | (1<<RW_SWITCH));
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
	LCD_PORT_DataDir &= ~(0xFF);             // Make 7th bit of LCD data port as input
	LCD_CTRL |=  (1<<RW_SWITCH);     // Read Mode
	LCD_CTRL &= ~(1<<RS_SWITCH);     // Select command register
	
//	while( (PINB>>7) & 1 )                   //read 7th bit again and again till it becomes 0
	{
		LCD_Kick();
	}                              
	
	LCD_PORT_DataDir |= (0xFF);              // Make 7th bit of LCD data port as output
	LCD_CTRL &= ~(1<<RW_SWITCH);     // Write Mode	
}

void LCD_Kick(void)
{
	LCD_CTRL |= (1 << EN_SWITCH);
	_delay_ms(30);
	LCD_CTRL &= ~(1 << EN_SWITCH);	
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