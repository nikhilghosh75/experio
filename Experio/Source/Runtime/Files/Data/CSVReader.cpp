#include "CSVReader.h"
#include <fstream>
#include <sstream>
#include "../../Containers/Algorithm.h"
#include "../../Containers/LString.h"
#include "../../Debug/Debug.h"

bool CSVReader::DetectDelimiter(const std::string & text)
{
	return LString::HasChars(text, {',', '\t', ';'});
}

std::string CSVReader::ParseCell(const std::string & text, size_t & i)
{
	bool quoted = text[i] == '"';
	if (quoted) i++;

	std::string str;
	while (i < text.size())
	{
		char c = text[i];
		if (quoted)
		{
			if (c == '"')
			{
				i++;
				if (i < text.size() || c == '\n' || c == '\r' || c == ',') break;
			}
		}
		else
		{
			if (c == '\n' || c == '\r' || c == ',') break;
		}
		str += c;
		i++;
	}

	return str;
}

EDataColumnType CSVReader::GetColumnType(const std::string & text)
{
	bool hasAlpha = LString::HasAlpha(text);

	if (hasAlpha)
		return EDataColumnType::STRING;

	bool hasNumeric = LString::HasNumeric(text);
	if (hasNumeric)
	{
		bool hasPeriod = LString::HasChar(text, '.');
		if (hasPeriod)
		{
			return EDataColumnType::FLOAT;
		}
		return EDataColumnType::INT;
	}

	return EDataColumnType::NONE;
}

Datatable * CSVReader::ReadFile(const char * filename)
{
	std::ifstream csvFile(filename);
	if (csvFile.fail())
	{
		Debug::LogError("CSV File could not be opened");
		return nullptr;
	}

	std::stringstream buffer;
	buffer << csvFile.rdbuf();
	std::string str = buffer.str();

	if (!DetectDelimiter(str))
	{
		Debug::LogError("CSV File has no delimiter");
		return nullptr;
	}

	std::vector<std::string> columnNames;

	size_t currentIndex = 0;
	while (currentIndex < str.size())
	{
		columnNames.push_back(ParseCell(str, currentIndex));
		if (str[currentIndex] == '\n' || str[currentIndex] == '\r') 
			break;
		currentIndex++;
	}

	std::vector<std::string> data;
	while (currentIndex < str.size())
	{
		data.push_back(ParseCell(str, currentIndex));
		currentIndex++;
	}
	
	if (data[0].size() == 0)
	{
		Experio::Algorithm::RemoveAt(data, 0);
	}

	// Parse Datatable
	std::vector<std::vector<float>> floatColumns = std::vector<std::vector<float>>();
	floatColumns.reserve(1);
	std::vector<std::vector<int32_t>> intColumns = std::vector<std::vector<int32_t>>();
	intColumns.reserve(1);
	std::vector< std::vector<std::string>> stringColumns = std::vector<std::vector<std::string>>();
	stringColumns.reserve(1);
	std::vector<EDataColumnType> columnTypes;

	uint32_t numColumns = columnNames.size();
	uint32_t numRows = data.size() / numColumns;
	columnTypes.reserve(numColumns);
	for (uint32_t i = 0; i < numColumns; i++)
	{
		EDataColumnType columnType = GetColumnType(data[i]);
		switch (columnType)
		{
		case EDataColumnType::FLOAT:
			floatColumns.push_back(std::vector<float>()); break;
		case EDataColumnType::INT:
			intColumns.push_back(std::vector<int32_t>()); break;
		case EDataColumnType::STRING:
			stringColumns.push_back(std::vector<std::string>()); break;
		}
		columnTypes.push_back(columnType);
	}

	for (uint32_t i = 0; i < numRows; i++)
	{
		uint32_t currentIntColumn = 0, currentFloatColumn = 0, currentStringColumn = 0;
		for (uint32_t j = 0; j < numColumns; j++)
		{
			std::string& element = data[i * numColumns + j];
			switch (columnTypes[j])
			{
			case EDataColumnType::FLOAT:
				floatColumns[currentFloatColumn].push_back(LString::StringToFloat(element));
				currentFloatColumn++;
				break;
			case EDataColumnType::INT:
				intColumns[currentIntColumn].push_back(LString::StringToInt(element));
				currentIntColumn++;
				break;
			case EDataColumnType::STRING:
				stringColumns[currentStringColumn].push_back(element);
				currentStringColumn++;
				break;
			}
		}
	}

	Datatable* datatable = new Datatable(intColumns, floatColumns, stringColumns, columnNames, columnTypes);
	return datatable;
}
