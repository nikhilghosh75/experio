#include "../../ExperioEditor/Source/Testing/UnitTestingFramework.h"
#include "Runtime/Debug/Debug.h"

TEST_SUITE("Debug", "Experio/Core");

UNIT_TEST(TestDebug, "Debug")
{
	size_t numLoggedMessages = Debug::GetDebugInfo().size();
	Debug::Log("Test Log");
	size_t newLoggedMessages = Debug::GetDebugInfo().size();
	ASSERT_EQUAL(newLoggedMessages - numLoggedMessages, 1, "");

	TEST_END();
}