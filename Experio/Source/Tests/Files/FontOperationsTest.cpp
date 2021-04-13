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

UNIT_TEST(TestFontOperationsEncoding, "FontOperations")
{
	FontData data;

	FCharacterInfo info1;
	info1.charCode = 113;
	data.characters.push_back(info1);
	ASSERT_EQUAL(LFontOperations::GetEncoding(data), ETextEncoding::ASCII, "");

	FCharacterInfo info2;
	info2.charCode = 140;
	data.characters.push_back(info2);
	ASSERT_EQUAL(LFontOperations::GetEncoding(data), ETextEncoding::UTF8, "");

	FCharacterInfo info3;
	info3.charCode = 650;
	data.characters.push_back(info3);
	ASSERT_EQUAL(LFontOperations::GetEncoding(data), ETextEncoding::UTF16, "");

	TEST_END();
}

UNIT_TEST(TestFontOperationsSizeOf, "FontOperations")
{
	FontData data;
	data.characters.resize(40);
	
	ASSERT_EQUAL(LFontOperations::SizeOf(data), 1316, "");

	TEST_END();
}