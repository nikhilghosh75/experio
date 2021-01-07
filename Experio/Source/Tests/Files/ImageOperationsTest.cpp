#include "../../ExperioEditor/Source/Testing/UnitTestingFramework.h"
#include "Runtime/Files/Images/LImageOperations.h"

TEST_SUITE("ImageOperations", "Experio/Files");

UNIT_TEST(TestImageOperationsSize, "ImageOperations")
{
	ASSERT_EQUAL(LImageOperations::SizeOfImage(512, 384, EImageEncoding::Grayscale), 196608, "");
	ASSERT_EQUAL(LImageOperations::SizeOfImage(128, 384, EImageEncoding::TruecolorAlpha), 196608, "");

	TEST_END();
}