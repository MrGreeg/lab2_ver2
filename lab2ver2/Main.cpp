#include "BinarySignal.h"
#include <iostream>
#include <fstream>


int main() {
	BinarySignal binarySignal1("011100110");

	std::cout << "binarySignal1: " << binarySignal1 << std::endl;
	std::cout << "binarySignal2 - read from file" << std::endl;
	BinarySignal binarySignal2;
	std::ifstream in("temp.txt"); // окрываем файл для чтения
	if (in.is_open())
	{
		in >> binarySignal2;
	}
	in.close();     // закрываем файл
	std::cout << "binarySignal2: " << binarySignal2 << std::endl;
	std::cout << "binarySignal2 delete part: " << binarySignal2(3, 4) << std::endl;
	std::cout << "binarySignal3 - copy binary signal 2: " << std::endl;
	BinarySignal binarySignal3 = binarySignal2;
	std::cout << "binarySignal3: " << binarySignal3 << std::endl;
	std::cout << "binarySignal3 - insert signal 1001" << std::endl;
	binarySignal3(3, BinarySignal("1001"));
	std::cout << "binarySignal3: " << binarySignal3 << std::endl;
	std::cout << "invert binarySignal3: " << std::endl;
	binarySignal3 = !binarySignal3;
	std::cout << "binarySignal3: " << binarySignal3 << std::endl;



	return 0;
}