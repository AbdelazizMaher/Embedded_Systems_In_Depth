/* STM32-CORTEXM3-LED-TOGGLE
 *  BY:ABDELAZIZ MAHER */

#include "Platform_Types.h"

#define RCC_BASE                    ( uint32_t )0x40021000
#define GPIOA_BASE                  ( uint32_t )0x40010800

#define RCC_APB2ENR                 *( ( volatile uint32_t* )( RCC_BASE + 0x18 ) )
#define GPIOA_CRH                   *( ( volatile uint32_t* )( GPIOA_BASE + 0x04 ) )
#define GPIOA_ODR                   *( ( volatile uint32_t* )( GPIOA_BASE + 0x0C ) )

#define RCC_IOPAEN                  ( 1 << 2 )
#define GPIOA_13                    ( 1 << 13 )
typedef union
{
	vuint32_t   all_fields;
	struct
	{
		vuint32_t   reserved:13;
		vuint32_t   Pin_13:1;
	}Pin;
}R_ODR_t;

volatile R_ODR_t* R_ODR = ( volatile R_ODR_t* )( GPIOA_BASE + 0x0C );

int main(void)
{
	RCC_APB2ENR |= RCC_IOPAEN;  // enable clock

	GPIOA_CRH &= ~( 7 << 20 );
	GPIOA_CRH |= ( 2 << 20 );   //enable pin as output

	while(1)
	{
		//GPIOA_ODR ^= GPIOA_13;      // toggle pin13
		R_ODR->Pin.Pin_13 ^= 1;
		for( int i =0 ; i < 5000 ; i++);  // delay
	}

	for(;;);
}
