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
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
CAN_HandleTypeDef hcan;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_CAN_Init(void);

/* USER CODE BEGIN PFP */

/* Function to transmit standard CAN frame */
void CAN_TransmitFrame(uint32_t MessgID , uint8_t DLC , uint8_t* DataPacket)
{
	uint8_t NumFreeMailboxes = 0;
	CAN_TxHeaderTypeDef CAN_Frame;
	uint32_t Mailboxes;

	/* Configure the Message frame */
	CAN_Frame.DLC = DLC;
	CAN_Frame.IDE = CAN_ID_STD;
	CAN_Frame.RTR = CAN_RTR_DATA;
	CAN_Frame.StdId = MessgID;

	/* First check if there is any mailbox is free or not */
	NumFreeMailboxes = HAL_CAN_GetTxMailboxesFreeLevel(&hcan);
	/* If there are mailboxes available, start to transmit */
	if(NumFreeMailboxes)
	{
		/* Request a transmission of a new message */
		if ( HAL_CAN_AddTxMessage(&hcan, &CAN_Frame, DataPacket, &Mailboxes) != HAL_OK )
		{
			Error_Handler();
		}

		/* Check if a transmission request is pending on the selected Tx Mailboxes (Wait message in the mailbox transmitted) */
		while( HAL_CAN_IsTxMessagePending(&hcan, Mailboxes) );
	}
}

/* Function to initiate the filter of received messages*/
void CAN_InitReceiveFilter(uint16_t STD_Filter_ID, uint16_t STD_Filter_Mask)
{
	CAN_FilterTypeDef FilterConfiguration;

	FilterConfiguration.FilterActivation = CAN_FILTER_ENABLE;
	FilterConfiguration.FilterBank = 0;
	FilterConfiguration.FilterFIFOAssignment = CAN_FILTER_FIFO0;
	FilterConfiguration.FilterIdHigh = (STD_Filter_ID << 5);
	FilterConfiguration.FilterIdLow = 0x0000;
	FilterConfiguration.FilterMaskIdHigh = (STD_Filter_Mask << 5);
	FilterConfiguration.FilterMaskIdLow = 0x0000;
	FilterConfiguration.FilterMode = CAN_FILTERMODE_IDMASK;
	FilterConfiguration.FilterScale = CAN_FILTERSCALE_32BIT;

	 if ( HAL_CAN_ConfigFilter(&hcan,&FilterConfiguration) != HAL_OK)
	 {
		 Error_Handler();
	 }
}


/* Function to receive standard CAN frame */
void CAN_ReceiveFrame(uint16_t* MessgID , uint8_t* DLC , uint8_t* DataPacket)
{
//    (++) Monitor reception of message using HAL_CAN_GetRxFifoFillLevel() until at least one message is received.
//    (++) Then get the message using HAL_CAN_GetRxMessage().
	CAN_RxHeaderTypeDef CAN_Frame;

//	wait until the fifo sent is filled with at least one frame
	while( HAL_CAN_GetRxFifoFillLevel(&hcan,CAN_FILTER_FIFO0) == 0 );
//	get the message in the fifo we chose
	if ( HAL_CAN_GetRxMessage(&hcan,CAN_FILTER_FIFO0,&CAN_Frame,DataPacket) != HAL_OK)
	{
		Error_Handler();
	}

	*DLC = CAN_Frame.DLC;
	*MessgID = CAN_Frame.StdId;

}


/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_CAN_Init();
	/* Init Can filter Receiver */
	/* Filter message 0x3ff and to receive only this message we should put the mask all ones ( To compare all bits of the ID ) */
	CAN_InitReceiveFilter(0x3ff, 0x7ff);

	/* Start the bxCAN to switch from initialization mode to normal mode */
	if(HAL_CAN_Start(&hcan) != HAL_OK)
	{
		Error_Handler();
	}


	/* Init data to send */
	uint8_t Tx_Data[8] = {'C','A','N',' ','N','o',':',' '};
	uint8_t frameNo = 0;

	/* Init data to receive */
	uint8_t Rx_Data[8] = {0};
	uint16_t Rx_ID;
	uint8_t Rx_DLC;

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1)
	{
		/* USER CODE END WHILE */
		Tx_Data[7] = frameNo++;
		CAN_TransmitFrame(0x3ff, 8, Tx_Data);

		CAN_ReceiveFrame(&Rx_ID, &Rx_DLC, Rx_Data);

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
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
	hcan.Init.AutoRetransmission = ENABLE;
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
	/* USER CODE BEGIN MX_GPIO_Init_1 */
	/* USER CODE END MX_GPIO_Init_1 */

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();

	/* USER CODE BEGIN MX_GPIO_Init_2 */
	/* USER CODE END MX_GPIO_Init_2 */
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
