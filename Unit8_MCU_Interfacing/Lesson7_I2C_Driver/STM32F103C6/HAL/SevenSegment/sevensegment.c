/*
 * sevensegment.c
 *
 *  Created on: Oct 22, 2023
 *      Author: Abdelaziz Maher
 */


#include "sevensegment.h"


void SevSegment_Init(void)
{
	//Enable clock
	GPIOB_CLOCK_ENABLE();

	GPIO_PinConfig_t cfg;

	cfg.GPIO_Mode = GPIO_PIN_MODE_OUTPUT_PP;
	cfg.GPIO_Output_Speed = GPIO_PIN_SPEED_10MHZ;

	cfg.GPIO_PinNumber = A ;
	MCAL_GPIO_Init(SevSeg_Port, &cfg);

	cfg.GPIO_PinNumber = B ;
	MCAL_GPIO_Init(SevSeg_Port, &cfg);

	cfg.GPIO_PinNumber = C ;
	MCAL_GPIO_Init(SevSeg_Port, &cfg);

	cfg.GPIO_PinNumber = D ;
	MCAL_GPIO_Init(SevSeg_Port, &cfg);

	cfg.GPIO_PinNumber = E ;
	MCAL_GPIO_Init(SevSeg_Port, &cfg);

	cfg.GPIO_PinNumber = F ;
	MCAL_GPIO_Init(SevSeg_Port, &cfg);

	cfg.GPIO_PinNumber = G ;
	MCAL_GPIO_Init(SevSeg_Port, &cfg);

}


