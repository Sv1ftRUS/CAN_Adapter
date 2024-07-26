/*
 * MyFifoBuf.h
 *
 *  Created on: Mar 16, 2024
 *      Author: volgunov
 */
#ifndef INC_USER_MYFIFOBUF_H_
#define INC_USER_MYFIFOBUF_H_

//includes
#include "main.h"

//enums
enum msgType //типы сообщений между адаптером и PC
{
	PC_toCAN_State,
	PC_toCAN,
	CAN_toPC_State,
	CAN_toPC
};

//data types
typedef struct
{
	CAN_RxHeaderTypeDef RxHeader;
	uint8_t CAN_Rx_Arr[8];
}CANMsgRx;

typedef struct
{
	CAN_TxHeaderTypeDef TxHeader;
	uint8_t CAN_Tx_Arr[8];
}CANMsgTx;

typedef struct
{
	enum msgType msgType;
	CANMsgRx CANMsg;
}PCMsg;

typedef struct
{
	uint8_t msgType;// msgType;
	CANMsgTx CANMsg;
}PCtoCANMsg; // длина 0x24 , 36 байт для CANMsgTx

typedef struct
{
	enum msgType msgType;
	CANMsgRx CANMsg;
}CANtoPCMsg; // длина 0x28 , 40 байт для CANMsgRx

typedef struct
{
	uint32_t MsgID;
	uint8_t MsgServInformation;//DLC:0-4	RTR 7
	uint8_t MsgData[8];
}CANlimMsg;// укороченный формат CAN сообщения
#define CANlimMsg_TxSize 13

typedef struct
{
	uint32_t msgType;
	uint8_t Communication;
	uint8_t Instance;
	uint8_t Prescaler;
	uint8_t Mode;
	uint32_t SyncJumpWidth;
	uint32_t TimeSeg1;
	uint32_t TimeSeg2;
	uint8_t TimeTriggeredMode;
	uint8_t AutoBusOff;
	uint8_t AutoWakeUp;
	uint8_t AutoRetransmission;
	uint8_t ReceiveFifoLocked;
	uint8_t TransmitFifoPriority;
}PCtoCANMsgCANConf;

typedef struct
{
	uint32_t msgType;
	uint8_t Communication;
	uint8_t Reserved0;
	uint8_t Reserved1;
	uint8_t Reserved2;
	uint32_t FilterIdHigh;
	uint32_t FilterIdLow;
	uint32_t FilterMaskIdHigh;
	uint32_t FilterMaskIdLow;
	uint8_t FilterFIFOAssignment;//
	uint8_t FilterBank;
	uint8_t FilterMode;
	uint8_t FilterScale;
	uint8_t FilterActivation;
	uint8_t SlaveStartFilterBank;
}PCtoCANMsgCANFiltIDConf;//31 байт

//vars
/*
extern CANMsgRx CANMsgRxBuf[];
static uint8_t CANMsgRxBufHead=0;
static uint8_t CANMsgRxBufTail=0;
static uint8_t CANMsgRxBufOverFlowFlag=0;

extern CANMsgTx CANMsgTxBuf[];
static uint8_t CANMsgTxBufHead=0;
static uint8_t CANMsgTxBufTail=0;
static uint8_t CANMsgTxBufOverFlowFlag=0;

extern PCMsg PCMsgRxBuf[];
static uint8_t PCMsgRxBufHead=0;
static uint8_t PCMsgRxBufTail=0;
static uint8_t PCMsgRxBufOverFlowFlag=0;

extern PCMsg PCMsgTxBuf[];
static uint8_t PCMsgTxBufHead=0;
static uint8_t PCMsgTxBufTail=0;
static uint8_t PCMsgTxBufOverFlowFlag=0;
*/
extern CANtoPCMsg CANtoPCMsgBuf[];
extern uint8_t CANtoPCMsgBufHead;
extern uint8_t CANtoPCMsgBufTail;
extern uint8_t CANtoPCMsgBufOverFlowFlag;

extern PCtoCANMsg PCtoCANMsgBuf[];
extern uint8_t PCtoCANMsgBufHead;
extern uint8_t PCtoCANMsgBufTail;
extern uint8_t PCtoCANMsgBufOverFlowFlag;

extern CANlimMsg CANlimMsgBuf[];
extern uint8_t CANlimMsgBufHead;
extern uint8_t CANlimMsgBufTail;
extern uint8_t CANlimMsgBufOverFlowFlag;

//functions
uint8_t avaibleForRead_CANRxBuf();
uint8_t avaibleForWrite_CANRxBuf();
CANMsgRx* directWrite_CANRxBuf();
CANMsgRx* directRead_CANRxBuf();
uint8_t overrun_CANRxBuf();

uint8_t avaibleForRead_CANTxBuf();
uint8_t avaibleForWrite_CANTxBuf();
CANMsgRx* directWrite_CANTxBuf();
CANMsgRx* directRead_CANTxBuf();
uint8_t overrun_CANTxBuf();

uint8_t avaibleForRead_PCRxBuf();
uint8_t avaibleForWrite_PCRxBuf();
PCMsg* directWrite_PCRxBuf();
PCMsg* directRead_PCRxBuf();
uint8_t overrun_PCRxBuf();

uint8_t avaibleForRead_PCTxBuf();
uint8_t avaibleForWrite_PCTxBuf();
PCMsg* directWrite_PCTxBuf();
PCMsg* directRead_PCTxBuf();
uint8_t overrun_PCTxBuf();

uint8_t avaibleForRead_CANtoPCMsgBuf();
uint8_t avaibleForWrite_CANtoPCMsgBuf();
CANtoPCMsg* directWrite_CANtoPCMsgBuf();
CANtoPCMsg* directRead_CANtoPCMsgBuf();
uint8_t overrun_CANtoPCMsgBuf();

uint8_t avaibleForRead_PCtoCANMsgBuf();
uint8_t avaibleForWrite_PCtoCANMsgBuf();
PCtoCANMsg* directWrite_PCtoCANMsgBuf();
PCtoCANMsg* directRead_PCtoCANMsgBuf();
uint8_t overrun_PCtoCANMsgBuf();

uint8_t avaibleForRead_CANlimMsgBuf();
uint8_t avaibleForWrite_CANlimMsgBuf();
CANlimMsg* directWrite_CANlimMsgBuf();
CANlimMsg* directRead_CANlimMsgBuf();
uint8_t overrun_CANlimMsgBuf();

//some defines
#define TYPE CANMsgRx //что-то типа шаблонной функции мда...
#define TYPE2 PCMsg //что-то типа шаблонной функции
#define TYPE3 CANtoPCMsg //что-то типа шаблонной функции
#define TYPE4 PCtoCANMsg
#define TYPE5 CANlimMsg

#define CANMSGRXBUFSIZE 20
#define CANMSGTXBUFSIZE 20
#define PCMSGRXBUFSIZE 20
#define PCMSGTXBUFSIZE 20
#define CANTOPCMSGBUFSIZE 20
#define PCTOCANMSGBUFSIZE 20
#define CANLIMMSGBUFSIZE 20

#endif /* INC_USER_MYFIFOBUF_H_ */
