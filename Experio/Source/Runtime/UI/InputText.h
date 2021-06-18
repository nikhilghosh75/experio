#pragma once

#include <string>
#include "../Framework/Component.h"

enum class EInputTextCharFlags : uint64_t
{
	None = 0,
	DecimalOnly = 1 << 0,
	HexadecimalOnly = 1 << 1,
	NoWhitespace = 1 << 2,
	UppercaseOnly = 1 << 3,
	LowercaseOnly = 1 << 4,
	PasswordDisplay = 1 << 5
};

class InputText : public Component
{

};