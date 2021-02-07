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
	void AddValue(EValueType type);
	void AddValue(const std::string& str, EValueType type);
	void AddValue(FValue value, EValueType type);

	void ClearValues();
	void ClearValues(EValueType type);

	void DeleteValue(uint16_t index, EValueType type);
	void DeleteValue(std::string name, EValueType type);

	FValue GetValue(uint16_t index, EValueType type);
	FValue GetValue(std::string name, EValueType type);

	uint16_t GetNextAvailibleValue(EValueType type);

	THashtable<uint16_t, std::string>& GetTable(EValueType type);

	THashtable<uint16_t, std::string>& GetTags();
	THashtable<uint16_t, std::string>& GetLayers();

	unsigned int NumValues(EValueType type);

	void SetValueName(uint16_t index, std::string& newName, EValueType type);
}