void SevSegment_Write_Num(int num)
{
	//Common Anode
	switch(num)
	{
	case 0:
		MCAL_GPIO_WritePin(SevSeg_Port, A, GPIO_PIN_STATE_RESET);
		MCAL_GPIO_WritePin(SevSeg_Port, B, GPIO_PIN_STATE_RESET);
		MCAL_GPIO_WritePin(SevSeg_Port, C, GPIO_PIN_STATE_RESET);
		MCAL_GPIO_WritePin(SevSeg_Port, D, GPIO_PIN_STATE_RESET);
		MCAL_GPIO_WritePin(SevSeg_Port, E, GPIO_PIN_STATE_RESET);
		MCAL_GPIO_WritePin(SevSeg_Port, F, GPIO_PIN_STATE_RESET);
		MCAL_GPIO_WritePin(SevSeg_Port, G, GPIO_PIN_STATE_SET);
		break;
	case 1:
		MCAL_GPIO_WritePin(SevSeg_Port, A, GPIO_PIN_STATE_SET);
		MCAL_GPIO_WritePin(SevSeg_Port, B, GPIO_PIN_STATE_RESET);
		MCAL_GPIO_WritePin(SevSeg_Port, C, GPIO_PIN_STATE_RESET);
		MCAL_GPIO_WritePin(SevSeg_Port, D, GPIO_PIN_STATE_SET);
		MCAL_GPIO_WritePin(SevSeg_Port, E, GPIO_PIN_STATE_SET);
		MCAL_GPIO_WritePin(SevSeg_Port, F, GPIO_PIN_STATE_SET);
		MCAL_GPIO_WritePin(SevSeg_Port, G, GPIO_PIN_STATE_SET);
		break;
	case 2:
		MCAL_GPIO_WritePin(SevSeg_Port, A, GPIO_PIN_STATE_RESET);
		MCAL_GPIO_WritePin(SevSeg_Port, B, GPIO_PIN_STATE_RESET);
		MCAL_GPIO_WritePin(SevSeg_Port, C, GPIO_PIN_STATE_SET);
		MCAL_GPIO_WritePin(SevSeg_Port, D, GPIO_PIN_STATE_RESET);
		MCAL_GPIO_WritePin(SevSeg_Port, E, GPIO_PIN_STATE_RESET);
		MCAL_GPIO_WritePin(SevSeg_Port, F, GPIO_PIN_STATE_SET);
		MCAL_GPIO_WritePin(SevSeg_Port, G, GPIO_PIN_STATE_RESET);
		break;
	case 3:
		MCAL_GPIO_WritePin(SevSeg_Port, A, GPIO_PIN_STATE_RESET);
		MCAL_GPIO_WritePin(SevSeg_Port, B, GPIO_PIN_STATE_RESET);
		MCAL_GPIO_WritePin(SevSeg_Port, C, GPIO_PIN_STATE_RESET);
		MCAL_GPIO_WritePin(SevSeg_Port, D, GPIO_PIN_STATE_RESET);
		MCAL_GPIO_WritePin(SevSeg_Port, E, GPIO_PIN_STATE_SET);
		MCAL_GPIO_WritePin(SevSeg_Port, F, GPIO_PIN_STATE_SET);
		MCAL_GPIO_WritePin(SevSeg_Port, G, GPIO_PIN_STATE_RESET);
		break;
	case 4:
		MCAL_GPIO_WritePin(SevSeg_Port, A, GPIO_PIN_STATE_SET);
		MCAL_GPIO_WritePin(SevSeg_Port, B, GPIO_PIN_STATE_RESET);
		MCAL_GPIO_WritePin(SevSeg_Port, C, GPIO_PIN_STATE_RESET);
		MCAL_GPIO_WritePin(SevSeg_Port, D, GPIO_PIN_STATE_SET);
		MCAL_GPIO_WritePin(SevSeg_Port, E, GPIO_PIN_STATE_SET);
		MCAL_GPIO_WritePin(SevSeg_Port, F, GPIO_PIN_STATE_RESET);
		MCAL_GPIO_WritePin(SevSeg_Port, G, GPIO_PIN_STATE_RESET);
		break;
	case 5:
		MCAL_GPIO_WritePin(SevSeg_Port, A, GPIO_PIN_STATE_RESET);
		MCAL_GPIO_WritePin(SevSeg_Port, B, GPIO_PIN_STATE_SET);
		MCAL_GPIO_WritePin(SevSeg_Port, C, GPIO_PIN_STATE_RESET);
		MCAL_GPIO_WritePin(SevSeg_Port, D, GPIO_PIN_STATE_RESET);
		MCAL_GPIO_WritePin(SevSeg_Port, E, GPIO_PIN_STATE_SET);
		MCAL_GPIO_WritePin(SevSeg_Port, F, GPIO_PIN_STATE_RESET);
		MCAL_GPIO_WritePin(SevSeg_Port, G, GPIO_PIN_STATE_RESET);
		break;
	case 6:
		MCAL_GPIO_WritePin(SevSeg_Port, A, GPIO_PIN_STATE_RESET);
		MCAL_GPIO_WritePin(SevSeg_Port, B, GPIO_PIN_STATE_SET);
		MCAL_GPIO_WritePin(SevSeg_Port, C, GPIO_PIN_STATE_RESET);
		MCAL_GPIO_WritePin(SevSeg_Port, D, GPIO_PIN_STATE_RESET);
		MCAL_GPIO_WritePin(SevSeg_Port, E, GPIO_PIN_STATE_RESET);
		MCAL_GPIO_WritePin(SevSeg_Port, F, GPIO_PIN_STATE_RESET);
		MCAL_GPIO_WritePin(SevSeg_Port, G, GPIO_PIN_STATE_RESET);
		break;
	case 7:
		MCAL_GPIO_WritePin(SevSeg_Port, A, GPIO_PIN_STATE_RESET);
		MCAL_GPIO_WritePin(SevSeg_Port, B, GPIO_PIN_STATE_RESET);
		MCAL_GPIO_WritePin(SevSeg_Port, C, GPIO_PIN_STATE_RESET);
		MCAL_GPIO_WritePin(SevSeg_Port, D, GPIO_PIN_STATE_SET);
		MCAL_GPIO_WritePin(SevSeg_Port, E, GPIO_PIN_STATE_SET);
		MCAL_GPIO_WritePin(SevSeg_Port, F, GPIO_PIN_STATE_SET);
		MCAL_GPIO_WritePin(SevSeg_Port, G, GPIO_PIN_STATE_SET);
		break;
	case 8:
		MCAL_GPIO_WritePin(SevSeg_Port, A, GPIO_PIN_STATE_RESET);
		MCAL_GPIO_WritePin(SevSeg_Port, B, GPIO_PIN_STATE_RESET);
		MCAL_GPIO_WritePin(SevSeg_Port, C, GPIO_PIN_STATE_RESET);
		MCAL_GPIO_WritePin(SevSeg_Port, D, GPIO_PIN_STATE_RESET);
		MCAL_GPIO_WritePin(SevSeg_Port, E, GPIO_PIN_STATE_RESET);
		MCAL_GPIO_WritePin(SevSeg_Port, F, GPIO_PIN_STATE_RESET);
		MCAL_GPIO_WritePin(SevSeg_Port, G, GPIO_PIN_STATE_RESET);
		break;
	case 9:
		MCAL_GPIO_WritePin(SevSeg_Port, A, GPIO_PIN_STATE_RESET);
		MCAL_GPIO_WritePin(SevSeg_Port, B, GPIO_PIN_STATE_RESET);
		MCAL_GPIO_WritePin(SevSeg_Port, C, GPIO_PIN_STATE_RESET);
		MCAL_GPIO_WritePin(SevSeg_Port, D, GPIO_PIN_STATE_RESET);
		MCAL_GPIO_WritePin(SevSeg_Port, E, GPIO_PIN_STATE_SET);
		MCAL_GPIO_WritePin(SevSeg_Port, F, GPIO_PIN_STATE_RESET);
		MCAL_GPIO_WritePin(SevSeg_Port, G, GPIO_PIN_STATE_RESET);
		break;
	default:
		break;
	}

}
