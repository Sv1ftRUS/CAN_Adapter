/*
 * MyFifoBuf.c
 *
 *  Created on: Mar 16, 2024
 *      Author: volgunov
 */
//#pragma once
#include <User/MyFifoBuf.h>
//#include "main.h"

/*
uint8_t CANtoPCMsgBufHead=0;
 uint8_t CANtoPCMsgBufTail=0;
 uint8_t CANtoPCMsgBufOverFlowFlag=0;


 uint8_t PCtoCANMsgBufHead=0;
 uint8_t PCtoCANMsgBufTail=0;
 uint8_t PCtoCANMsgBufOverFlowFlag=0;
*/





/*
//CANRx
inline uint8_t avaibleForRead_CANRxBuf()
{
	return CANMsgRxBufHead != CANMsgRxBufTail;
}

inline uint8_t avaibleForWrite_CANRxBuf()
{
	return CANMsgRxBufTail != ((CANMsgRxBufHead + 1) % CANMSGRXBUFSIZE);
}

inline TYPE * directWrite_CANRxBuf()
{
	uint8_t headPrv = CANMsgRxBufHead;
    uint8_t i = (CANMsgRxBufHead + 1) % CANMSGRXBUFSIZE ;      // положение нового значения в буфере
    if (i != CANMsgRxBufTail) {                // если есть местечко
    	CANMsgRxBufHead = i;                   // двигаем голову
    	return &(CANMsgRxBuf[headPrv]);     // возвращаем ссылку на элемент для записи
   	}
    else
    	CANMsgRxBufOverFlowFlag++;
    return &(CANMsgRxBuf[headPrv]);
}

inline TYPE * directRead_CANRxBuf()
{
	if (CANMsgRxBufHead == CANMsgRxBufTail) return 0;   // буфер пуст
    uint8_t CANMsgRxBufTailPrv=CANMsgRxBufTail;
    CANMsgRxBufTail = (CANMsgRxBufTail + 1) % CANMSGRXBUFSIZE;     // хвост двигаем
    return &(CANMsgRxBuf[CANMsgRxBufTailPrv]);                   // возвращаем
}

inline uint8_t overrun_CANRxBuf()
{
	return CANMsgRxBufOverFlowFlag;
}

//CANTx
inline uint8_t avaibleForRead_CANTxBuf()
{
	return CANMsgTxBufHead != CANMsgTxBufTail;
}

inline uint8_t avaibleForWrite_CANTxBuf()
{
	return CANMsgTxBufTail != ((CANMsgTxBufHead + 1) % CANMSGTXBUFSIZE);
}

inline TYPE * directWrite_CANTxBuf()
{
	uint8_t headPrv = CANMsgTxBufHead;
    uint8_t i = (CANMsgTxBufHead + 1) % CANMSGTXBUFSIZE ;      // положение нового значения в буфере
    if (i != CANMsgTxBufTail) {                // если есть местечко
    	CANMsgTxBufHead = i;                   // двигаем голову
    	return &(CANMsgTxBuf[headPrv]);     // возвращаем ссылку на элемент для записи
   	}
    else
    	CANMsgTxBufOverFlowFlag++;
    return &(CANMsgTxBuf[headPrv]);
}

inline TYPE * directRead_CANTxBuf()
{
	if (CANMsgTxBufHead == CANMsgTxBufTail) return 0;   // буфер пуст
    uint8_t CANMsgTxBufTailPrv=CANMsgTxBufTail;
    CANMsgTxBufTail = (CANMsgTxBufTail + 1) % CANMSGTXBUFSIZE;     // хвост двигаем
    return &(CANMsgTxBuf[CANMsgTxBufTailPrv]);                   // возвращаем
}

inline uint8_t overrun_CANTxBuf()
{
	return CANMsgTxBufOverFlowFlag;
}






//PCRx
inline uint8_t avaibleForRead_PCRxBuf()
{
	return PCMsgRxBufHead != PCMsgRxBufTail;
}

inline uint8_t avaibleForWrite_PCRxBuf()
{
	return PCMsgRxBufTail != ((PCMsgRxBufHead + 1) % PCMSGRXBUFSIZE);
}

inline TYPE2 * directWrite_PCRxBuf()
{
	uint8_t headPrv = PCMsgRxBufHead;
    uint8_t i = (PCMsgRxBufHead + 1) % PCMSGRXBUFSIZE ;      // положение нового значения в буфере
    if (i != PCMsgRxBufTail) {                // если есть местечко
    	PCMsgRxBufHead = i;                   // двигаем голову
    	return &(PCMsgRxBuf[headPrv]);     // возвращаем ссылку на элемент для записи
   	}
    else
    	PCMsgRxBufOverFlowFlag++;
    return &(PCMsgRxBuf[headPrv]);
}

inline TYPE2 * directRead_PCRxBuf()
{
	if (PCMsgRxBufHead == PCMsgRxBufTail) return 0;   // буфер пуст
    uint8_t PCMsgRxBufTailPrv=PCMsgRxBufTail;
    PCMsgRxBufTail = (PCMsgRxBufTail + 1) % PCMSGRXBUFSIZE;     // хвост двигаем
    return &(PCMsgRxBuf[PCMsgRxBufTailPrv]);                   // возвращаем
}

inline uint8_t overrun_PCRxBuf()
{
	return PCMsgRxBufOverFlowFlag;
}

//PCTx
inline uint8_t avaibleForRead_PCTxBuf()
{
	return PCMsgTxBufHead != PCMsgTxBufTail;
}

inline uint8_t avaibleForWrite_PCTxBuf()
{
	return PCMsgTxBufTail != ((PCMsgTxBufHead + 1) % PCMSGTXBUFSIZE);
}

inline TYPE2 * directWrite_PCTxBuf()
{
	uint8_t headPrv = PCMsgTxBufHead;
    uint8_t i = (PCMsgTxBufHead + 1) % PCMSGTXBUFSIZE ;      // положение нового значения в буфере
    if (i != PCMsgTxBufTail) {                // если есть местечко
    	PCMsgTxBufHead = i;                   // двигаем голову
    	return &(PCMsgTxBuf[headPrv]);     // возвращаем ссылку на элемент для записи
   	}
    else
    	PCMsgTxBufOverFlowFlag++;
    return &(PCMsgTxBuf[headPrv]);
}

inline TYPE2 * directRead_PCTxBuf()
{
	if (PCMsgTxBufHead == PCMsgTxBufTail) return 0;   // буфер пуст
    uint8_t PCMsgTxBufTailPrv=PCMsgTxBufTail;
    PCMsgTxBufTail = (PCMsgTxBufTail + 1) % PCMSGTXBUFSIZE;     // хвост двигаем
    return &(PCMsgTxBuf[PCMsgTxBufTailPrv]);                   // возвращаем
}

inline uint8_t overrun_PCTxBuf()
{
	return PCMsgTxBufOverFlowFlag;
}
*/
//------------------------------------------------------------------------

