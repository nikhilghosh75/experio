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

	TEST_END();
}