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

UNIT_TEST(TestVoidPtrOperator, "VoidPtr")
{
	VoidPtr v1 = VoidPtr((void*)336);
	VoidPtr v2 = VoidPtr((void*)203);

	ASSERT_GREATER_THAN(v1, v2, "");
	ASSERT_NOT_EQUAL(v1, v2, "");

	ASSERT_EQUAL(v1 + v2, VoidPtr((void*)539), "");
	ASSERT_EQUAL(v1 - v2, VoidPtr((void*)133), "");

	TEST_END();
}