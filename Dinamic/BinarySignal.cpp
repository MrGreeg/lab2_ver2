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
				levelSignal = 5;
			}
		}
		signals_[size_].level = level;
		signals_[size_++].duration = duration;

	}
}

BinarySignal BinarySignal::operator!() {
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

//BinarySignal& BinarySignal::operator+=(const BinarySignal& right) {
//	int index = GetIndex(posi)
//	return *this;
//}

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

//BinarySignal& BinarySignal::operator()(const int position, const BinarySignal& binarySignalToInsert)
//{	// как вариант перевести в строку из 0 и 1, вставить в нужное место и использовать конструктор от строки
//	if (position > MAX_COUNT_STATES * 255) {
//		throw "Exceeding the limits of the allowed position values";
//	}
//	if (size_ + binarySignalToInsert.size_ > MAX_COUNT_STATES-2) {
//		Signal tempSignal[MAX_COUNT_STATES];
//		int tempSize = 0;
//		for (int i = position / 255; i < size_; i++) {
//			if (position % 255 == 0) {
//				tempSignal[tempSize++] = tempSignal[i];
//			}
//			else {
//				tempSignal[tempSize].duration = tempSignal[i].duration - position % 255;
//				tempSignal[tempSize++].level = tempSignal[i].level;
//			}
//			tempSignal[i].duration = 0;
//		}
//		size_ = position / 255;
//		for (int i = 0; i < binarySignalToInsert.size_; i++) {
//			signals_[size_++] = binarySignalToInsert.signals_[i];
//		}
//		for (int i = 0; i < tempSize; i++) {
//			signals_[size_++] = tempSignal[i];
//		}
//	}
//	else {
//		throw "Exceeding the maximum size";
//	}
//}

BinarySignal& BinarySignal::operator()(const int position, const BinarySignal binarySignalToInsert)
{	// как вариант перевести в строку из 0 и 1, вставить в нужное место и использовать конструктор от строки
	if (position > MAX_COUNT_STATES * 255) {
		throw "Exceeding the limits of the allowed position values";
	}
	Offset offset = GetIndex(position);
	if (offset.index >= size_) {
		throw "Exceeding the limits of the allowed position values";
	}
	if (size_ + binarySignalToInsert.size_ >= MAX_COUNT_STATES - 1) {
		throw "The signal is too long";
	}
	Signal remainingPartSignal = signals_[offset.index + 1];	// остаток от сигнала
	signals_[offset.index + 1].duration = position - offset.length;
	signals_[offset.index + 2 + binarySignalToInsert.size_].level = remainingPartSignal.level;
	signals_[offset.index + 2 + binarySignalToInsert.size_].duration = remainingPartSignal.duration - signals_[offset.index + 1].duration;
	for (int i = offset.index + 2; i < offset.index + 2 + binarySignalToInsert.size_; i++) {	// сдвиг части массива
		signals_[i + binarySignalToInsert.size_ + 1] = signals_[i];
	}
	for (int i = offset.index + 2; i < offset.index + 2 + binarySignalToInsert.size_; i++) {	// вставка на освобождённое место сигнала
		signals_[i] = binarySignalToInsert.signals_[i - offset.index - 2];
	}
	size_ = offset.index + 1 + 2 * binarySignalToInsert.size_;

	// оптимизация
	int correct = 1;
	for (int i = 0; i < size_ - 1; i++) {
		if (signals_[i].duration != 0 && signals_[i].level == signals_[i + correct].level) {

			if (signals_[i].duration < 255) {
				char difference = 255 - signals_[i].duration;
				if (difference <= signals_[i + correct].duration) {
					signals_[i].duration += signals_[i + 1].duration;
					signals_[i + correct].duration = 0;
					signals_[i + correct].level = 0;
					correct += 1;
				}
				else {
					signals_[i].duration = 255;
					signals_[i + correct].duration = difference;
				}
			}
		}
		if ((i != i + correct - 1) && signals_[i].duration == 0 && signals_[i + correct - 1].duration != 0) {
			signals_[i] = signals_[i + correct - 1];
			signals_[i + correct - 1].duration = 0;
			signals_[i + correct - 1].level = 0;
		}
	}
	size_ -= correct - 1;

	return *this;
}

BinarySignal& BinarySignal::operator()(const int position, int duration)
{
	//std::string str = "";
	//for (int i = 0; i < size_; i++) {
	//	if (signals_[i].level == 1) {
	//		str += '1' * signals_[i].duration;
	//	}
	//	else {
	//		str += '0' * signals_[i].duration;
	//	}
	//}
	//str.erase(position, duration);
	//BinarySignal temp(str);
	//return temp;
	if (duration > 0) {
		Offset offsetStart = GetIndex(position);
		duration -= signals_[offsetStart.index + 1].duration - (position - offsetStart.length);
		signals_[offsetStart.index + 1].duration = position - offsetStart.length;
		Offset offsetStop = GetIndex(position + duration);

		signals_[offsetStop.index + 1].duration -= position + duration - offsetStop.length;
		duration -= position + duration - offsetStop.length;
		for (int i = offsetStart.index + 2; i < size_; i++) {
			signals_[i] = signals_[i + (offsetStop.index - offsetStart.index) - 1];
		}
		size_ -= offsetStop.index - offsetStart.index - 1;
		// оптимизация
		int correct = 1;
		for (int i = 0; i < size_ - 1; i++) {
			if (signals_[i].duration != 0 && signals_[i].level == signals_[i + correct].level) {

				if (signals_[i].duration < 255) {
					char difference = 255 - signals_[i].duration;
					if (difference <= signals_[i + correct].duration) {
						signals_[i].duration += signals_[i + 1].duration;
						signals_[i + correct].duration = 0;
						signals_[i + correct].level = 0;
						correct += 1;
					}
					else {
						signals_[i].duration = 255;
						signals_[i + correct].duration = difference;
					}
				}
			}
			if ((i != i + correct - 1) && signals_[i].duration == 0 && signals_[i + correct - 1].duration != 0) {
				signals_[i] = signals_[i + correct - 1];
				signals_[i + correct - 1].duration = 0;
				signals_[i + correct - 1].level = 0;
			}
		}
		size_ -= correct - 1;
	}


	return *this;
}

bool BinarySignal::isEqual(BinarySignal& right)
{
	bool result = size_ == right.size_;
	if (result == true) {
		for (int i = 0; i < size_; i++) {
			result = result && (signals_[i].duration == right.signals_[i].duration) && (signals_[i].level == right.signals_[i].level);
		}
	}

	return result;
}

Offset BinarySignal::GetIndex(const int position) const
{
	int length = 0;
	int index = -1;
	while (index + 1 < size_ && (signals_[index + 1].duration + length < position)) {
		index++;
		length += signals_[index].duration;

	}
	//if (position > length) {
	//	index = -1;
	//}
	return Offset(index, length);
}

std::ostream& operator<<(std::ostream& out, BinarySignal& binarySignal)
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
			//std::cout << inputSignal;
			int duration = 1;
			char level = inputSignal > '0' ? 1 : 0;
			char levelSignal = level;
			while (!in.eof() && tempBinarySignal.size_ < MAX_COUNT_STATES) {
				in >> inputSignal;
				//std::cout << inputSignal;
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
					levelSignal = 5;
				}
			}
			if (tempBinarySignal.size_ >= MAX_COUNT_STATES - 1 && !in.eof()) {
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
