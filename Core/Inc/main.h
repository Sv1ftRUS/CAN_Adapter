/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
//#include "MyFIFOBuf.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
typedef struct
{
	CAN_RxHeaderTypeDef RxHeader;
	uint8_t CAN_Rx_Arr[8];
} CANMsgBufRx;

typedef struct
{
	CAN_TxHeaderTypeDef RxHeader;
	uint8_t CAN_Rx_Arr[8];
} CANMsgBufTx;
/*
#ifndef MyFIFOBuf_H
#define MyFIFOBuf_H
//#define SIZE 4
template <typename TYPE, int SIZE>
class MyFIFOBuf {
public:
    // запись в буфер. Вернёт true при успешной записи
    bool write(TYPE *newVal) {
        int i = (head + 1) % SIZE;      // положение нового значения в буфере
        if (i != tail) {                // если есть местечко
            buffer[head] = *newVal;      // пишем в буфер
            head = i;                   // двигаем голову
            return 1;
        } else
        return 0;
    }

    &TYPE directWrite()
        {
        int headPrv = head;
        int i = (head + 1) % SIZE;      // положение нового значения в буфере
        if (i != tail) {                // если есть местечко
            head = i;                   // двигаем голову
            return &(buffer[headPrv]);     // возвращаем ссылку на элемент для записи
        } else
        overFlow++;
        return &(buffer[headPrv]);
    }
    // доступность для записи (свободное место)
    bool availableForWrite() {
        return (head + 1) % SIZE != tail;
    }

    // чтение из буфера
    TYPE read() {
        if (head == tail) return 0;   // буфер пуст
        TYPE val = buffer[tail];      // берём с хвоста
        tail = (tail + 1) % SIZE;     // хвост двигаем
        return val;                   // возвращаем
    }

    &TYPE directRead() {
        if (head == tail) return 0;   // буфер пуст
        int tailPrv=tail;
        tail = (tail + 1) % SIZE;     // хвост двигаем
        return &(buffer[tailPrv]);                   // возвращаем
    }
    // возвращает крайнее значение без удаления из буфера
    &TYPE peek() {
        return &(buffer[tail]);
    }

    // вернёт количество непрочитанных элементов
    int available() {
        return (SIZE + head - tail) % SIZE;
    }

    // "очистка" буфера
    void clear() {
        head = tail = 0;
    }

private:
    TYPE buffer[SIZE];
    int head = 0, tail = 0;
    int overFlow = 0;
};
#endif
*/
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_Pin GPIO_PIN_9
#define LED_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
