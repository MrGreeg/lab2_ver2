#include "DinamicArray.h"
#include <iostream>


int main(){
	DinamicArray dinamicArray(256);
	for (int i = 0; i < 1000; i++) {
		dinamicArray[i].duration = i % 256;
	}
	DinamicArray dinamicArrayCopy = dinamicArray;
	//dinamicArray.~DinamicArray();
	std::cout << dinamicArrayCopy[15].duration << ' ' << dinamicArray[15].duration;
	return 0;
}