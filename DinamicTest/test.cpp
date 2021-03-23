#include "pch.h"
#include "../Dinamic/DinamicArray.h"

TEST(TestsDinamicArray, block0to127) {
	DinamicArray dinamicArray(128);
	for (int i = 0; i < 128; i++) {
		dinamicArray[i].duration = i;
	}
	for (int i = 0; i < 128; i++) {
		EXPECT_EQ(dinamicArray[i].duration, i);
	}
}

TEST(TestsDinamicArray, block0to255) {
	DinamicArray dinamicArray(128);
	for (int i = 0; i < 255; i++) {
		dinamicArray[i].duration = i % 256;
	}
	for (int i = 0; i < 255; i++) {
		EXPECT_EQ(dinamicArray[i].duration, i % 256);
	}
}

TEST(TestsDinamicArray, block0to1000) {
	DinamicArray dinamicArray(64);
	for (int i = 0; i < 1000; i++) {
		dinamicArray[i].duration = i % 256;
	}
	for (int i = 0; i < 1000; i++) {
		EXPECT_EQ(dinamicArray[i].duration, i % 256);
	}
}

TEST(TestsDinamicArray, DinamicCopyTest) {
	DinamicArray dinamicArray(64);
	for (int i = 0; i < 1000; i++) {
		dinamicArray[i].duration = i % 256;
	}
	DinamicArray dinamicArrayCopy = dinamicArray;

	for (int i = 0; i < 1000; i++) {
		dinamicArray[i].duration = (i+1) % 256;
	}

	for (int i = 0; i < 1000; i++) {
		EXPECT_EQ(dinamicArrayCopy[i].duration, i % 256);
	}
}