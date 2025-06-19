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
#include "string.h"
#include "stdio.h"
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
CAN_HandleTypeDef hcan1;

UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart2_tx;
DMA_HandleTypeDef hdma_usart2_rx;

/* USER CODE BEGIN PV */
//Error Handler
uint8_t ErrorHandler_Code=0;
//UART vars
uint8_t str_Tx[]=" CAN project USART Transmit!!!";
uint8_t str_Rx[50];
uint8_t str_Tx_DMA[]=" CAN project USART_DMA Transmit!!!";
uint8_t str_Rx_DMA[8];
uint8_t str_Tx_DMA_HalfReciveI[] = "IRQ!!!_USART_DMA_HalfRecive Complete";
uint8_t str_Tx_DMA_HalfRecive[] = "USART_DMA_HalfRecive Complete";

//CAN vars
CAN_TxHeaderTypeDef TxHeader1;
CAN_RxHeaderTypeDef RxHeader1;
CAN_FilterTypeDef sFilterConfig;
uint8_t CAN_Tx_Arr[] = {0,1,2,3,4,5,6,255};
uint8_t CAN_Tx_Arr2[] = {0xFF,0xEE,0xDD,0xCC,0xBB,0xAA,0x99,0x88};
uint8_t CAN_Rx_Arr[8] = {0,0,0,0,0,0,0,0};
uint32_t pTxMailbox;
uint32_t RxFifo;

//MyFifoBuf vars

CANMsgRx CANMsgRxBuf[CANMSGRXBUFSIZE];
CANMsgTx CANMsgTxBuf[CANMSGTXBUFSIZE];
PCMsg PCMsgRxBuf[PCMSGRXBUFSIZE];
PCMsg PCMsgTxBuf[PCMSGTXBUFSIZE];
CANtoPCMsg CANtoPCMsgBuf[CANTOPCMSGBUFSIZE];
PCtoCANMsg PCtoCANMsgBuf[PCTOCANMSGBUFSIZE];
CANlimMsg CANlimMsgBuf[CANLIMMSGBUFSIZE];

uint8_t CANtoPCMsgBufHead=0;
uint8_t CANtoPCMsgBufTail=0;
uint8_t CANtoPCMsgBufOverFlowFlag=0;

uint8_t PCtoCANMsgBufHead=0;
uint8_t PCtoCANMsgBufTail=0;
uint8_t PCtoCANMsgBufOverFlowFlag=0;

uint8_t CANlimMsgBufHead=0;
uint8_t CANlimMsgBufTail=0;
uint8_t CANlimMsgBufOverFlowFlag=0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_CAN1_Init(void);
/* USER CODE BEGIN PFP */
//void User_UartCompleteCallback(UART_HandleTypeDef *huart);//��������������� weak-������� ����������� ���������� ������ UART
//void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart);//��������������� weak-������� ����������� ���������� ������ �������� ���
__inline void CANtoPCBuf_processing();
__inline void PCtoCANBuf_processing();

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/*
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)//��������������� weak-������� ����������� ���������� ������ UART
{
	if (huart==&huart2)
	{
		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
		HAL_UART_Transmit_IT(&huart2, str_Rx, sizeof(str_Rx));
	}
}
*/
/*
void User_UartCompleteCallback(UART_HandleTypeDef *huart)//���������� ���������������� ������� ��������� ����������
{
	char msg[]="User_UartCompleteCallback";
		HAL_UART_Transmit(huart, msg, sizeof(msg), 1000);
}
*/
/*
void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart)//��������������� weak-������� ����������� ���������� ������ �������� ���
{
	if(huart == &huart2)
		HAL_UART_Transmit_DMA(huart, str_Tx_DMA_HalfRecive, sizeof(str_Tx_DMA_HalfRecive));//�� ��� ��� ������� ����� ������ �������������� ��� � ������� ��������� ����������
}
*/


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
  MX_DMA_Init();
  MX_USART2_UART_Init();
  MX_CAN1_Init();
  /* USER CODE BEGIN 2 */
  //TxHeader1.StdId = 0x123;
  //TxHeader1.RTR = CAN_RTR_DATA;
  //TxHeader1.IDE = CAN_ID_STD;
  //TxHeader1.DLC = 8;
  //TxHeader1.TransmitGlobalTime = DISABLE;

  CAN_FilterTypeDef canFilterConfig;
  canFilterConfig.FilterBank = 0;
  canFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
  canFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
  canFilterConfig.FilterIdHigh = 0x0000;
  canFilterConfig.FilterIdLow = 0x0000;
  canFilterConfig.FilterMaskIdHigh = 0x0000;
  canFilterConfig.FilterMaskIdLow = 0x0000;
  canFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
  canFilterConfig.FilterActivation = ENABLE;
  canFilterConfig.SlaveStartFilterBank = 14;
  HAL_CAN_ConfigFilter(&hcan1, &canFilterConfig);

  if(HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING)!= HAL_OK) {Error_Handler();};//���������� ������� �������� ���������� � ���������� ���
  if(HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_FULL)!= HAL_OK) {Error_Handler();};
  if(HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO1_MSG_PENDING)!= HAL_OK) {Error_Handler();};//���������� ������� �������� ���������� � ���������� ���
  if(HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO1_FULL)!= HAL_OK) {Error_Handler();};
  if(HAL_CAN_Start(&hcan1) != HAL_OK) {Error_Handler();};

  //HAL_UART_RegisterCallback(&huart2, HAL_UART_RX_COMPLETE_CB_ID, User_UartCompleteCallback);//���������� ���� ������� �� �������� � �� ������� �����������
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  uint8_t size = sizeof(CANlimMsg_TxSize);
  HAL_UART_Transmit(&huart2, &size, 4, 1000);

  PCtoCANMsg * PCtoCANmsg_ptr = &PCtoCANMsgBuf[0];
  if(HAL_UART_Receive_IT(&huart2, (uint8_t *)PCtoCANmsg_ptr, sizeof(PCtoCANMsg))!=HAL_OK)
	  Error_Handler();

  	//HAL_CAN_GetRxMessage(&hcan1, RxFifo, &CANtoPCMsgBuf[0].CANMsg.RxHeader, (uint8_t*)(&CANtoPCMsgBuf[0].CANMsg.CAN_Rx_Arr));

