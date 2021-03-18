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
	// TODO: вставьте здесь оператор return
}

BinarySignal& BinarySignal::operator+=(const BinarySignal& right)
{
	// TODO: вставьте здесь оператор return
}

BinarySignal& BinarySignal::operator*=(const int right)
{
	// TODO: вставьте здесь оператор return
}

BinarySignal& BinarySignal::operator()(const int position, const BinarySignal& binarySignalToInsert)
{
	// TODO: вставьте здесь оператор return
}

BinarySignal& BinarySignal::operator()(const int position, const int duration)
{
	// TODO: вставьте здесь оператор return
}

std::ostream& operator<<(std::ostream& out, const BinarySignal& binarySignal)
{
	// TODO: вставьте здесь оператор return
}

std::istream& operator>>(std::istream& in, BinarySignal& binarySignal)
{
	// TODO: вставьте здесь оператор return
}
