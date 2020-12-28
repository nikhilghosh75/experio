#include "../../ExperioEditor/Source/Testing/UnitTestingFramework.h"
#include "Runtime/Containers/Algorithm.h"

using namespace Experio;

TEST_SUITE("Algorithm", "Experio/Containers");

UNIT_TEST(TestAlgorithmInsertAt, "Algorithm")
{
	std::vector<int> vector = { 1, 2, 3, 4, 5 };
	Algorithm::InsertAt(vector, 6, 2);
	ASSERT_EQUAL(vector.size(), 6, "");
	ASSERT_EQUAL(vector[0], 1, "");
	ASSERT_EQUAL(vector[1], 2, "");
	ASSERT_EQUAL(vector[2], 6, "");
	ASSERT_EQUAL(vector[3], 3, "");
	ASSERT_EQUAL(vector[4], 4, "");
	ASSERT_EQUAL(vector[5], 5, "");

	TEST_END();
}

UNIT_TEST(TestAlgorithmGetUnique, "Algorithm")
{
	std::vector<int> vector = { 1, 1, 2, 3, 5, 6, 7, 5, 9};
	std::vector<int> unique = Algorithm::GetUnique(vector);
	ASSERT_EQUAL(unique[0], 1, "");
	ASSERT_EQUAL(unique[1], 2, "");
	ASSERT_EQUAL(unique[2], 3, "");
	ASSERT_EQUAL(unique[3], 5, "");
	ASSERT_EQUAL(unique[4], 6, "");
	ASSERT_EQUAL(unique[5], 7, "");
	ASSERT_EQUAL(unique[6], 9, "");

	TEST_END();
}