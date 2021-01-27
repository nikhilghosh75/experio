#include "../../ExperioEditor/Source/Testing/UnitTestingFramework.h"
#include "Runtime/Files/LFileOperations.h"

TEST_SUITE("FileOperations", "Experio/Files");

UNIT_TEST(TestFileOperationsExt, "FileOperations")
{
	ASSERT_EQUAL(LFileOperations::GetExtension("Folder/File.png"), "png", "");
	
	ASSERT_TRUE(LFileOperations::DoesFileHaveExtension("Wolvey.csv", "csv"), "");

	TEST_END();
}