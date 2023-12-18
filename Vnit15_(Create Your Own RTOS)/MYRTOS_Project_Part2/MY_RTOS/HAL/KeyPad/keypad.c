/*
 * keypad.c
 *
 * Created: 6/16/2023 11:33:42 PM
 *  Author: Abdelaziz Maher
 */ 

#include "keypad.h"

int Keypad_row[] = {KeyPad_R0 , KeyPad_R1 , KeyPad_R2 , KeyPad_R3};
int Keypad_col[] = {KeyPad_C0 , KeyPad_C1 , KeyPad_C2 , KeyPad_C3};
	
void Keypad_Init(void)
{
	// Enable clock
	GPIOB_CLOCK_ENABLE();

	GPIO_PinConfig_t cfg;

	// columns as outputs
	cfg.GPIO_Mode = GPIO_PIN_MODE_OUTPUT_PP;
	cfg.GPIO_Output_Speed = GPIO_PIN_SPEED_10MHZ;

	cfg.GPIO_PinNumber = KeyPad_C0 ;
	MCAL_GPIO_Init(KeyPad_PORT, &cfg);

	cfg.GPIO_PinNumber = KeyPad_C1 ;
	MCAL_GPIO_Init(KeyPad_PORT, &cfg);

	cfg.GPIO_PinNumber = KeyPad_C2 ;
	MCAL_GPIO_Init(KeyPad_PORT, &cfg);

	cfg.GPIO_PinNumber = KeyPad_C3;
	MCAL_GPIO_Init(KeyPad_PORT, &cfg);

	// rows as inputs
	cfg.GPIO_Mode = GPIO_PIN_MODE_INPUT_PD;

	cfg.GPIO_PinNumber = KeyPad_R0;
	MCAL_GPIO_Init(KeyPad_PORT, &cfg);

	cfg.GPIO_PinNumber = KeyPad_R1;
	MCAL_GPIO_Init(KeyPad_PORT, &cfg);

	cfg.GPIO_PinNumber = KeyPad_R2;
	MCAL_GPIO_Init(KeyPad_PORT, &cfg);

	cfg.GPIO_PinNumber = KeyPad_R3;
	MCAL_GPIO_Init(KeyPad_PORT, &cfg);
}

char Keypad_GetKey(void)
{
	int row , column;
	
	for( column = 0 ; column < 4 ; column++ )
	{
		//Columns output are high
		MCAL_GPIO_WritePin(KeyPad_PORT, Keypad_col[0], GPIO_PIN_STATE_RESET);
		MCAL_GPIO_WritePin(KeyPad_PORT, Keypad_col[1], GPIO_PIN_STATE_RESET);
		MCAL_GPIO_WritePin(KeyPad_PORT, Keypad_col[2], GPIO_PIN_STATE_RESET);
		MCAL_GPIO_WritePin(KeyPad_PORT, Keypad_col[3], GPIO_PIN_STATE_RESET);

		MCAL_GPIO_WritePin(KeyPad_PORT, Keypad_col[column], GPIO_PIN_STATE_SET);

		for( row = 0 ; row < 4 ; row++ )
		{
			if(  MCAL_GPIO_ReadPin(KeyPad_PORT, Keypad_row[row]) == GPIO_PIN_STATE_SET )
			{
				while(  MCAL_GPIO_ReadPin(KeyPad_PORT, Keypad_row[row]) == GPIO_PIN_STATE_SET );  // wait till it goes low again
				
				switch(column)
				{
				case 0:
					if( row == 0 )return '7';
					else if( row == 1 )return '4';
					else if( row == 2 )return '1';
					else if( row == 3 )return '!';  // clear the screen
					break;
				
				case 1:
					if( row == 0 )return '8';
					else if( row == 1 )return '5';
					else if( row == 2 )return '2';
					else if( row == 3 )return '0';
					break;	
				
				case 2:
					if( row == 0 )return '9';
					else if( row == 1 )return '6';
					else if( row == 2 )return '3';
					else if( row == 3 )return '=';
					break;
				
				case 3:
					if( row == 0 )return '/';
					else if( row == 1 )return '*';
					else if( row == 2 )return '-';
					else if( row == 3 )return '+';
					break;											
				}		
			}		
		}			
	}
	return 'N'; // Return 'N' if no key is pressed	
}
