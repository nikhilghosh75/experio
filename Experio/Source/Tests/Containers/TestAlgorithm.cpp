#include "../../ExperioEditor/Source/Testing/UnitTestingFramework.h"
#include "Runtime/Containers/Algorithm.h"

// using namespace Experio;

TEST_SUITE("Algorithm", "Experio/Containers");

UNIT_TEST(TestAlgorithmInsertAt, "Algorithm")
{
	std::vector<int> vector = { 1, 2, 3, 4, 5 };
	Experio::Algorithm::InsertAt(vector, 6, 2);
	ASSERT_EQUAL(vector.size(), 6, "");
	ASSERT_EQUAL(vector[0], 1, "");
	ASSERT_EQUAL(vector[1], 2, "");
	ASSERT_EQUAL(vector[2], 6, "");
	ASSERT_EQUAL(vector[3], 3, "");
	ASSERT_EQUAL(vector[4], 4, "");
	ASSERT_EQUAL(vector[5], 5, "");

	TEST_END();
}