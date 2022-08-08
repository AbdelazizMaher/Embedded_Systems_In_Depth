/* TIVA-C-LED-TOGGLE
 *  BY:ABDELAZIZ MAHER */

#include "Platform_Types.h"


#define SYSCTL_BASE 		        ( uint32_t )0x400FE000
#define GPIOF_BASE 			        ( uint32_t )0x40025000

#define SYSCTL_RCGC2_R 		        *( ( volatile uint32_t* )(SYSCTL_BASE + 0x108) )
#define GPIO_PORTF_DATA_R 	        *( ( volatile uint32_t* )(GPIOF_BASE + 0x3FC) )
#define GPIO_PORTF_DIR_R 	        *( ( volatile uint32_t* )(GPIOF_BASE + 0x400) )
#define GPIO_PORTF_DEN_R	        *( ( volatile uint32_t* )(GPIOF_BASE + 0x51C) )


#define GPIOF_3                     ( 1 << 3 )

int main(void)
{
    volatile unsigned long delay_count;

	SYSCTL_RCGC2_R = 0x20;  // enable clock
	for( delay_count =0 ; delay_count < 200 ; delay_count++);  // delay for stabilization

	GPIO_PORTF_DIR_R |= GPIOF_3;   // Set direction as output
	GPIO_PORTF_DEN_R |= GPIOF_3;   //enable GPIO pin 

	while(1)
	{
		GPIO_PORTF_DATA_R ^= GPIOF_3;      // toggle pin3
		for( delay_count =0 ; delay_count < 20000 ; delay_count++);  // delay
	}

	return 0;
}
