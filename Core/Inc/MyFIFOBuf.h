/*
 * MyFIFOBuf.h
 *
 *  Created on: Mar 15, 2024
 *      Author: volgunov
 */

#ifndef INC_MYFIFOBUF_H_
#define INC_MYFIFOBUF_H_
#define TYPE int
#define SIZE 4
//template <typename TYPE, int SIZE>
class MyFIFOBuf {
public:

    bool write(TYPE *newVal);
    TYPE * directWrite();
    bool availableForWrite();

    // ������ �� ������
    TYPE read();

    TYPE * directRead();
    // ���������� ������� �������� ��� �������� �� ������
    TYPE * peek();

    // ����� ���������� ������������� ���������
    int available();
    // "�������" ������
    void clear();

private:
    TYPE buffer[SIZE];
    int head = 0, tail = 0;
    int overFlow = 0;
};

#endif /* INC_MYFIFOBUF_H_ */
