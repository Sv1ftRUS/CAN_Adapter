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
    uint8_t i = (CANMsgRxBufHead + 1) % CANMSGRXBUFSIZE ;      // ��������� ������ �������� � ������
    if (i != CANMsgRxBufTail) {                // ���� ���� ��������
    	CANMsgRxBufHead = i;                   // ������� ������
    	return &(CANMsgRxBuf[headPrv]);     // ���������� ������ �� ������� ��� ������
   	}
    else
    	CANMsgRxBufOverFlowFlag++;
    return &(CANMsgRxBuf[headPrv]);
}

inline TYPE * directRead_CANRxBuf()
{
	if (CANMsgRxBufHead == CANMsgRxBufTail) return 0;   // ����� ����
    uint8_t CANMsgRxBufTailPrv=CANMsgRxBufTail;
    CANMsgRxBufTail = (CANMsgRxBufTail + 1) % CANMSGRXBUFSIZE;     // ����� �������
    return &(CANMsgRxBuf[CANMsgRxBufTailPrv]);                   // ����������
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
    uint8_t i = (CANMsgTxBufHead + 1) % CANMSGTXBUFSIZE ;      // ��������� ������ �������� � ������
    if (i != CANMsgTxBufTail) {                // ���� ���� ��������
    	CANMsgTxBufHead = i;                   // ������� ������
    	return &(CANMsgTxBuf[headPrv]);     // ���������� ������ �� ������� ��� ������
   	}
    else
    	CANMsgTxBufOverFlowFlag++;
    return &(CANMsgTxBuf[headPrv]);
}

inline TYPE * directRead_CANTxBuf()
{
	if (CANMsgTxBufHead == CANMsgTxBufTail) return 0;   // ����� ����
    uint8_t CANMsgTxBufTailPrv=CANMsgTxBufTail;
    CANMsgTxBufTail = (CANMsgTxBufTail + 1) % CANMSGTXBUFSIZE;     // ����� �������
    return &(CANMsgTxBuf[CANMsgTxBufTailPrv]);                   // ����������
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
    uint8_t i = (PCMsgRxBufHead + 1) % PCMSGRXBUFSIZE ;      // ��������� ������ �������� � ������
    if (i != PCMsgRxBufTail) {                // ���� ���� ��������
    	PCMsgRxBufHead = i;                   // ������� ������
    	return &(PCMsgRxBuf[headPrv]);     // ���������� ������ �� ������� ��� ������
   	}
    else
    	PCMsgRxBufOverFlowFlag++;
    return &(PCMsgRxBuf[headPrv]);
}

inline TYPE2 * directRead_PCRxBuf()
{
	if (PCMsgRxBufHead == PCMsgRxBufTail) return 0;   // ����� ����
    uint8_t PCMsgRxBufTailPrv=PCMsgRxBufTail;
    PCMsgRxBufTail = (PCMsgRxBufTail + 1) % PCMSGRXBUFSIZE;     // ����� �������
    return &(PCMsgRxBuf[PCMsgRxBufTailPrv]);                   // ����������
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
    uint8_t i = (PCMsgTxBufHead + 1) % PCMSGTXBUFSIZE ;      // ��������� ������ �������� � ������
    if (i != PCMsgTxBufTail) {                // ���� ���� ��������
    	PCMsgTxBufHead = i;                   // ������� ������
    	return &(PCMsgTxBuf[headPrv]);     // ���������� ������ �� ������� ��� ������
   	}
    else
    	PCMsgTxBufOverFlowFlag++;
    return &(PCMsgTxBuf[headPrv]);
}

inline TYPE2 * directRead_PCTxBuf()
{
	if (PCMsgTxBufHead == PCMsgTxBufTail) return 0;   // ����� ����
    uint8_t PCMsgTxBufTailPrv=PCMsgTxBufTail;
    PCMsgTxBufTail = (PCMsgTxBufTail + 1) % PCMSGTXBUFSIZE;     // ����� �������
    return &(PCMsgTxBuf[PCMsgTxBufTailPrv]);                   // ����������
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
    uint8_t i = (CANtoPCMsgBufHead + 1) % CANTOPCMSGBUFSIZE ;      // ��������� ������ �������� � ������
    if (i != CANtoPCMsgBufTail) {                // ���� ���� ��������
    	CANtoPCMsgBufHead = i;                   // ������� ������
    	return &(CANtoPCMsgBuf[headPrv]);     // ���������� ������ �� ������� ��� ������
    	//return &(CANtoPCMsgBuf[CANtoPCMsgBufHead]);     // ���������� ������ �� ������� ��� ������
   	}
    else
    	CANtoPCMsgBufOverFlowFlag++;
    return &(CANtoPCMsgBuf[headPrv]);
}

