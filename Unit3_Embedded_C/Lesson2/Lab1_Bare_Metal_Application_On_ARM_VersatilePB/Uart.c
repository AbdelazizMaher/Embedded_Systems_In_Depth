#include "Uart.h"

#define UART0_BASE   ( unsigned int )(0x101f1000)
#define UART0DR      *( ( volatile unsigned int* const)( UART0_BASE + 0x0 ) )

void Uart_Send_String(unsigned char* P_tx_string)
{
	while( *P_tx_string |= 0 )
	{
		UART0DR = (unsigned int)(*P_tx_string);
		P_tx_string++;
	}
}
