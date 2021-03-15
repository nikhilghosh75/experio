#include "../../ExperioEditor/Source/Testing/UnitTestingFramework.h"
#include "Runtime/Files/LFileOperations.h"

TEST_SUITE("FileOperations", "Experio/Files");

UNIT_TEST(TestFileOperationsExt, "FileOperations")
{
	ASSERT_EQUAL(LFileOperations::GetExtension("Folder/File.png"), "png", "");
	
	ASSERT_TRUE(LFileOperations::DoesFileHaveExtension("Wolvey.csv", "csv"), "");
	ASSERT_FALSE(LFileOperations::DoesFileHaveExtension("Wolf.png", "csv"), "");

	TEST_END();
}

UNIT_TEST(TestFileOperationsBytes, "FileOperations")
{
	ASSERT_EQUAL(LFileOperations::MultipleToBytes(2.340, EDataUnit::Kilobyte), 2340, "");
	ASSERT_EQUAL(LFileOperations::MultipleToBytes(42.945000, EDataUnit::Megabyte), 42945000, "");

	TEST_END();
}

UNIT_TEST(TestFileOperationsGet, "FileOperations")
{
	ASSERT_EQUAL(LFileOperations::GetDirectory("Experio/Source/Third Party/RCCPP.h"), "Experio/Source/Third Party", "");
	ASSERT_EQUAL(LFileOperations::GetExtension("Experio/Source/Third Party/RCCPP.cpp"), "cpp", "");

	TEST_END();
}

UNIT_TEST(TestFileOperationsAsset, "FileOperations")
{
	ASSERT_EQUAL(LFileOperations::StringToAssetType("Mesh"), EAssetType::Mesh, "");
	ASSERT_EQUAL(LFileOperations::AssetTypeToString(EAssetType::Mesh), "Mesh", "");

	TEST_END();
}