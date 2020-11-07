#pragma once

#include "DataReader.h"

class CSVReader : DataReader
{
	bool DetectDelimiter(const std::string& text);

	std::string ParseCell(const std::string& text, size_t& i);

	EDataColumnType GetColumnType(const std::string& text);

public:
	Datatable* ReadFile(const char* filename) override;
};