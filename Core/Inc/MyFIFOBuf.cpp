/*
 * MyFIFOBuf.cpp
 *
 *  Created on: Mar 15, 2024
 *      Author: volgunov
 */

#include <MyFIFOBuf.h>

#define TYPE int
#define SIZE 4
//template <typename TYPE, int SIZE>

    // ������ � �����. ����� true ��� �������� ������
    bool MyFIFOBuf::write(TYPE *newVal) {
        int i = (head + 1) % SIZE;      // ��������� ������ �������� � ������
        if (i != tail) {                // ���� ���� ��������
            buffer[head] = *newVal;      // ����� � �����
            head = i;                   // ������� ������
            return 1;
        } else
        return 0;
    }

    TYPE * MyFIFOBuf::directWrite()
        {
        int headPrv = head;
        int i = (head + 1) % SIZE;      // ��������� ������ �������� � ������
        if (i != tail) {                // ���� ���� ��������
            head = i;                   // ������� ������
            return &(buffer[headPrv]);     // ���������� ������ �� ������� ��� ������
        } else
        overFlow++;
        return &(buffer[headPrv]);
    }
    // ����������� ��� ������ (��������� �����)
    bool MyFIFOBuf::availableForWrite() {
        return (head + 1) % SIZE != tail;
    }

    // ������ �� ������
    TYPE MyFIFOBuf::read() {
        if (head == tail) return 0;   // ����� ����
        TYPE val = buffer[tail];      // ���� � ������
        tail = (tail + 1) % SIZE;     // ����� �������
        return val;                   // ����������
    }

    TYPE * MyFIFOBuf::directRead() {
        if (head == tail) return 0;   // ����� ����
        int tailPrv=tail;
        tail = (tail + 1) % SIZE;     // ����� �������
        return &(buffer[tailPrv]);                   // ����������
    }
    // ���������� ������� �������� ��� �������� �� ������
    TYPE * MyFIFOBuf::peek() {
        return &(buffer[tail]);
    }

    // ����� ���������� ������������� ���������
    int MyFIFOBuf::available() {
        return (SIZE + head - tail) % SIZE;
    }

    // "�������" ������
    void MyFIFOBuf::clear() {
        head = tail = 0;
    }

