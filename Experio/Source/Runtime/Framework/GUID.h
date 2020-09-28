#pragma once
#include <stdint.h>
#include <string>
#include "../Containers/LString.h"

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