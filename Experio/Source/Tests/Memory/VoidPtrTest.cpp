#include "../../ExperioEditor/Source/Testing/UnitTestingFramework.h"
#include "Runtime/Memory/VoidPtr.h"

TEST_SUITE("VoidPtr", "Experio/Memory");

UNIT_TEST(TestVoidPtrGeneral, "VoidPtr")
{
	VoidPtr voidPtr = VoidPtr((void*)204);
	ASSERT_EQUAL(voidPtr, (void*)204, "");
	ASSERT_EQUAL(voidPtr, VoidPtr((void*)204), "");

	voidPtr = voidPtr + 5;
	ASSERT_EQUAL(voidPtr, (void*)209, "");
	ASSERT_EQUAL(voidPtr, VoidPtr((void*)209), "");

	TEST_END();
}