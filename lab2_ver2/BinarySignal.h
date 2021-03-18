#pragma once
#include <string>

const int MAX_COUNT_STATES = 256;	// ������������ ���������� �������� �������

struct Signal {
	char level = 0;
	char duration = 0;
};

class BinarySignal
{
public:
	BinarySignal();		                    // ������ ����������� ��� ������������� ����������� � �������� ����������� ������ �� ���������.

    BinarySignal(char level);               // ����������� ��� �������������� ���������� ������� �������(������� 0 ��� 1 �� ������������ ������������).

    BinarySignal(const std::string& str);   // ����������� ��� �������������� �������� ��� ������ ��������.

    friend std::ostream& operator <<(std::ostream& out, const BinarySignal& binarySignal);  // ����� ������� � ������� �������������

    friend std::istream& operator >>(std::istream& in, BinarySignal& binarySignal);         // ���� ������� �� �������� ������;

    BinarySignal& operator !();                             // �������� �������

    BinarySignal& operator +=(const BinarySignal& right);   // ���������� ������� ������ ��������

    BinarySignal& operator *=(const int right);            // ����������� ������� ����������� ����� ���

    BinarySignal& operator ()(const int position, const BinarySignal& binarySignalToInsert); // ������� � ����������� ������ �������(��� int) ������� �������(� ������� �������������� ���������());

    BinarySignal& operator ()(const int position, const int duration); // �������� ��������� ������� � ������������ �����(��� int) ����������� ������������(� ������� �������������� ���������()).

private:
	Signal signals_[MAX_COUNT_STATES];
	unsigned int size_ = 0;
};

