/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f1xx_it.c
  * @brief   Interrupt Service Routines.
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
#include "stm32f1xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern CAN_HandleTypeDef hcan1;
extern DMA_HandleTypeDef hdma_usart2_tx;
extern DMA_HandleTypeDef hdma_usart2_rx;
extern UART_HandleTypeDef huart2;
/* USER CODE BEGIN EV */
extern uint8_t* str_Tx_DMA_HalfReciveI;
extern CAN_TxHeaderTypeDef TxHeader1;
extern CAN_RxHeaderTypeDef RxHeader1;
extern uint8_t CAN_Rx_Arr[];
extern uint32_t RxFifo;
extern uint32_t pTxMailbox;
extern CANMsgRx CANMsgRxBuf[];
extern CANtoPCMsg CANtoPCMsgBuf[];
/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M3 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
   while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F1xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f1xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles DMA1 channel6 global interrupt.
  */
void DMA1_Channel6_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel6_IRQn 0 */
	  /*if(__HAL_DMA_GET_FLAG(&hdma_usart2_rx, __HAL_DMA_GET_TC_FLAG_INDEX(&hdma_usart2_rx)))
	  	  {
	  		  HAL_UART_Transmit(&huart2, str_Tx_DMA_HalfReciveI, sizeof(str_Tx_DMA_HalfReciveI), 1000);
	  		  //hdma_usart2_rx.State = HAL_DMA_STATE_BUSY;
	  		  //HAL_UART_Transmit(&huart2, str_Tx, sizeof(str_Tx), 10000);
	  	  }*/
  /* USER CODE END DMA1_Channel6_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart2_rx);
  /* USER CODE BEGIN DMA1_Channel6_IRQn 1 */

  /* USER CODE END DMA1_Channel6_IRQn 1 */
}

/**
  * @brief This function handles DMA1 channel7 global interrupt.
  */
void DMA1_Channel7_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel7_IRQn 0 */
	  /*if(__HAL_DMA_GET_FLAG(&hdma_usart2_tx, __HAL_DMA_GET_TC_FLAG_INDEX(&hdma_usart2_tx)))
	  	  {
		  HAL_StatusTypeDef status= HAL_UART_Transmit(&huart2, str_Tx_DMA_HalfReciveI, sizeof(str_Tx_DMA_HalfReciveI), 1000);
	  		//HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
	  	  }*/
  /* USER CODE END DMA1_Channel7_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart2_tx);
  /* USER CODE BEGIN DMA1_Channel7_IRQn 1 */
  //HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
  /* USER CODE END DMA1_Channel7_IRQn 1 */
}

/**
  * @brief This function handles CAN1 TX interrupt.
  */
void CAN1_TX_IRQHandler(void)
{
  /* USER CODE BEGIN CAN1_TX_IRQn 0 */

  /* USER CODE END CAN1_TX_IRQn 0 */
  HAL_CAN_IRQHandler(&hcan1);
  /* USER CODE BEGIN CAN1_TX_IRQn 1 */

  /* USER CODE END CAN1_TX_IRQn 1 */
}

/**
  * @brief This function handles CAN1 RX0 interrupt.
  */
void CAN1_RX0_IRQHandler(void)
{
  /* USER CODE BEGIN CAN1_RX0_IRQn 0 */
	/*static CANtoPCMsg* CANtoPCmsg_ptr = NULL;
	CANtoPCmsg_ptr = directWrite_CANtoPCMsgBuf();
	CANtoPCmsg_ptr->msgType=CAN_toPC;
	if(HAL_CAN_GetRxMessage(&hcan1, RxFifo, &CANtoPCmsg_ptr->CANMsg.RxHeader, (uint8_t*)(CANtoPCmsg_ptr->CANMsg.CAN_Rx_Arr))!=HAL_OK){Error_Handler();}*/
  /* USER CODE END CAN1_RX0_IRQn 0 */
  HAL_CAN_IRQHandler(&hcan1);
  /* USER CODE BEGIN CAN1_RX0_IRQn 1 */

  /* USER CODE END CAN1_RX0_IRQn 1 */
}

/**
  * @brief This function handles CAN1 RX1 interrupt.
  */
void CAN1_RX1_IRQHandler(void)
{
  /* USER CODE BEGIN CAN1_RX1_IRQn 0 */
	/*static CANtoPCMsg* CANtoPCmsg_ptr = NULL;
	CANtoPCmsg_ptr = directWrite_CANtoPCMsgBuf();
	CANtoPCmsg_ptr->msgType=CAN_toPC;
	if(HAL_CAN_GetRxMessage(&hcan1, RxFifo, &CANtoPCmsg_ptr->CANMsg.RxHeader, (uint8_t*)(CANtoPCmsg_ptr->CANMsg.CAN_Rx_Arr))!=HAL_OK){Error_Handler();}*/
  /* USER CODE END CAN1_RX1_IRQn 0 */
  HAL_CAN_IRQHandler(&hcan1);
  /* USER CODE BEGIN CAN1_RX1_IRQn 1 */

  /* USER CODE END CAN1_RX1_IRQn 1 */
}

/**
  * @brief This function handles USART2 global interrupt.
  */
