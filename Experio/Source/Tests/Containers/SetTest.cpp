#include "../../ExperioEditor/Source/Testing/UnitTestingFramework.h"
#include "Runtime/Containers/TSet.h"

TEST_SUITE("Set", "Experio/Containers");

UNIT_TEST(TestSetGeneral, "Set")
{
	TSet<int> set;
	
	set.Insert(40);
	set.Insert(26);
	set.Insert(64);
	set.Insert(8);

	ASSERT_EQUAL(set.Count(), 4, "");
	ASSERT_TRUE(set.Exists(40), "");
	ASSERT_FALSE(set.Exists(50), "");

	TEST_END();
}

UNIT_TEST(TestSetMerge, "Set")
{
	TSet<int> set1;
	TSet<int> set2;

	set1.Insert(40);
	set1.Insert(50);
	set1.Insert(60);
	set1.Insert(80);

	set2.Insert(10);
	set2.Insert(20);
	set2.Insert(30);
	set2.Insert(40);
	set2.Insert(70);

	TSet<int> mergedSet = TSet<int>::Merge(set1, set2);

	ASSERT_EQUAL(mergedSet.Count(), 8, "");
	ASSERT_TRUE(mergedSet.Exists(10), "");
	ASSERT_FALSE(mergedSet.Exists(90), "");

	TEST_END();
}