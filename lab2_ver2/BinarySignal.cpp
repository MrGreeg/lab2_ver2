#include "BinarySignal.h"

BinarySignal::BinarySignal()
{
}

BinarySignal::BinarySignal(char level)
{
}

BinarySignal::BinarySignal(const std::string& str)
{
}

BinarySignal& BinarySignal::operator!()
{
	// TODO: �������� ����� �������� return
}

BinarySignal& BinarySignal::operator+=(const BinarySignal& right)
{
	// TODO: �������� ����� �������� return
}

BinarySignal& BinarySignal::operator*=(const int right)
{
	// TODO: �������� ����� �������� return
}

BinarySignal& BinarySignal::operator()(const int position, const BinarySignal& binarySignalToInsert)
{
	// TODO: �������� ����� �������� return
}

BinarySignal& BinarySignal::operator()(const int position, const int duration)
{
	// TODO: �������� ����� �������� return
}

std::ostream& operator<<(std::ostream& out, const BinarySignal& binarySignal)
{
	// TODO: �������� ����� �������� return
}

std::istream& operator>>(std::istream& in, BinarySignal& binarySignal)
{
	// TODO: �������� ����� �������� return
}
