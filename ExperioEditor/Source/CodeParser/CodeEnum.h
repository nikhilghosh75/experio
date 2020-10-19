#pragma once
#include <stdint.h>
#include <map>
#include <string>

enum class EEnumDataType : uint8_t
{
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
	std::map<int, std::string> values;
	EEnumDataType dataType;
};