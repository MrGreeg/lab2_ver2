#pragma once

const int SIZE_BLOCK = 128;

struct Signal {
	unsigned char level = 0;
	unsigned char duration = 0;
};

class DinamicArray
{
public:
	DinamicArray() {
		sizeBlock = SIZE_BLOCK;
	};

	DinamicArray(const int sizeBlock) {
		DinamicArray::sizeBlock = sizeBlock;
	};

	~DinamicArray() {
		for (int i = 0; i < size; i++) {
			delete[] array[i];
		}
		delete[] array;
		size = 0;
	};
	
	Signal& operator[](size_t position) {
		if (position / sizeBlock >= size) {
			int newSize = position / sizeBlock + 1;
			Signal** temp = new Signal * [newSize];
			for (int i = 0; i < size; i++) {	// перенос уже существующих данных
				temp[i] = array[i];
			}
			for (int i = size; i < newSize; i++) {
				temp[i] = new Signal[sizeBlock];
			}
			delete[] array;
			array = temp;
			size = newSize;
		}
		return array[position / sizeBlock][position % sizeBlock];
	};

	DinamicArray& operator = (const DinamicArray& object) {
		if (this != &object) { // проверка  a = a
			for (int i = 0; i < size; i++) {
				delete[] array[i];
			}
			delete[] array;
			array = nullptr;
			if ((size = object.size) != 0) {
				array = new Signal * [size];
				for (int i = 0; i < size; i++) {
					array[i] = new Signal[sizeBlock];
				}
				for (int i = 0; i < size; i++) {
					for (int j = 0; j < sizeBlock; j++) {
						array[i][j] = object.array[i][j];
					}
				}
			}
		}
		return *this;
	};

	DinamicArray(const DinamicArray& object) {	// Копирующий конструктор
		sizeBlock = object.sizeBlock;
		if (object.size) {
			size = object.size;
			array = new Signal * [size];
			sizeBlock = object.sizeBlock;
			for (int i = 0; i < size; i++) {
				array[i] = new Signal[sizeBlock];
			}
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < sizeBlock; j++) {
					array[i][j] = object.array[i][j];
				}
			}
		}
	};

private:
	Signal** array = nullptr;
	unsigned int size = 0;
	int sizeBlock = 256;
};
//
//template<class TN>
//inline DinamicArray::DinamicArray()
//{
//	sizeBlock = SIZE_BLOCK;
//}
//
//template<class TN>
//inline DinamicArray<TN>::DinamicArray(int sizeBlock)
//{
//	DinamicArray::sizeBlock = sizeBlock;
//}
//
//template<class TN>
//inline DinamicArray<TN>& DinamicArray<TN>::operator[](const int position)
//{
//	if (position / sizeBlock > size) {
//		TN** temp = new * TN(position / sizeBlock);
//		for (int i = 0 i < size; i++) {
//			temp[i] = array[i];
//		}
//		for (int i = size; i < position / sizeBlock; i++) {
//			temp[i] = new TN(sizeBlock);
//		}
//		delete[] array;
//		array = temp;
//		size = position / sizeBlock;
//	}
//	return *array[position / sizeBlock][position % sizeBlock];
//}
