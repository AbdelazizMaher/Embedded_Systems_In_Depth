/* LEARN-IN-DEPTH-STM32-CORTEXM3-LED-TOGGLE-STARTUP
 *  BY:ABDELAZIZ MAHER */

#include "Platform_Types.h"

extern int main (void);
void Reset_Handler   (void);

void Default_Handler (void)	{ Reset_Handler(); }

void NMI_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));;
void H_Fault_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));;
void MM_Fault_Handler    (void) __attribute__ ((weak, alias("Default_Handler")));;
void Bus_Fault_Handler   (void) __attribute__ ((weak, alias("Default_Handler")));;
void Usage_Fault_Handler (void) __attribute__ ((weak, alias("Default_Handler")));;

// Booking 1024 byte located by .bss through uninitialized array of uint32 256 element
static uint32_t Stack_Top[256];  //(256*4 = 1024)

void (* const g_p_fn_Vectors[])() __attribute__ ((section(".vectors"))) = 
{
	( void (*)() ) ( uint32_t )Stack_Top + sizeof(Stack_Top),
	&Reset_Handler,
	&NMI_Handler,
	&H_Fault_Handler,
	&MM_Fault_Handler,
	&Bus_Fault_Handler,
	&Usage_Fault_Handler	
};

extern uint32_t _E_text;
extern uint32_t _S_data;
extern uint32_t _E_data;
extern uint32_t _S_bss;
extern uint32_t _E_bss;

void Reset_Handler   (void) 
{
	/* Copy data section from flash to ram */
	uint32_t DATA_size = (uint8_t*)&_E_data - (uint8_t*)&_S_data;
	uint8_t* P_src = (uint8_t*)&_E_text;
	uint8_t* P_dst = (uint8_t*)&_S_data;

	for (uint32_t i = 0; i < DATA_size; i++)
	{
		*((uint8_t*)P_dst++) = *((uint8_t*)P_src++);
	}

	/* Init .bss section in SRAM = 0 */
	uint32_t bss_size = (uint8_t*)&_E_bss - (uint8_t*)&_S_bss;
	P_dst = (uint8_t*)&_S_bss;

	for (uint32_t i = 0; i < bss_size; i++)
	{
		*((uint8_t*)P_dst++) = (uint8_t) 0;
	}

	/* Jump to main */ 
	main();          
}