//CANtoPCMsg
inline uint8_t avaibleForRead_CANtoPCMsgBuf()
{
	return CANtoPCMsgBufHead != CANtoPCMsgBufTail;
}

inline uint8_t avaibleForWrite_CANtoPCMsgBuf()
{
	return CANtoPCMsgBufTail != ((CANtoPCMsgBufHead + 1) % CANTOPCMSGBUFSIZE);
}

inline TYPE3 * directWrite_CANtoPCMsgBuf()
{
	uint8_t headPrv = CANtoPCMsgBufHead;
    uint8_t i = (CANtoPCMsgBufHead + 1) % CANTOPCMSGBUFSIZE ;      // положение нового значения в буфере
    if (i != CANtoPCMsgBufTail) {                // если есть местечко
    	CANtoPCMsgBufHead = i;                   // двигаем голову
    	return &(CANtoPCMsgBuf[headPrv]);     // возвращаем ссылку на элемент для записи
    	//return &(CANtoPCMsgBuf[CANtoPCMsgBufHead]);     // возвращаем ссылку на элемент для записи
   	}
    else
    	CANtoPCMsgBufOverFlowFlag++;
    return &(CANtoPCMsgBuf[headPrv]);
}

inline TYPE3 * directRead_CANtoPCMsgBuf()
{
	if (CANtoPCMsgBufHead == CANtoPCMsgBufTail) return 0;   // буфер пуст
    uint8_t CANtoPCMsgBufTailPrv=CANtoPCMsgBufTail;
    CANtoPCMsgBufTail = (CANtoPCMsgBufTail + 1) % CANTOPCMSGBUFSIZE;     // хвост двигаем
    return &(CANtoPCMsgBuf[CANtoPCMsgBufTailPrv]);                   // возвращаем
}

inline uint8_t overrun_CANtoPCMsgBuf()
{
	return CANtoPCMsgBufOverFlowFlag;
}

//PCtoCANMsg
inline uint8_t avaibleForRead_PCtoCANMsgBuf()//возможно эту функцию вообще лучше убрать
{
	return PCtoCANMsgBufHead != PCtoCANMsgBufTail;
}

inline uint8_t avaibleForWrite_PCtoCANMsgBuf()
{
		return PCtoCANMsgBufTail != ((PCtoCANMsgBufHead + 1) % PCTOCANMSGBUFSIZE);
}

