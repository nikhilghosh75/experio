#include "Values.h"

namespace ExperioEditor
{
THashtable<uint16_t, std::string> tags;
THashtable<uint16_t, std::string> layers;

TEvent OnValuesChanged;

namespace Internal
{
	uint16_t NextAvailible(const THashtable<uint16_t, std::string>& table)
	{
		for (uint16_t i = 0; i < 65535; i++)
		{
			if (!table.ExistsIn(i))
			{
				return i;
			}
		}
		return 65535;
	}
}

void AddValue(EValueType type)
{
	uint16_t nextAvailible = GetNextAvailibleValue(type);
	std::string temp;
	switch (type)
	{
	case EValueType::Layer:
		if (layers.GetSize() >= 64)
			return;
		temp = "Layer";
		temp.resize(32);
		layers.Insert(nextAvailible, temp);
		break;
	case EValueType::Tag:
		if (tags.GetSize() >= 65535)
			return;
		temp = "Tag               ";
		temp.resize(32);
		tags.Insert(nextAvailible, temp);
		break;
	}
	OnValuesChanged.Invoke();
}

void AddValue(const std::string & str, EValueType type)
{
	uint16_t nextAvailible = GetNextAvailibleValue(type);
	
	switch (type)
	{
	case EValueType::Layer:
		if (layers.GetSize() >= 64)
			return;
		
		layers.Insert(nextAvailible, str);
		break;
	case EValueType::Tag:
		if (tags.GetSize() >= 65535)
			return;

		tags.Insert(nextAvailible, str);
		break;
	}
	OnValuesChanged.Invoke();
}

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
	OnValuesChanged.Invoke();
}

void DeleteValue(uint16_t index, EValueType type)
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
	OnValuesChanged.Invoke();
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
	OnValuesChanged.Invoke();
}

FValue GetValue(uint16_t index, EValueType type)
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
	uint16_t index;
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
	OnValuesChanged.Invoke();
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
	OnValuesChanged.Invoke();
}

uint16_t GetNextAvailibleValue(EValueType type)
{
	switch (type)
	{
	case EValueType::Layer:
		return Internal::NextAvailible(layers);
	case EValueType::Tag:
		return Internal::NextAvailible(tags);
	}
}

THashtable<uint16_t, std::string>& GetTable(EValueType type)
{
	switch (type)
	{
	case EValueType::Layer: return layers;
	case EValueType::Tag: return tags;
	}
	return tags;
}

THashtable<uint16_t, std::string>& GetTags()
{
	return tags;
}

THashtable<uint16_t, std::string>& GetLayers()
{
	return layers;
}

void AddEventToOnValuesChanged(TFunctionPointer pointer)
{
	OnValuesChanged.AddListener(pointer);
}

unsigned int NumValues(EValueType type)
{
	switch (type)
	{
	case EValueType::Layer:
		return layers.GetSize();
	case EValueType::Tag:
		return tags.GetSize();
	}
	return 0;
}

void SetValueName(uint16_t index, std::string& newName, EValueType type)
{
	std::string temp = "TEST";
	std::string& str = temp;

	switch (type)
	{
	case EValueType::Layer:
	{
		str = layers.Get(index);
		str.assign(newName.c_str());
	}
		break;
	case EValueType::Tag:
	{
		str = tags.Get(index);
		str.assign(newName.c_str());
	}
		break;
	}
	OnValuesChanged.Invoke();
}

} // Experio Editor

unsigned short DefaultTagStringToNum(const char* string)
{
	return (unsigned short)ExperioEditor::GetValue(std::string(string), EValueType::Tag).index;
}

std::string DefaultTagNumToString(unsigned short num)
{
	return ExperioEditor::GetValue((int)num, EValueType::Tag).name;
}