/*
  if(HAL_CAN_AddTxMessage(&hcan1, &TxHeader1, CAN_Tx_Arr, &pTxMailbox)!=HAL_OK)
	   Error_Handler();
  HAL_Delay(10);
  if(HAL_CAN_AddTxMessage(&hcan1, &TxHeader1, CAN_Tx_Arr2, &pTxMailbox)!=HAL_OK)
  	   Error_Handler();
  HAL_Delay(10);*/
  while (1)
  {
	  //HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);

	  //������������ UART
	  //TX(�� �����) 11- 14 - 5- RX(���������) ������//��� rs232 - 2

	  //HAL_UART_Receive (&huart2, str_Rx, sizeof(str_Rx), 10000);//��������� �� ������ �� ���� ������� ���� �� ������� ��� �����
	  //HAL_UART_Receive_IT (&huart2, str_Rx, sizeof(str_Rx));//� ����� ��������� ������ �������� �������� ��������� ���� ���� � ����� ������ �� ����� �����
	  //HAL_UART_Receive_DMA(&huart2, str_Rx_DMA, sizeof(str_Rx_DMA));
	  //HAL_Delay(1000);
	  //HAL_UART_Transmit(&huart2, str_Tx, sizeof(str_Tx), 10000);
	  //HAL_UART_Transmit_IT(&huart2, str_Tx, sizeof(str_Tx));
	  //HAL_UART_Transmit_DMA(&huart2, str_Tx_DMA, sizeof(str_Tx_DMA));

	  //������������ CAN
	  //if(HAL_CAN_AddTxMessage(&hcan1, &TxHeader1, CAN_Tx_Arr, &pTxMailbox)!=HAL_OK)
		  //Error_Handler();
	  //HAL_Delay(100);
	  //if(HAL_CAN_GetRxMessage(&hcan1, RxFifo, &RxHeader1, CAN_Rx_Arr)!=HAL_OK)
	  		//Error_Handler();
	  //HAL_Delay(3000);
	  //HAL_UART_Transmit_IT(&huart2, (uint8_t *) &RxHeader1, sizeof(RxHeader1));
	  //HAL_Delay(100);
	  //HAL_UART_Transmit_IT(&huart2, CAN_Rx_Arr, RxHeader1.DLC);

	  //HAL_UART_Transmit_IT(&huart2, &RxBuf[0].RxHeader, (uint8_t *) RxBuf[0].CAN_Rx_Arr);
	  //HAL_UART_Transmit_IT(&huart2, (uint8_t*)&CANMsgRxBuf[0].RxHeader, sizeof(RxHeader1));
	  //HAL_Delay(100);
	  //HAL_UART_Transmit_IT(&huart2, (uint8_t*) &CANMsgRxBuf[0].CAN_Rx_Arr, 8);
	  //HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
	  //HAL_UART_RxCpltCallback(&huart2);


	  //--------------------------------------------------------
	  //�������� ��� ��������� ��� �����
/*
	  if(HAL_CAN_AddTxMessage(&hcan1, &TxHeader1, CAN_Tx_Arr, &pTxMailbox)!=HAL_OK)
		   Error_Handler();
	  HAL_Delay(10);
	  if(HAL_CAN_AddTxMessage(&hcan1, &TxHeader1, CAN_Tx_Arr, &pTxMailbox)!=HAL_OK)
	  	   Error_Handler();
	  HAL_Delay(10);
	  	  if(HAL_CAN_AddTxMessage(&hcan1, &TxHeader1, CAN_Tx_Arr2, &pTxMailbox)!=HAL_OK)
	  	  	   Error_Handler();
	  HAL_Delay(10);
	  	if(HAL_CAN_AddTxMessage(&hcan1, &TxHeader1, CAN_Tx_Arr2, &pTxMailbox)!=HAL_OK)
	  		  Error_Handler();
	  HAL_Delay(10);
*/
	   //-----------------------------------------------------

	  //HW Test
/*
	  HAL_Delay(100);
	  HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
	  HAL_UART_Transmit(&huart2, (uint8_t*)"Hello!", sizeof("Hello!"), 1000);*/
	  CANtoPCBuf_processing();//��������� ������ �������� ��������� �� PC	PCBuf_processing();
	  //HAL_Delay(100);
	  PCtoCANBuf_processing();//��������� ������ �������� ��������� �� CAN CANBuf_processing();
	  //HAL_Delay(100);
	  if(overrun_PCtoCANMsgBuf()||overrun_CANtoPCMsgBuf()||overrun_CANlimMsgBuf())
		  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 1);
	  //*/------------------------------------------------------------

    /* USER CODE END WHILE */

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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.Prediv1Source = RCC_PREDIV1_SOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  RCC_OscInitStruct.PLL2.PLL2State = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure the Systick interrupt time
  */
  __HAL_RCC_PLLI2S_ENABLE();
}

