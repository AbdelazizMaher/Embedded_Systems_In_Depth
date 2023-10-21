/*
 * keypad.c
 *
 * Created: 6/16/2023 11:33:42 PM
 *  Author: Abdelaziz Maher
 */ 

#include "keypad.h"

int Keypad_row[] = {R0 , R1 , R2 , R3};
int Keypad_col[] = {C0 , C1 , C2 , C3};
	
void Keypad_Init(void)
{
	Keypad__PORT_DataDir |= ( (1<<C0) | (1<<C1) | (1<<C2) | (1<<C3) ) ;			// columns as output
	Keypad__PORT_DataDir &= ~( (1<<R0) | (1<<R1) | (1<<R2) | (1<<R3) ) ;		// rows as input
	
	Keypad_PORT = 0xFF;
}

char Keypad_GetKey(void)
{
	int row , column;
	
	for( column = 0 ; column < 4 ; column++ )
	{
		Keypad_PORT |= ( (1<<Keypad_col[0]) | (1<<Keypad_col[1]) | (1<<Keypad_col[2]) | (1<<Keypad_col[3]) ) ;  //Columns output are high
		Keypad_PORT &= ~(1<<Keypad_col[column]);                        
		for( row = 0 ; row < 4 ; row++ )
		{
			if( !(Keypad_PIN & (1<<Keypad_row[row])) )
			{
				while( !(Keypad_PIN & (1<<Keypad_row[row])) );  // wait till it goes high again
				
				switch(column)
				{
				case 0:
					if( row == 0 )return '7';
					else if( row == 1 )return '4';
					else if( row == 2 )return '1';
					else if( row == 3 )return '!';  // clear the screen button
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