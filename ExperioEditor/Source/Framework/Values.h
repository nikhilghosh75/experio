#pragma once
#include <string>
#include "Runtime/Containers/THashtable.h"

enum class EValueType
{
	Unknown,
	Tag,
	Layer
};

struct FValue
{
	int index;
	std::string name;

	FValue(int index, std::string name)
	{
		this->index = index;
		this->name = name;
	}
};

namespace ExperioEditor
{
	void AddValue(FValue value, EValueType type);
	void DeleteValue(int index, EValueType type);
	void DeleteValue(std::string name, EValueType type);

	FValue GetValue(int index, EValueType type);
	FValue GetValue(std::string name, EValueType type);

	void ClearValues();
	void ClearValues(EValueType type);
}