#include "BinarySignalDinamic.h"
#include <iostream>
#include <fstream>


int main(){
	BinarySignalDinamic binarySignal1("011100110");

	std::cout << "binarySignal1: " << binarySignal1 << std::endl;
	std::cout << "binarySignal2 - read from file" << std::endl;
	BinarySignalDinamic binarySignal2;
	std::ifstream in("temp.txt"); // �������� ���� ��� ������
	if (in.is_open())
	{
		in >> binarySignal2;
	}
	in.close();     // ��������� ����
	std::cout << "binarySignal2: " << binarySignal2 << std::endl;
	std::cout << "binarySignal2 delete part: " << binarySignal2(3, 4) << std::endl;
	std::cout << "binarySignal3 - copy binary signal 2: " << std::endl;
	BinarySignalDinamic binarySignal3 = binarySignal2;
	std::cout << "binarySignal3: " << binarySignal3 << std::endl;
	std::cout << "binarySignal3 - insert signal 1001" << std::endl;
	binarySignal3(3, BinarySignalDinamic("1001"));
	std::cout << "binarySignal3: " << binarySignal3 << std::endl;

	return 0;
}