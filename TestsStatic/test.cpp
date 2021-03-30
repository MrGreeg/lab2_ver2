#include "pch.h"
#include "BinarySignal.h"
#include <string>

TEST(TestDelete, Delete) {
	int a = 0;
	EXPECT_TRUE(BinarySignal("01110").isEqual(BinarySignal("011100110")(3, 4)));
}

TEST(TestInsert, Insert) {
	BinarySignal bs("000");
	bs(3, BinarySignal("111"));
	EXPECT_TRUE(BinarySignal("000111").isEqual(bs));
}

TEST(TestADD, Add) {
	BinarySignal bs("000");
	bs+=BinarySignal("111");
	EXPECT_TRUE(BinarySignal("000111").isEqual(bs));
}

TEST(TestMul, Mul) {
	BinarySignal bs("000111");
	bs *= 2;
	EXPECT_TRUE(BinarySignal("000111000111").isEqual(bs));
}

