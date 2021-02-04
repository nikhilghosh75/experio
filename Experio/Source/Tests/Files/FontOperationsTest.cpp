#pragma once

#include "../../ExperioEditor/Source/Testing/UnitTestingFramework.h"
#include "Runtime/Files/Font/LFontOperations.h"

TEST_SUITE("FontOperations", "Experio/Files");

UNIT_TEST(TestFontOperationsCharset, "FontOperations")
{
	ASSERT_EQUAL(LFontOperations::CharsetToString(ECharacterSet::ARABIC), "Arabic", "");

	TEST_END();
}

UNIT_TEST(TestFontOperationsHas, "FontOperations")
{
	FontData data;
	
	FCharacterInfo info;
	info.charCode = 113;
	data.characters.push_back(info);

	info.charCode = 400;
	data.characters.push_back(info);

	ASSERT_TRUE(data.HasCharacter(113), "");
	ASSERT_FALSE(data.HasCharacter(30), "");

	TEST_END();
}