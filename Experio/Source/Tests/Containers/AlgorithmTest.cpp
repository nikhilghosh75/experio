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

UNIT_TEST(TestAlgorithmExistsAt, "Algorithm")
{
	std::vector<int> vector = { 1, 2, 3, 5, 6, 11, 4, 9 };

	ASSERT_TRUE(Algorithm::ExistsIn(vector, 3), "");
	ASSERT_FALSE(Algorithm::ExistsIn(vector, 12), "");

	TEST_END();
}

UNIT_TEST(TestAlgorithmRemove, "Algorithm")
{
	std::vector<int> vector = { 1, 2, 3, 5, 6, 11, 4, 9 };

	Algorithm::RemoveElement(vector, 5);
	ASSERT_FALSE(Algorithm::ExistsIn(vector, 5), "");

	Algorithm::RemoveAt(vector, 2);
	ASSERT_FALSE(Algorithm::ExistsIn(vector, 3), "");

	TEST_END();
}

UNIT_TEST(TestAlgorithmAdd, "Algorithm")
{
	std::vector<int> vector = { 1, 2, 3, 5 };
	Algorithm::AddNumOf(vector, 8, 3);

	ASSERT_EQUAL(vector.size(), 7, "");
	ASSERT_EQUAL(vector[4], 8, "");
	ASSERT_EQUAL(vector[5], 8, "");
	ASSERT_EQUAL(vector[6], 8, "");

	TEST_END();
}

UNIT_TEST(TestAlgorithmAllOf, "Algorithm")
{
	std::vector<int> trueVector = { 1, 2, 3, 4, 5 };
	std::vector<int> falseVector = { -1, -2, 0, 2, 1 };

	bool trueAllOf = Algorithm::AllOf(trueVector, std::function<bool(const int&)>([](const int& i) { return i >= 0; }));
	bool falseAllOf = Algorithm::AllOf(falseVector, std::function<bool(const int&)>([](const int& i) { return i >= 0; }));

	// Fix this later
	ASSERT_TRUE(trueAllOf, "");
	ASSERT_FALSE(falseAllOf, "");

	TEST_END();
}

UNIT_TEST(TestAlgorithmNotAllOf, "Algorithm")
{
	std::vector<int> trueVector = { -1, -2, 0, 2, 1 };
	std::vector<int> falseVector = { 1, 2, 3, 4, 5 };

	bool trueNotAllOf = Algorithm::NotAllOf(trueVector, std::function<bool(const int&)>([](const int& i) { return i >= 0; }));
	bool falseNotAllOf = Algorithm::NotAllOf(falseVector, std::function<bool(const int&)>([](const int& i) { return i >= 0; }));

	// Fix this later
	ASSERT_TRUE(trueNotAllOf, "");
	ASSERT_FALSE(falseNotAllOf, "");

	TEST_END();
}