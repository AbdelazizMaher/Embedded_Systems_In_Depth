/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
typedef enum
{
	ENABLE_POLLING,
	DISABLE_POLLING
}eCAN_PollEN;

#define CMD_ACC			1
#define CMD_NO_ACC		0

/* Private variables ---------------------------------------------------------*/
CAN_HandleTypeDef hcan;


/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_CAN_Init(void);

void CAN_Tx( uint32_t StdId, uint32_t DLC, uint8_t*pTxData, eCAN_PollEN CAN_PollEN);
void CAN_Rx( uint32_t *StdId, uint32_t *DLC, uint8_t*pRxData, eCAN_PollEN CAN_PollEN);
void CAN_RX_FilterInit(uint16_t STD_FilterID ,uint16_t STD_FilterMASK);



/* Private user code ---------------------------------------------------------*/

void HAL_CAN_TxMailbox0CompleteCallback(CAN_HandleTypeDef *hcan)
{

}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{

}

void HAL_CAN_ErrorCallback(CAN_HandleTypeDef *hcan)
{
	/*!< TxMailbox 0 transmit failure due to transmit error   */
	if(  (hcan->ErrorCode & HAL_CAN_ERROR_TX_TERR0) == HAL_CAN_ERROR_TX_TERR0 )
	{

	}
}

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* Configure the system clock */
	SystemClock_Config();

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_CAN_Init();

	// Configures the CAN reception filter
	CAN_RX_FilterInit(0x3FF ,0x7FF);

	//    (#) Notifications are activated using HAL_CAN_ActivateNotification()
	//        function.
	if( HAL_CAN_ActivateNotification(&hcan, CAN_IT_TX_MAILBOX_EMPTY | CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK )
	{
		Error_Handler();
	}

	//  (#) Start the CAN module using HAL_CAN_Start() function. At this level
	//      the node is active on the bus: it receive messages, and can send messages.
	HAL_CAN_Start(&hcan);

	uint8_t TX_DATA;

	/* Infinite loop */
	while (1)
	{
		HAL_Delay(1000);
		TX_DATA = CMD_ACC;
		CAN_Tx( 0x030, 1, &TX_DATA, DISABLE_POLLING);

		HAL_Delay(1000);
		TX_DATA = CMD_NO_ACC;
		CAN_Tx( 0x030, 1, &TX_DATA, DISABLE_POLLING);
	}
}


void CAN_Tx( uint32_t StdId, uint32_t DLC, uint8_t*pTxData, eCAN_PollEN CAN_PollEN)
{
	uint32_t No_Of_FreeTxMailboxes = 0 , TxMailbox_Used = 0 ;

	CAN_TxHeaderTypeDef pHeader;
	pHeader.DLC = DLC;
	pHeader.IDE = CAN_ID_STD;
	pHeader.RTR = CAN_RTR_DATA;
	pHeader.StdId = StdId;


	//    (#) Transmission:
	//          (++) Monitor the Tx mailboxes availability until at least one Tx
	//               mailbox is free, using HAL_CAN_GetTxMailboxesFreeLevel().
	//          (++) Then request transmission of a message using
	//               HAL_CAN_AddTxMessage().


	// (++) HAL_CAN_GetTxMailboxesFreeLevel() to get the number of free Tx mailboxes.
	No_Of_FreeTxMailboxes = HAL_CAN_GetTxMailboxesFreeLevel(&hcan);

	if( No_Of_FreeTxMailboxes )
	{
		// (++) HAL_CAN_AddTxMessage() to request transmission of a new message.
		if( HAL_CAN_AddTxMessage(&hcan, &pHeader,pTxData ,&TxMailbox_Used) != HAL_OK )
		{
			Error_Handler();
		}

		if( CAN_PollEN )
		{
			// (++) HAL_CAN_IsTxMessagePending() to check if a message is pending in a Tx mailbox.
			while ( HAL_CAN_IsTxMessagePending(&hcan,TxMailbox_Used) );
		}
	}
}

void CAN_Rx( uint32_t *StdId, uint32_t *DLC, uint8_t*pRxData, eCAN_PollEN CAN_PollEN)
{
	CAN_RxHeaderTypeDef pHeader;

	//    (#) Reception:
	//          (++) Monitor reception of message using HAL_CAN_GetRxFifoFillLevel()
	//               until at least one message is received.
	//          (++) Then get the message using HAL_CAN_GetRxMessage().

	if( CAN_PollEN )
	{
		while( HAL_CAN_GetRxFifoFillLevel(&hcan,CAN_RX_FIFO0) == 0 );
	}

	if( HAL_CAN_GetRxMessage(&hcan, CAN_RX_FIFO0, &pHeader , pRxData) != HAL_OK )
	{
		Error_Handler();
	}

	*StdId = pHeader.StdId;
	*DLC   = pHeader.DLC;
}

void CAN_RX_FilterInit(uint16_t STD_FilterID ,uint16_t STD_FilterMASK)
{
	CAN_FilterTypeDef sFilterConfig;

	sFilterConfig.FilterActivation = CAN_FILTER_ENABLE;
	sFilterConfig.FilterBank = 0;
	sFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
	sFilterConfig.FilterIdHigh = STD_FilterID << 5;
	sFilterConfig.FilterIdLow = 0x0000;
	sFilterConfig.FilterMaskIdHigh = STD_FilterMASK << 5;
	sFilterConfig.FilterMaskIdLow = 0x0000;
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;

	//    (#) Configure the reception filters using the following configuration functions:
	//    		(++) HAL_CAN_ConfigFilter()
	if( HAL_CAN_ConfigFilter(&hcan, &sFilterConfig) != HAL_OK )
	{
		Error_Handler();
	}
}


/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
			|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
	{
		Error_Handler();
	}
}

/**
 * @brief CAN Initialization Function
 * @param None
 * @retval None
 */
static void MX_CAN_Init(void)
{

	/* USER CODE BEGIN CAN_Init 0 */

	/* USER CODE END CAN_Init 0 */

	/* USER CODE BEGIN CAN_Init 1 */

	/* USER CODE END CAN_Init 1 */
	hcan.Instance = CAN1;
	hcan.Init.Prescaler = 1;
	hcan.Init.Mode = CAN_MODE_LOOPBACK;
	hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
	hcan.Init.TimeSeg1 = CAN_BS1_6TQ;
	hcan.Init.TimeSeg2 = CAN_BS2_1TQ;
	hcan.Init.TimeTriggeredMode = DISABLE;
	hcan.Init.AutoBusOff = DISABLE;
	hcan.Init.AutoWakeUp = DISABLE;
	hcan.Init.AutoRetransmission = DISABLE;
	hcan.Init.ReceiveFifoLocked = DISABLE;
	hcan.Init.TransmitFifoPriority = DISABLE;
	if (HAL_CAN_Init(&hcan) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN CAN_Init 2 */

	/* USER CODE END CAN_Init 2 */

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void)
{

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1)
	{
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
