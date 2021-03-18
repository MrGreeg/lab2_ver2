#include "BinarySignal.h"
#include <iostream>

BinarySignal::BinarySignal()
{
}

BinarySignal::BinarySignal(char level) {
	if (level == 1 || level > '0') {
		level = 1;
	}
	else {
		level = 0;
	}
	for (int i = 0; i < MAX_COUNT_STATES; i++) {
		signals_[i].level = level;
		signals_[i].duration = 255;
	}
}

BinarySignal::BinarySignal(const std::string& inputSignal) {
	size_ = 0;
	if (inputSignal.length() > 0) {
		int duration = 1;
		char level = inputSignal[0] > '0' ? 1 : 0;
		char levelSignal = level;
		for (int i = 1; i < inputSignal.length(); ++i) {
			levelSignal = inputSignal[i] > '0' ? 1 : 0;
			if (level == levelSignal) {
				if (duration == 255) {
					signals_[size_].level = level;
					signals_[size_++].duration = duration;
					duration = 0;
				}
				else {
					duration++;
				}
			}
			else {
				signals_[size_].level = level;
				signals_[size_++].duration = duration;
				duration = 1;
				level = levelSignal;
			}
		}
		signals_[size_].level = level;
		signals_[size_++].duration = duration;
	}
}

BinarySignal& BinarySignal::operator!() {
	BinarySignal tempBinarySignal = *this;
	for (int i = 0; i < size_; ++i) {
		tempBinarySignal.signals_[i].level = (signals_[i].level + 1) % 2;	// Инверсия значения сигнала
	}
	return tempBinarySignal;
}

BinarySignal& BinarySignal::operator+=(const BinarySignal& right) {
	if ((signals_[size_ - 1].level == right.signals_[0].level) &&
		(signals_[size_ - 1].duration + right.signals_[0].duration > 255)) {
		if (size_ + right.size_ - 1 > MAX_COUNT_STATES) {
			throw "Exceeding the maximum size";
		}
	}
	else {
		if (size_ + right.size_ > MAX_COUNT_STATES) {
			throw "Exceeding the maximum size";
		}
	}

	int countElement = (size_ + right.size_) % MAX_COUNT_STATES;
	for (int i = 0; i < countElement; ++i) {
		signals_[size_].level = right.signals_[i].level;
		signals_[size_++].duration = right.signals_[i].duration;
	}
	return *this;
}

BinarySignal& BinarySignal::operator*=(const int right)
{
	if ((signals_[size_ - 1].level == signals_[0].level) &&
		(signals_[size_ - 1].duration + signals_[0].duration > 255)) {
		if (size_ * 2 - right - 1 > MAX_COUNT_STATES) {
			throw "Exceeding the maximum size";
		}
	}
	else {
		if (size_ * 2 > MAX_COUNT_STATES) {
			throw "Exceeding the maximum size";
		}
	}

	int size = size_;
	for (int n = 0; n < right; ++n) {
		for (int i = 0; i < size && size_ < MAX_COUNT_STATES; ++i) {
			signals_[size_].level = signals_[i].level;
			signals_[size_++].duration = signals_[i].duration;
		}
	}
	return *this;
}

BinarySignal& BinarySignal::operator()(const int position, const BinarySignal& binarySignalToInsert)
{	// как вариант перевести в строку из 0 и 1, вставить в нужное место и использовать конструктор от строки
	if (position > MAX_COUNT_STATES * 255) {
		throw "Exceeding the limits of the allowed position values";
	}
	if (size_ + binarySignalToInsert.size_ > MAX_COUNT_STATES-2) {
		Signal tempSignal[MAX_COUNT_STATES];
		int tempSize = 0;
		for (int i = position / 255; i < size_; i++) {
			if (position % 255 == 0) {
				tempSignal[tempSize++] = tempSignal[i];
			}
			else {
				tempSignal[tempSize].duration = tempSignal[i].duration - position % 255;
				tempSignal[tempSize++].level = tempSignal[i].level;
			}
			tempSignal[i].duration = 0;
		}
		size_ = position / 255;
		for (int i = 0; i < binarySignalToInsert.size_; i++) {
			signals_[size_++] = binarySignalToInsert.signals_[i];
		}
		for (int i = 0; i < tempSize; i++) {
			signals_[size_++] = tempSignal[i];
		}
	}
	else {
		throw "Exceeding the maximum size";
	}
}

BinarySignal& BinarySignal::operator()(const int position, const int duration)
{
	std::string str = "";
	for (int i = 0; i < size_; i++) {
		if (signals_[i].level == 1) {
			str += '1' * signals_[i].duration;
		}
		else {
			str += '0' * signals_[i].duration;
		}
	}
	str.erase(position, duration);
	BinarySignal temp(str);
	return temp;
}

std::ostream& operator<<(std::ostream& out, const BinarySignal& binarySignal)
{
	char symbol;
	for (int i = 0; i < binarySignal.size_; ++i) {
		if (binarySignal.signals_[i].level == 0) {
			symbol = '_';
		}
		else {
			symbol = char(196);
		}
		if (i > 0 && binarySignal.signals_[i - 1].level != binarySignal.signals_[i].level) {
			if (binarySignal.signals_[i].level == 0) {
				out << char(191);
			}
			else {
				out << char(218);
			}
		}
		for (int j = 0; j < binarySignal.signals_[i].duration; ++j) {
			out << symbol;
		}
	}
	return out;
}

std::istream& operator>>(std::istream& in, BinarySignal& binarySignal)
{
	if (binarySignal.size_ < MAX_COUNT_STATES) {
		try {
			BinarySignal tempBinarySignal = binarySignal;
			char inputSignal;
			in >> inputSignal;
			int duration = 1;
			char level = inputSignal > '0' ? 1 : 0;
			char levelSignal = level;
			while (!in.eof() && tempBinarySignal.size_<MAX_COUNT_STATES) {
				in >> inputSignal;
				levelSignal = inputSignal > '0' ? 1 : 0;
				if (level == levelSignal) {
					if (duration == 255) {
						tempBinarySignal.signals_[tempBinarySignal.size_].level = level;
						tempBinarySignal.signals_[tempBinarySignal.size_++].duration = duration;
						duration = 0;
					}
					else {
						duration++;
					}
				}
				else {
					tempBinarySignal.signals_[tempBinarySignal.size_].level = level;
					tempBinarySignal.signals_[tempBinarySignal.size_++].duration = duration;
					duration = 1;
					level = levelSignal;
				}
			}
			if (tempBinarySignal.size_ >= MAX_COUNT_STATES && !in.eof()) {
				throw "Exceeding the maximum size";
			}
			else {
				tempBinarySignal.signals_[tempBinarySignal.size_].level = level;
				tempBinarySignal.signals_[tempBinarySignal.size_++].duration = duration;

				binarySignal = tempBinarySignal;
			}
			
		}
		catch (std::ios_base::iostate except) {
			in.setstate(std::ios_base::failbit);
			throw "Exceeding input stream";
		}
	}
	else {
		throw "Exceeding the maximum size";
	}
	return in;
}
