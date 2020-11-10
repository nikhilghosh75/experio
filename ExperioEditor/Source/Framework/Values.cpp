#include "Values.h"

namespace ExperioEditor
{
THashtable<int, std::string> tags;
THashtable<int, std::string> layers;

void AddValue(FValue value, EValueType type)
{
	switch (type)
	{
	case EValueType::Layer:
		layers.Insert(value.index, value.name);
		break;
	case EValueType::Tag:
		tags.Insert(value.index, value.name);
		break;
	}
}

void DeleteValue(int index, EValueType type)
{
	switch (type)
	{
	case EValueType::Layer:
		layers.Remove(index);
		break;
	case EValueType::Tag:
		tags.Remove(index);
		break;
	}
}

void DeleteValue(std::string name, EValueType type)
{
	switch (type)
	{
	case EValueType::Layer:
		layers.RemoveValue(name);
		break;
	case EValueType::Tag:
		tags.RemoveValue(name);
		break;
	}
}

FValue GetValue(int index, EValueType type)
{
	std::string name;
	bool found;
	switch (type)
	{
	case EValueType::Layer: 
		found = layers.SafeGet(index, name);
		if (found)
		{
			return FValue(index, name);
		}
		break;
	case EValueType::Tag:
		found = tags.SafeGet(index, name);
		if (found)
		{
			return FValue(index, name);
		}
		break;
	}
	return FValue(0, "NOT FOUND");
}

FValue GetValue(std::string name, EValueType type)
{
	int index;
	bool found;

	switch (type)
	{
	case EValueType::Layer:
		found = layers.Find(name, index);
		if (found)
		{
			return FValue(index, name);
		}
		break;
	case EValueType::Tag:
		found = tags.Find(name, index);
		if (found)
		{
			return FValue(index, name);
		}
		break;
	}
	return FValue(0, "NOT FOUND");
}

void ClearValues()
{
	layers.Empty();
	tags.Empty();
}

void ClearValues(EValueType type)
{
	switch (type)
	{
	case EValueType::Layer:
		layers.Empty();
		break;
	case EValueType::Tag:
		tags.Empty();
		break;
	}
}

} // Experio

unsigned short DefaultTagStringToNum(const char* string)
{
	return (unsigned short)ExperioEditor::GetValue(std::string(string), EValueType::Tag).index;
}

std::string DefaultTagNumToString(unsigned short num)
{
	return ExperioEditor::GetValue((int)num, EValueType::Tag).name;
}