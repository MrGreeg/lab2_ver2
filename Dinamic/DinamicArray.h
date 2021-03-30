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
			for (int i = 0; i < size; i++) {	// ������� ��� ������������ ������
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

	Signal& operator[](const size_t position) const {
		if (position / sizeBlock >= size) {
			throw "Error going out of the array";
		}
		return array[position / sizeBlock][position % sizeBlock];
	};

	DinamicArray& operator = (const DinamicArray& object) {
		if (this != &object) { // ��������  a = a
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

	DinamicArray(const DinamicArray& object) {	// ���������� �����������
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

