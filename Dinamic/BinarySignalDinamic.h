#pragma once
#include <string>
#include "DinamicArray.h"

const int MAX_COUNT_STATES = 256;	// ������������ ���������� �������� �������


struct Offset {
    int index = 0;
    int length = 0;

    Offset(int index, int length) :index(index), length(length) {};
    Offset() :index(0), length(0) {};
};

class BinarySignalDinamic
{
public:
    BinarySignalDinamic();		                    // ������ ����������� ��� ������������� ����������� � �������� ����������� ������ �� ���������.

    BinarySignalDinamic(char level);               // ����������� ��� �������������� ���������� ������� �������(������� 0 ��� 1 �� ������������ ������������).

    BinarySignalDinamic(const std::string& str);   // ����������� ��� �������������� �������� ��� ������ ��������.

    friend std::ostream& operator <<(std::ostream& out,  BinarySignalDinamic& BinarySignal);  // ����� ������� � ������� �������������

    friend std::istream& operator >>(std::istream& in, const BinarySignalDinamic& BinarySignal);         // ���� ������� �� �������� ������;

    BinarySignalDinamic& operator !();                             // �������� �������

    BinarySignalDinamic& operator +=(BinarySignalDinamic& right);   // ���������� ������� ������ ��������

    BinarySignalDinamic& operator *=( int right);            // ����������� ������� ����������� ����� ���

    BinarySignalDinamic& operator ()( int position, BinarySignalDinamic binarySignalToInsert); // ������� � ����������� ������ �������(��� int) ������� �������(� ������� �������������� ���������());

    BinarySignalDinamic& operator ()( int position,  int duration); // �������� ��������� ������� � ������������ �����(��� int) ����������� ������������(� ������� �������������� ���������()).

    bool isEqual(BinarySignalDinamic& right); // ����� �������������

private:
    DinamicArray signals_;
    unsigned int size_ = 0;

    Offset GetIndex( int position);
};

