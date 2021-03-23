#include "BinarySignal.h"
#include <iostream>


int main() {
	BinarySignal binarySignal("011100110");
	std::cout << binarySignal << std::endl;
	std::cout << binarySignal(3, 4) << std::endl;
	/*binarySignal(3, 4);
	*/
	std::cout << BinarySignal("01110").isEqual(binarySignal) << std::endl;

	return 0;
}