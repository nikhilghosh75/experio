#pragma once
#include "Datatable.h"
#include <string>

class CSVWriter
{
public:
	static void SaveToCSV(Datatable& datatable, const std::string& filepath);
};