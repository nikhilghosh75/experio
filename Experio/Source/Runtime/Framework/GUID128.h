#pragma once

#include <limits>
#include <stdint.h>
#include <string>
#include "../Containers/LString.h"
#include "../Math/Random.h"

struct GUID128
{
	uint64_t lowWord;
	uint64_t highWord;

	GUID128()
	{
		this->lowWord = 0;
		this->highWord = 0;
	}

	GUID128(uint64_t lowWord, uint64_t highWord)
	{
		this->lowWord = lowWord;
		this->highWord = highWord;
	}

	GUID128(const std::string& s)
	{
		int numDashes = LString::NumOfChars(s, '-');
		if (numDashes == 4)
		{
			uint64_t subwords[5];
			subwords[0] = LString::HexStringToLong(s.substr(0, 8));
			subwords[1] = LString::HexStringToLong(s.substr(9, 4));
			subwords[2] = LString::HexStringToLong(s.substr(14, 4));
			subwords[3] = LString::HexStringToLong(s.substr(19, 4));
			subwords[4] = LString::HexStringToLong(s.substr(24));
			this->lowWord = (subwords[0] << 32 | subwords[1] << 16 | subwords[2]);
			this->highWord = (subwords[3] << 48 | subwords[4]);
			return;
		}
		this->highWord = LString::HexStringToLong(s.substr(0, 16));
		this->lowWord = LString::HexStringToLong(s.substr(16));
	}

	static GUID128 Random()
	{
		uint64_t subWords[4];

		for (int i = 0; i < 4; i++)
		{
			subWords[i] = Random::RandomUIntInRange(0, 0xffffffff);
		}

		return GUID128((uint64_t)subWords[0] << 32 | subWords[1], (uint64_t)subWords[2] << 32 | subWords[3]);
	}

	std::string ToString() const
	{
		return LString::LongLongToHexString(this->highWord) + LString::LongLongToHexString(this->lowWord);
	}

	std::string ToVisualStudioString() const
	{
		std::string str = ToString();
		return str.substr(0, 8) + "-" + str.substr(8, 4) + "-" + str.substr(12, 4) + "-" + str.substr(16, 4) + "-" + str.substr(20);
	}

	bool operator==(const GUID128& other)
	{
		return this->lowWord == other.lowWord && this->highWord == other.highWord;
	}

	bool operator!=(const GUID128& other)
	{
		return this->lowWord != other.lowWord || this->highWord != other.highWord;
	}
};