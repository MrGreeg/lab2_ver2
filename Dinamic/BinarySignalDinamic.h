#pragma once
#include <string>
#include "DinamicArray.h"

const int MAX_COUNT_STATES = 256;	// Максимальное количество описаний сигнала


struct Offset {
    int index = 0;
    int length = 0;

    Offset(int index, int length) :index(index), length(length) {};
    Offset() :index(0), length(0) {};
};

class BinarySignalDinamic
{
public:
    BinarySignalDinamic();		                    // Пустой конструктор для инициализации экземпляров и массивов экземпляров класса по умолчанию.

    BinarySignalDinamic(char level);               // Конструктор для инициализацией постоянным уровнем сигнала(уровень 0 или 1 на максимальную длительность).

    BinarySignalDinamic(const std::string& str);   // Конструктор для инициализацией сигналом как строки символов.

    friend std::ostream& operator <<(std::ostream& out,  BinarySignalDinamic& BinarySignal);  // Вывод сигнала с помощью псевдографики

    friend std::istream& operator >>(std::istream& in, const BinarySignalDinamic& BinarySignal);         // Ввод сигнала из входного потока;

    BinarySignalDinamic& operator !();                             // Инверсия сигнала

    BinarySignalDinamic& operator +=(BinarySignalDinamic& right);   // Дополнение сигнала другим сигналом

    BinarySignalDinamic& operator *=( int right);            // Копирование сигнала определённое число раз

    BinarySignalDinamic& operator ()( int position, BinarySignalDinamic binarySignalToInsert); // Вставка в определённый момент времени(тип int) другого сигнала(с помощью перегруженного оператора());

    BinarySignalDinamic& operator ()( int position,  int duration); // Удаление фрагмента сигнала в определенное время(тип int) определённой длительности(с помощью перегруженного оператора()).

    bool isEqual(BinarySignalDinamic& right); // Введён дополнительно

private:
    DinamicArray signals_;
    unsigned int size_ = 0;

    Offset GetIndex( int position);
};

