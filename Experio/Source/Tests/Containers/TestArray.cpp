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



	TEST_END();
}