inline TYPE4 * directWrite_PCtoCANMsgBuf()
{
	//uint8_t headPrv = PCtoCANMsgBufHead;
    uint8_t i = (PCtoCANMsgBufHead + 1) % PCTOCANMSGBUFSIZE ;      // положение нового значения в буфере
    if (i != PCtoCANMsgBufTail) {                // если есть местечко
    	PCtoCANMsgBufHead = i;                   // двигаем голову
    	//return &(PCtoCANMsgBuf[headPrv]);     // возвращаем ссылку на элемент для записи
    	return &(PCtoCANMsgBuf[PCtoCANMsgBufHead]);     // возвращаем ссылку на элемент для записи
   	}
    else
    	PCtoCANMsgBufOverFlowFlag++;
    return &(PCtoCANMsgBuf[PCtoCANMsgBufHead]);
}

inline TYPE4 * directRead_PCtoCANMsgBuf()
{
	if (PCtoCANMsgBufHead == PCtoCANMsgBufTail) return 0;   // буфер пуст
    uint8_t PCtoCANMsgBufTailPrv=PCtoCANMsgBufTail;
    PCtoCANMsgBufTail = (PCtoCANMsgBufTail + 1) % PCTOCANMSGBUFSIZE;     // хвост двигаем
    return &(PCtoCANMsgBuf[PCtoCANMsgBufTailPrv]);                   // возвращаем
}

inline uint8_t overrun_PCtoCANMsgBuf()
{
	return PCtoCANMsgBufOverFlowFlag;
}

//CANlimMsg
inline uint8_t avaibleForRead_CANlimMsgBuf()//возможно эту функцию вообще лучше убрать
{
	return CANlimMsgBufHead != CANlimMsgBufTail;
}

inline uint8_t avaibleForWrite_CANlimMsgBuf()
{
		return CANlimMsgBufTail != ((CANlimMsgBufHead + 1) % CANLIMMSGBUFSIZE);
}

inline TYPE5 * directWrite_CANlimMsgBuf()
{
	uint8_t headPrv = CANlimMsgBufHead;
    uint8_t i = (CANlimMsgBufHead + 1) % CANLIMMSGBUFSIZE ;      // положение нового значения в буфере
    if (i != CANlimMsgBufTail) {                // если есть местечко
    	CANlimMsgBufHead = i;                   // двигаем голову
    	return &(CANlimMsgBuf[headPrv]);     // возвращаем ссылку на элемент для записи
    	//return &(CANlimMsgBuf[CANlimMsgBufHead]);     // возвращаем ссылку на элемент для записи
   	}
    else
    	CANlimMsgBufOverFlowFlag++;
    return &(CANlimMsgBuf[CANlimMsgBufHead]);
}

inline TYPE5 * directRead_CANlimMsgBuf()
{
	if (CANlimMsgBufHead == CANlimMsgBufTail) return 0;   // буфер пуст
    uint8_t CANlimMsgBufTailPrv=CANlimMsgBufTail;
    CANlimMsgBufTail = (CANlimMsgBufTail + 1) % CANLIMMSGBUFSIZE;     // хвост двигаем
    return &(CANlimMsgBuf[CANlimMsgBufTailPrv]);                   // возвращаем
}

inline uint8_t overrun_CANlimMsgBuf()
{
	return CANlimMsgBufOverFlowFlag;
}










































//template <typename TYPE, int CANMSGRXBUFSIZE>
//typedef struct /*class*/ MyFIFOBuf {
//public:

    //bool write(TYPE *newVal);
    //TYPE * directWrite();
   // bool availableForWrite();
    // чтение из буфера
    //TYPE read();
    //TYPE * directRead();
    // возвращает крайнее значение без удаления из буфера
    //TYPE * peek();
    // вернёт количество непрочитанных элементов
    //int available();
    // "очистка" буфера
    //void clear();

/*
    bool write(TYPE *newVal) {
           int i = (head + 1) % CANMSGRXBUFSIZE;      // положение нового значения в буфере
           if (i != tail) {                // если есть местечко
               buffer[head] = *newVal;      // пишем в буфер
               head = i;                   // двигаем голову
               return 1;
           } else
           return 0;
       }
*/
/*
       // доступность для записи (свободное место)
       bool MyFIFOBuf::availableForWrite() {
           return (head + 1) % CANMSGRXBUFSIZE != tail;
       }

       // чтение из буфера
       TYPE MyFIFOBuf::read() {
           if (head == tail) return 0;   // буфер пуст
           TYPE val = buffer[tail];      // берём с хвоста
           tail = (tail + 1) % CANMSGRXBUFSIZE;     // хвост двигаем
           return val;                   // возвращаем
       }
*/

/*
       // возвращает крайнее значение без удаления из буфера
       TYPE * MyFIFOBuf::peek() {
           return &(buffer[tail]);
       }

       // вернёт количество непрочитанных элементов
       int MyFIFOBuf::available() {
           return (CANMSGRXBUFSIZE + head - tail) % CANMSGRXBUFSIZE;
       }

       // "очистка" буфера
       void MyFIFOBuf::clear() {
           head = tail = 0;
       }
*/