/**
  * @brief CAN1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN1_Init(void)
{

  /* USER CODE BEGIN CAN1_Init 0 */

  /* USER CODE END CAN1_Init 0 */

  /* USER CODE BEGIN CAN1_Init 1 */

  /* USER CODE END CAN1_Init 1 */
  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 8;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_7TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_1TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = DISABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = DISABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN1_Init 2 */

  /* USER CODE END CAN1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 921600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel6_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel6_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel6_IRQn);
  /* DMA1_Channel7_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel7_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel7_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */
  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : LED_Pin */
  GPIO_InitStruct.Pin = LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */
  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void PCtoCANBuf_processing()
{
	static PCtoCANMsg * PCtoCANmsg_ptr = NULL;
	if(avaibleForRead_PCtoCANMsgBuf())
	{
		NVIC_DisableIRQ(USART2_IRQn);
		PCtoCANmsg_ptr = directRead_PCtoCANMsgBuf();

		//��������� PC_toCAN
		if(PCtoCANmsg_ptr->msgType==PC_toCAN)
			//HAL_UART_Transmit(&huart2, PCtoCANmsg_ptr, sizeof(PCtoCANMsg), 1000);
			if(HAL_CAN_AddTxMessage(&hcan1, &PCtoCANmsg_ptr->CANMsg.TxHeader, (uint8_t*)PCtoCANmsg_ptr->CANMsg.CAN_Tx_Arr, &pTxMailbox)!=HAL_OK){Error_Handler();}//�������� � CAN

		//��������� PC_toCAN_State
		if(PCtoCANmsg_ptr->msgType==PC_toCAN_State)
		{
			PCtoCANMsgCANConf* MsgCANConf;
			PCtoCANMsgCANFiltIDConf* CANMsgCANFiltIDConf;
			MsgCANConf = (PCtoCANMsgCANConf*)PCtoCANmsg_ptr;
			CANMsgCANFiltIDConf = (PCtoCANMsgCANFiltIDConf*)PCtoCANmsg_ptr;

			PCtoCANMsgCANConf CANMsgCANConf_test= *MsgCANConf;
			PCtoCANMsgCANFiltIDConf CANMsgCANFiltIDConf_test= *CANMsgCANFiltIDConf;

			switch(MsgCANConf->Communication)
			{
			case 0://Disconnect - ���������� CAN
			//if(MsgCANConf->Communication==0)//Disconnect - ���������� CAN
			{
				if(HAL_CAN_Stop(&hcan1)!= HAL_OK) {Error_Handler();}
				if(HAL_CAN_DeInit(&hcan1)!= HAL_OK) {Error_Handler();}
				break;
			}
			case 1://Connect - ��������� CAN
			//if(MsgCANConf->Communication==1)//Connect - ��������� CAN
			{
				if (HAL_CAN_Init(&hcan1) != HAL_OK) {Error_Handler();}
				if(HAL_CAN_Start(&hcan1) != HAL_OK) {Error_Handler();};
				if(HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING)!= HAL_OK) {Error_Handler();}
				if(HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_FULL)!= HAL_OK) {Error_Handler();}
				if(HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO1_MSG_PENDING)!= HAL_OK) {Error_Handler();}
				if(HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO1_FULL)!= HAL_OK) {Error_Handler();}
				break;
			}
			case 2://Reset - �������� CAN
			{
				if(HAL_CAN_Stop(&hcan1)!= HAL_OK) {Error_Handler();}
				if(HAL_CAN_DeInit(&hcan1)!= HAL_OK) {Error_Handler();}
				if (HAL_CAN_Init(&hcan1) != HAL_OK) {Error_Handler();}
				if(HAL_CAN_Start(&hcan1) != HAL_OK) {Error_Handler();};
				if(HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING)!= HAL_OK) {Error_Handler();}
				if(HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_FULL)!= HAL_OK) {Error_Handler();}
				if(HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO1_MSG_PENDING)!= HAL_OK) {Error_Handler();}
				if(HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO1_FULL)!= HAL_OK) {Error_Handler();}
				break;
			}
			case 3://Init - ��������� CAN
			//if(MsgCANConf->Communication==2)//Init - ��������� CAN
			{
				if(HAL_CAN_Stop(&hcan1)!= HAL_OK) {Error_Handler();}
				if(HAL_CAN_DeInit(&hcan1)!= HAL_OK) {Error_Handler();}

				hcan1.Instance = CAN1;//MsgCANConf->Instance;
				hcan1.Init.Prescaler = MsgCANConf->Prescaler;
				hcan1.Init.Mode = MsgCANConf->Mode;
				hcan1.Init.SyncJumpWidth = MsgCANConf->SyncJumpWidth;
				hcan1.Init.TimeSeg1 = MsgCANConf->TimeSeg1;
				hcan1.Init.TimeSeg2 = MsgCANConf->TimeSeg2;
				hcan1.Init.TimeTriggeredMode = MsgCANConf->TimeTriggeredMode;
				hcan1.Init.AutoBusOff = MsgCANConf->AutoBusOff;
				hcan1.Init.AutoWakeUp = MsgCANConf->AutoWakeUp;
				hcan1.Init.AutoRetransmission = MsgCANConf->AutoRetransmission;
				hcan1.Init.ReceiveFifoLocked = MsgCANConf->ReceiveFifoLocked;
				hcan1.Init.TransmitFifoPriority = MsgCANConf->TransmitFifoPriority;;
				if (HAL_CAN_Init(&hcan1) != HAL_OK) {Error_Handler();}

				if(HAL_CAN_Start(&hcan1) != HAL_OK) {Error_Handler();};
				if(HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING)!= HAL_OK) {Error_Handler();}
				if(HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_FULL)!= HAL_OK) {Error_Handler();}
				if(HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO1_MSG_PENDING)!= HAL_OK) {Error_Handler();}
				if(HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO1_FULL)!= HAL_OK) {Error_Handler();}
				break;
			}
			case 4://FilterConf - ��������� CAN ������
			//if(MsgCANConf->Communication==3)//FilterConf - ��������� CAN ������
			{
				CAN_FilterTypeDef canFilterConfig;
				canFilterConfig.FilterBank = CANMsgCANFiltIDConf->FilterBank;
				canFilterConfig.FilterMode = CANMsgCANFiltIDConf->FilterMode;
				canFilterConfig.FilterScale = CANMsgCANFiltIDConf->FilterScale;
				canFilterConfig.FilterIdHigh = CANMsgCANFiltIDConf->FilterMaskIdHigh;
				canFilterConfig.FilterIdLow = CANMsgCANFiltIDConf->FilterIdLow;
				canFilterConfig.FilterMaskIdHigh = CANMsgCANFiltIDConf->FilterMaskIdHigh;
				canFilterConfig.FilterMaskIdLow = CANMsgCANFiltIDConf->FilterIdLow;
				canFilterConfig.FilterFIFOAssignment = CANMsgCANFiltIDConf->FilterFIFOAssignment;
				canFilterConfig.FilterActivation = CANMsgCANFiltIDConf->FilterActivation;
				canFilterConfig.SlaveStartFilterBank = CANMsgCANFiltIDConf->SlaveStartFilterBank;
				if (HAL_CAN_ConfigFilter(&hcan1, &canFilterConfig) != HAL_OK) {Error_Handler();}
				break;
			}
			default: break;
			}
		}
	NVIC_EnableIRQ(USART2_IRQn);
	}
}

