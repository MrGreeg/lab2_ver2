#include "pch.h"
#include "../lab2ver2/BinarySignal.h"
#include <string>

TEST(TestSum, ZeroAddZero) {
	//std::string str;
	//getline(std::cin, str);
	//BinarySignal bs1(0);
	//BinarySignal bs2(0);
	int a = 0;
	EXPECT_TRUE(BinarySignal("01110").isEqual(BinarySignal("011100110")(3, 4)));
}

//class TestDinamicArray : public ::testing::Test
//{
//protected:
//	void SetUp()
//	{
//		foo = new DinamicArray;
//		foo->i = 5;
//	}
//	void TearDown()
//	{
//		delete foo;
//	}
//	Foo* foo;
//};

//TEST_F(TestFoo, test1)
//{
//	ASSERT_EQ(foo->i, 5);
//	foo->i = 10;
//}
//
//TEST_F(TestFoo, test2)
//{
//	ASSERT_EQ(foo->i, 5);
//}

//int main(int argc, char* argv[])
//{
//	::testing::InitGoogleTest(&argc, argv);
//	return RUN_ALL_TESTS();
//}