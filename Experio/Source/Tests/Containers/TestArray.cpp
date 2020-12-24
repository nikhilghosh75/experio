#include "../../ExperioEditor/Source/Testing/UnitTestingFramework.h"
#include "Runtime/Containers/TArray.h"

TEST_SUITE("Array", "Experio/Containers");

UNIT_TEST(TestArrayGeneral, "Array")
{
	TArray<int> array(125, 5);

	// Check Count
	ASSERT_EQUAL(array.Count(), 5, "");

	// Check Access Function
	array[3] = 6;
	ASSERT_EQUAL(array[3], 6, "");
	ASSERT_EQUAL(array[4], 125, "");

	// Check Object Append
	array.Append(64);
	ASSERT_EQUAL(array.Count(), 6, "");
	ASSERT_EQUAL(array[5], 64, "");

	// Check Array Append
	int tempArray[2];
	tempArray[0] = 12;
	tempArray[1] = 13;
	array.Append(tempArray, 2);
	ASSERT_EQUAL(array.Count(), 8, "");
	ASSERT_EQUAL(array[7], 13, "");

	// Check Array Insert
	array.Insert(256, 5);
	ASSERT_EQUAL(array.Count(), 9, "");
	ASSERT_EQUAL(array[5], 256, "");

	// Check First
	ASSERT_EQUAL(array.First(), 125, "");

	// Check Last
	ASSERT_EQUAL(array.Last(), 13, "");

	TEST_END();
}

UNIT_TEST(TestArrayEmpty, "Array")
{
	TArray<int> array;

	ASSERT_EQUAL(array.Count(), 0, "");
	
	array.Append(1);
	array.Append(2);

	array.Empty();
	ASSERT_EQUAL(array.Count(), 0, "");

	TEST_END();
}

UNIT_TEST(TestArrayFind, "Array")
{
	TArray<int> array = { 2, 3, 4, 5, 6, 7 };

	ASSERT_EQUAL(array.FindIndex(4), 2, "");
	ASSERT_EQUAL(array.FindIndex(7), 6, "");
	ASSERT_EQUAL(array.FindIndex(4, 4), TArray<int>::NotFound, "");
	
	ASSERT_EQUAL(array.FindIndex([](const int& i) {return i % 7 == 5; }), 4, "");
	ASSERT_EQUAL(array.FindIndex([](const int& i) {return i % 9 == 8; }), TArray<int>::NotFound, "");

	TEST_END();
}

UNIT_TEST(TestArrayResize, "Array")
{
	TArray<int> array = { 3, 4,5 };
	
	array.Resize(30);

	ASSERT_EQUAL(array.Capacity(), 30, "Capacity is not what is expected");

	for (int i = 0; i < 26; i++)
	{
		array.Append(i + 5);
	}

	ASSERT_EQUAL(array.Count(), 29, "Count is not what is expected");
	array.Append(32);
	ASSERT_EQUAL(array.Count(), 30, "");
	array.Append(33);
	ASSERT_EQUAL(array.Count(), 31, "");
	ASSERT_GREATER_THAN(array.Capacity(), 30, "");

	TEST_END();
}