void USART2_IRQHandler(void)
{
  /* USER CODE BEGIN USART2_IRQn 0 */
	/*int flag;
	HAL_StatusTypeDef status=HAL_OK;
	if(flag =(__HAL_UART_GET_FLAG(&huart2, UART_FLAG_TC) && __HAL_UART_GET_FLAG(&huart2, UART_FLAG_TXE)))// && __HAL_UART_GET_FLAG(&huart2, UART_FLAG_IDLE))


		  	  {
		UART_HandleTypeDef *huart=&huart2;
		  __HAL_UART_DISABLE_IT(huart, UART_IT_TC);

		  //Tx process is ended, restore huart->gState to Ready
		  //huart->gState = HAL_UART_STATE_READY;
		  //status= HAL_UART_Transmit_IT(&huart2, str_Tx_DMA_HalfReciveI, sizeof(str_Tx_DMA_HalfReciveI));


		//HAL_Delay(500);//��������
		//do{
			//HAL_UART_IRQHandler(&huart2);
			//status= HAL_UART_Transmit_IT(&huart2, str_Tx_DMA_HalfReciveI, sizeof(str_Tx_DMA_HalfReciveI));
		  		//HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
		//} while(status!=HAL_OK);
		  	  //}
  /* USER CODE END USART2_IRQn 0 */
  HAL_UART_IRQHandler(&huart2);
  /* USER CODE BEGIN USART2_IRQn 1 */

  //HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
  //__HAL_UART_DISABLE_IT(&huart2, UART_IT_TXE);
  /* USER CODE END USART2_IRQn 1 */
}

/* USER CODE BEGIN 1 */

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)//��������������� weak-������� ����������� ���������� ��������� �������� �� UART. ��� ��������� �������� �� uART, ������� ���� �� ��� � ������ �������� ���-���������, ���� ���� ����������
#ifndef CANlimMsg_enable
{//� ���� ������� ����� ��������� ��� ��������� �� �������� � PC? ���� ��� �� ������� ������� =/
	static CANtoPCMsg * CANtoPCmsg_ptr = NULL;
	if(huart == &huart2)
		if (avaibleForRead_CANtoPCMsgBuf())
		{
			CANtoPCmsg_ptr = directRead_CANtoPCMsgBuf();
			if(HAL_UART_Transmit_DMA(huart, CANtoPCmsg_ptr, sizeof(CANtoPCMsg))!=HAL_OK){Error_Handler();};
		}
}
#endif
#ifdef CANlimMsg_enable
{
	static CANlimMsg * CANlimmsg_ptr = NULL;
	if(huart == &huart2)
		if (avaibleForRead_CANlimMsgBuf())
		{
			CANlimmsg_ptr = directRead_CANlimMsgBuf();
			if(HAL_UART_Transmit_DMA(huart, (uint8_t*)CANlimmsg_ptr, CANlimMsg_TxSize)!=HAL_OK){Error_Handler();};
		}
	}

#endif

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)//��������������� weak-������� ����������� ���������� ��������� ������ �� UART. ��� ��������� ������ �� uART, ������ ��� ��������� � PCtoCANMsgBuf
{
	static PCtoCANMsg * PCtoCANmsg_ptr = NULL;
	if(huart == &huart2)
		{
			PCtoCANmsg_ptr = directWrite_PCtoCANMsgBuf();
			if(HAL_UART_Receive_DMA(&huart2, (uint8_t*)PCtoCANmsg_ptr, sizeof(PCtoCANMsg))!=HAL_OK){Error_Handler();}//���� ������������ �� ����� ���������� HAL_UART_Receive_DMA, �� ������ �� �����
			//HAL_CAN_AddTxMessage(&hcan1, &PCtoCANmsg_ptr, sizeof(PCtoCANMsg), &pTxMailbox);
		}
}

void HAL_CAN_RxFifo0MsgPendingCallback (CAN_HandleTypeDef * hcan)
{
	static CANtoPCMsg* CANtoPCmsg_ptr = NULL;
	CANtoPCmsg_ptr = directWrite_CANtoPCMsgBuf();
	CANtoPCmsg_ptr->msgType=CAN_toPC;
	if(HAL_CAN_GetRxMessage(&hcan1, RxFifo, &CANtoPCmsg_ptr->CANMsg.RxHeader, (uint8_t*)(CANtoPCmsg_ptr->CANMsg.CAN_Rx_Arr))!=HAL_OK){Error_Handler();}
}
void HAL_CAN_RxFifo1MsgPendingCallback (CAN_HandleTypeDef * hcan)
{
	static CANtoPCMsg* CANtoPCmsg_ptr = NULL;
	CANtoPCmsg_ptr = directWrite_CANtoPCMsgBuf();
	CANtoPCmsg_ptr->msgType=CAN_toPC;
	if(HAL_CAN_GetRxMessage(&hcan1, RxFifo, &CANtoPCmsg_ptr->CANMsg.RxHeader, (uint8_t*)(CANtoPCmsg_ptr->CANMsg.CAN_Rx_Arr))!=HAL_OK){Error_Handler();}
}
/* USER CODE END 1 */
