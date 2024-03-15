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

    // запись в буфер. Вернёт true при успешной записи
    bool MyFIFOBuf::write(TYPE *newVal) {
        int i = (head + 1) % SIZE;      // положение нового значения в буфере
        if (i != tail) {                // если есть местечко
            buffer[head] = *newVal;      // пишем в буфер
            head = i;                   // двигаем голову
            return 1;
        } else
        return 0;
    }

    TYPE * MyFIFOBuf::directWrite()
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
    bool MyFIFOBuf::availableForWrite() {
        return (head + 1) % SIZE != tail;
    }

    // чтение из буфера
    TYPE MyFIFOBuf::read() {
        if (head == tail) return 0;   // буфер пуст
        TYPE val = buffer[tail];      // берём с хвоста
        tail = (tail + 1) % SIZE;     // хвост двигаем
        return val;                   // возвращаем
    }

    TYPE * MyFIFOBuf::directRead() {
        if (head == tail) return 0;   // буфер пуст
        int tailPrv=tail;
        tail = (tail + 1) % SIZE;     // хвост двигаем
        return &(buffer[tailPrv]);                   // возвращаем
    }
    // возвращает крайнее значение без удаления из буфера
    TYPE * MyFIFOBuf::peek() {
        return &(buffer[tail]);
    }

    // вернёт количество непрочитанных элементов
    int MyFIFOBuf::available() {
        return (SIZE + head - tail) % SIZE;
    }

    // "очистка" буфера
    void MyFIFOBuf::clear() {
        head = tail = 0;
    }

