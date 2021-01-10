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