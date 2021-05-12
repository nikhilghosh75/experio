#include "../../ExperioEditor/Source/Testing/UnitTestingFramework.h"
#include "Runtime/Containers/TQueue.h"

TEST_SUITE("Queue", "Experio/Containers");

UNIT_TEST(TestQueueGeneral, "Queue")
{
	TQueue<int> queue;
	queue.Push(1);
	queue.Push(3);
	queue.Push(6);

	ASSERT_EQUAL(queue.Count(), 3, "");
	ASSERT_EQUAL(queue.Peek(), 1, "");
	ASSERT_EQUAL(queue.PeekAt(1), 3, "");
	ASSERT_EQUAL(queue.Pop(), 1, "");
	
	TEST_END();
}

UNIT_TEST(TestQueueLarge, "Queue")
{
	TQueue<size_t> queue;
	for (size_t i = 0; i < 100; i++)
	{
		queue.Push(i);
	}

	for (size_t i = 0; i < 99; i--)
	{
		ASSERT_EQUAL(queue.Pop(), i, "");
	}

	TEST_END();
}

UNIT_TEST(TestQueueInitializer, "Queue")
{
	TQueue<int> queue = { 1, 2, 3, 4, 5, 6 };

	ASSERT_EQUAL(queue.Peek(), 1, "");
	ASSERT_EQUAL(queue.Pop(), 1, "");

	TEST_END();
}

UNIT_TEST(TestQueueEmpty, "Empty")
{
	TQueue<int> queue;
	ASSERT_TRUE(queue.IsEmpty(), "");

	queue.Push(2);
	ASSERT_FALSE(queue.IsEmpty(), "");

	queue.Empty();
	ASSERT_TRUE(queue.IsEmpty(), "");

	TEST_END();
}