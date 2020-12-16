#pragma once
#include <stdint.h>
#include <string>
#include "Runtime/Containers/THashtable.h"

enum class EEnumDataType : uint8_t
{
	NONE = 0,
	BYTE = 7,
	UBYTE = 8,
	SHORT = 15,
	USHORT = 16,
	INT = 31,
	UINT = 32,
	LONGLONG = 63,
	ULONGLONG = 64
};

class CodeEnum
{
public:
	std::string name;
	THashtable<int, std::string> values;
	EEnumDataType dataType;

	CodeEnum() = default;
	
	CodeEnum(const std::string& name)
	{
		this->name = name;
		this->dataType = EEnumDataType::INT;
	}

	CodeEnum(const std::string& name, EEnumDataType dataType)
	{
		this->name = name;
		this->dataType = dataType;
	}
};