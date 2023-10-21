/*
 * LCD_Keypad_Driver.c
 *
 * Created: 6/16/2023 9:26:57 PM
 * Author : Abdelaziz Maher
 */ 

#include "KeyPad/keypad.h"
#include "LCD/lcd.h"

int main(void)
{
    /* Replace with your application code */
	 Keypad_Init();
	 LCD_INIT();
	 
	 char* str1 = "INITILIZATION";
	 char* str2 = "COMPLETE";
	 LCD_GOTO_XY(0, 1);
	 LCD_WRITE_STRING(str1);
	 LCD_GOTO_XY(1, 3);
	 LCD_WRITE_STRING(str2);
	 _delay_ms(2000);
	 LCD_Clear_Screen();
	 
    while (1) 
    {
		unsigned char key_pressed = Keypad_GetKey();
		
		switch(key_pressed)
		{
		default:
			LCD_WRITE_CHAR(key_pressed);
			break;			
		case '!':
			LCD_Clear_Screen();
			break;
		case 'N':
			break;
		}
    }
}

