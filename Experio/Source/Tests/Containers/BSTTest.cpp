#include "../../ExperioEditor/Source/Testing/UnitTestingFramework.h"
#include "Runtime/Containers/TBinarySearchTree.h"

TEST_SUITE("BST", "Experio/Containers");

UNIT_TEST(TestBSTGeneral, "BST")
{
	TBinarySearchTree<int> tree;
	tree.Insert(9);
	tree.Insert(4);
	tree.Insert(3);
	tree.Insert(11);

	ASSERT_EQUAL(tree.Count(), 4, "");
	ASSERT_TRUE(tree.Exists(3), "");
	ASSERT_FALSE(tree.Exists(7), "");

	TEST_END();
}

UNIT_TEST(TestBSTMinMax, "BST")
{
	TBinarySearchTree<int> tree = {10, 4, 6, 8, 12, 16, 14};

	ASSERT_EQUAL(tree.Count(), 7, "");
	ASSERT_TRUE(tree.Exists(4), "");
	ASSERT_FALSE(tree.Exists(3), "");

	ASSERT_EQUAL(tree.MinElement(), 4, "");
	ASSERT_EQUAL(tree.MaxElement(), 16, "");

	TEST_END();
}

UNIT_TEST(TestBSTRemove, "BST")
{
	TBinarySearchTree<int> tree = { 10, 4, 6, 8, 12, 16, 14 };

	ASSERT_EQUAL(tree.Count(), 7, "");
	ASSERT_TRUE(tree.Exists(12), "");

	tree.Remove(12);

	ASSERT_EQUAL(tree.Count(), 6, "");
	ASSERT_FALSE(tree.Exists(12), "");

	TEST_END();
}

UNIT_TEST(TestBSTForEach, "BST")
{
	TBinarySearchTree<int> tree = { 2, 1, 3, 6, 4, 5 };
	int sum = 0;
	tree.ForEachInOrder([&sum](int& node) { sum += node; });

	ASSERT_EQUAL(sum, 21, "");

	TEST_END();
}