inline TYPE3 * directRead_CANtoPCMsgBuf()
{
	if (CANtoPCMsgBufHead == CANtoPCMsgBufTail) return 0;   // ����� ����
    uint8_t CANtoPCMsgBufTailPrv=CANtoPCMsgBufTail;
    CANtoPCMsgBufTail = (CANtoPCMsgBufTail + 1) % CANTOPCMSGBUFSIZE;     // ����� �������
    return &(CANtoPCMsgBuf[CANtoPCMsgBufTailPrv]);                   // ����������
}

inline uint8_t overrun_CANtoPCMsgBuf()
{
	return CANtoPCMsgBufOverFlowFlag;
}

//PCtoCANMsg
inline uint8_t avaibleForRead_PCtoCANMsgBuf()//�������� ��� ������� ������ ����� ������
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
    uint8_t i = (PCtoCANMsgBufHead + 1) % PCTOCANMSGBUFSIZE ;      // ��������� ������ �������� � ������
    if (i != PCtoCANMsgBufTail) {                // ���� ���� ��������
    	PCtoCANMsgBufHead = i;                   // ������� ������
    	//return &(PCtoCANMsgBuf[headPrv]);     // ���������� ������ �� ������� ��� ������
    	return &(PCtoCANMsgBuf[PCtoCANMsgBufHead]);     // ���������� ������ �� ������� ��� ������
   	}
    else
    	PCtoCANMsgBufOverFlowFlag++;
    return &(PCtoCANMsgBuf[PCtoCANMsgBufHead]);
}

inline TYPE4 * directRead_PCtoCANMsgBuf()
{
	if (PCtoCANMsgBufHead == PCtoCANMsgBufTail) return 0;   // ����� ����
    uint8_t PCtoCANMsgBufTailPrv=PCtoCANMsgBufTail;
    PCtoCANMsgBufTail = (PCtoCANMsgBufTail + 1) % PCTOCANMSGBUFSIZE;     // ����� �������
    return &(PCtoCANMsgBuf[PCtoCANMsgBufTailPrv]);                   // ����������
}

inline uint8_t overrun_PCtoCANMsgBuf()
{
	return PCtoCANMsgBufOverFlowFlag;
}

//CANlimMsg
inline uint8_t avaibleForRead_CANlimMsgBuf()//�������� ��� ������� ������ ����� ������
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
    uint8_t i = (CANlimMsgBufHead + 1) % CANLIMMSGBUFSIZE ;      // ��������� ������ �������� � ������
    if (i != CANlimMsgBufTail) {                // ���� ���� ��������
    	CANlimMsgBufHead = i;                   // ������� ������
    	return &(CANlimMsgBuf[headPrv]);     // ���������� ������ �� ������� ��� ������
    	//return &(CANlimMsgBuf[CANlimMsgBufHead]);     // ���������� ������ �� ������� ��� ������
   	}
    else
    	CANlimMsgBufOverFlowFlag++;
    return &(CANlimMsgBuf[CANlimMsgBufHead]);
}

inline TYPE5 * directRead_CANlimMsgBuf()
{
	if (CANlimMsgBufHead == CANlimMsgBufTail) return 0;   // ����� ����
    uint8_t CANlimMsgBufTailPrv=CANlimMsgBufTail;
    CANlimMsgBufTail = (CANlimMsgBufTail + 1) % CANLIMMSGBUFSIZE;     // ����� �������
    return &(CANlimMsgBuf[CANlimMsgBufTailPrv]);                   // ����������
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
    // ������ �� ������
    //TYPE read();
    //TYPE * directRead();
    // ���������� ������� �������� ��� �������� �� ������
    //TYPE * peek();
    // ����� ���������� ������������� ���������
    //int available();
    // "�������" ������
    //void clear();

/*
    bool write(TYPE *newVal) {
           int i = (head + 1) % CANMSGRXBUFSIZE;      // ��������� ������ �������� � ������
           if (i != tail) {                // ���� ���� ��������
               buffer[head] = *newVal;      // ����� � �����
               head = i;                   // ������� ������
               return 1;
           } else
           return 0;
       }
*/
/*
       // ����������� ��� ������ (��������� �����)
       bool MyFIFOBuf::availableForWrite() {
           return (head + 1) % CANMSGRXBUFSIZE != tail;
       }

       // ������ �� ������
       TYPE MyFIFOBuf::read() {
           if (head == tail) return 0;   // ����� ����
           TYPE val = buffer[tail];      // ���� � ������
           tail = (tail + 1) % CANMSGRXBUFSIZE;     // ����� �������
           return val;                   // ����������
       }
*/

/*
       // ���������� ������� �������� ��� �������� �� ������
       TYPE * MyFIFOBuf::peek() {
           return &(buffer[tail]);
       }

       // ����� ���������� ������������� ���������
       int MyFIFOBuf::available() {
           return (CANMSGRXBUFSIZE + head - tail) % CANMSGRXBUFSIZE;
       }

       // "�������" ������
       void MyFIFOBuf::clear() {
           head = tail = 0;
       }
*/


