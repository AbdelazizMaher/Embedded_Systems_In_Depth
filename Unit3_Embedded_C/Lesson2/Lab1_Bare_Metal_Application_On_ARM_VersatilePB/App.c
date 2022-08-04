#include "Uart.h"

unsigned char string_buffer[100] = "learn-in-depth :<Abdelaziz>";

int main()
{
	Uart_Send_String(string_buffer);

	return 0;
}
