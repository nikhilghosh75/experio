#pragma once
#include <stdint.h>
#include <string>
#include "../Containers/LString.h"
#include "../Math/Random.h"

struct GUID
{
	uint64_t id;

	GUID(uint64_t id)
	{
		this->id = id;
	}

	GUID(std::string s)
	{
		this->id = (uint64_t)LString::HexStringToLong(s);
	}

	static GUID Random()
	{
		uint64_t subWords[2];

		for (int i = 0; i < 2; i++)
		{
			subWords[i] = Random::RandomUIntInRange(0, 0xffffffff);
		}

		return GUID((uint64_t)subWords[0] << 32 | subWords[1]);
	}

	std::string ToString()
	{
		return LString::LongLongToHexString(this->id);
	}

	bool operator==(const GUID& other)
	{
		return this->id == other.id;
	}

	bool operator!=(const GUID& other)
	{
		return this->id != other.id;
	}
};