void CANtoPCBuf_processing()
{
#ifndef CANlimMsg_enable
	static CANtoPCMsg * CANtoPCmsg_ptr = NULL;
	if(avaibleForRead_CANtoPCMsgBuf())
	{
		NVIC_DisableIRQ(CAN1_RX0_IRQn);
		CANtoPCmsg_ptr = directRead_CANtoPCMsgBuf();
		//��������� CAN_toPC
		if(CANtoPCmsg_ptr->msgType==CAN_toPC)
			if(HAL_UART_GetState(&huart2) == HAL_UART_STATE_READY)
				if(HAL_UART_Transmit_DMA(&huart2, (uint8_t*)CANtoPCmsg_ptr, sizeof(CANtoPCMsg))!=HAL_OK)//{Error_Handler();}
;
#endif
#ifdef CANlimMsg_enable
	static CANtoPCMsg * CANtoPCmsg_ptr = NULL;
	static CANlimMsg * CANlimmsg_ptr = NULL;
	if(avaibleForRead_CANtoPCMsgBuf())
	{
		NVIC_DisableIRQ(CAN1_RX0_IRQn);
		CANtoPCmsg_ptr = directRead_CANtoPCMsgBuf();
		if(CANtoPCmsg_ptr->msgType==CAN_toPC)
		{
			CANlimmsg_ptr = directWrite_CANlimMsgBuf();
			if(CANtoPCmsg_ptr->CANMsg.RxHeader.IDE)
				CANlimmsg_ptr->MsgID = (CANtoPCmsg_ptr->CANMsg.RxHeader.ExtId | (CAN_toPC << 29));
			else
				CANlimmsg_ptr->MsgID = CANtoPCmsg_ptr->CANMsg.RxHeader.StdId | (CAN_toPC << 29);
			CANlimmsg_ptr->MsgServInformation = CANtoPCmsg_ptr->CANMsg.RxHeader.DLC | (CANtoPCmsg_ptr->CANMsg.RxHeader.RTR << 7);
			CANlimmsg_ptr->MsgData[0] = CANtoPCmsg_ptr->CANMsg.CAN_Rx_Arr[0];
			CANlimmsg_ptr->MsgData[1] = CANtoPCmsg_ptr->CANMsg.CAN_Rx_Arr[1];
			CANlimmsg_ptr->MsgData[2] = CANtoPCmsg_ptr->CANMsg.CAN_Rx_Arr[2];
			CANlimmsg_ptr->MsgData[3] = CANtoPCmsg_ptr->CANMsg.CAN_Rx_Arr[3];
			CANlimmsg_ptr->MsgData[4] = CANtoPCmsg_ptr->CANMsg.CAN_Rx_Arr[4];
			CANlimmsg_ptr->MsgData[5] = CANtoPCmsg_ptr->CANMsg.CAN_Rx_Arr[5];
			CANlimmsg_ptr->MsgData[6] = CANtoPCmsg_ptr->CANMsg.CAN_Rx_Arr[6];
			CANlimmsg_ptr->MsgData[7] = CANtoPCmsg_ptr->CANMsg.CAN_Rx_Arr[7];
			//if(HAL_UART_GetState(&huart2) == HAL_UART_STATE_READY |  HAL_UART_STATE_BUSY_RX)//
			if(huart2.gState == HAL_UART_STATE_READY)//Check that a Tx process is not already ongoing
				if (avaibleForRead_CANlimMsgBuf())
				{
					CANlimmsg_ptr = directRead_CANlimMsgBuf();
					if(HAL_UART_Transmit_DMA(&huart2, CANlimmsg_ptr, CANlimMsg_TxSize)!=HAL_OK){Error_Handler();};
				}
		}
#endif
		//��������� CAN_toPC_State
		else if(CANtoPCmsg_ptr->msgType==CAN_toPC_State)
			;//
		NVIC_EnableIRQ(CAN1_RX0_IRQn);
	}
}
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
	  HAL_UART_Transmit(&huart2, (uint8_t*)"Error_Handler_Code:", 13, 1000);
	  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 1);
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
