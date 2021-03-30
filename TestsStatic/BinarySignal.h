#pragma once
#include <string>

const int MAX_COUNT_STATES = 256;	// Максимальное количество описаний сигнала

struct Signal {
	char level = 0;
	char duration = 0;
};

struct Offset {
    int index = 0;
    int length = 0;

    Offset(int index, int length) :index(index), length(length) {};
    Offset() :index(0), length(0) {};
};

class BinarySignal
{
public:
	BinarySignal();		                    // Пустой конструктор для инициализации экземпляров и массивов экземпляров класса по умолчанию.

    BinarySignal(char level);               // Конструктор для инициализацией постоянным уровнем сигнала(уровень 0 или 1 на максимальную длительность).

    BinarySignal(const std::string& str);   // Конструктор для инициализацией сигналом как строки символов.

    friend std::ostream& operator <<(std::ostream& out, BinarySignal& binarySignal);  // Вывод сигнала с помощью псевдографики

    friend std::istream& operator >>(std::istream& in, BinarySignal& binarySignal);         // Ввод сигнала из входного потока;

    BinarySignal operator !();                             // Инверсия сигнала

    BinarySignal& operator +=(const BinarySignal& right);   // Дополнение сигнала другим сигналом

    BinarySignal& operator *=(const int right);            // Копирование сигнала определённое число раз

    BinarySignal& operator ()(const int position, BinarySignal const binarySignalToInsert); // Вставка в определённый момент времени(тип int) другого сигнала(с помощью перегруженного оператора());

    BinarySignal& operator ()(const int position, const int duration); // Удаление фрагмента сигнала в определенное время(тип int) определённой длительности(с помощью перегруженного оператора()).

    bool isEqual(BinarySignal& right); // Введён дополнительно

private:
	Signal signals_[MAX_COUNT_STATES];
	unsigned int size_ = 0;

    Offset GetIndex(const int position) const;
};

