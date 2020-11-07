#pragma once

#include "../FileReader.h"
#include "../../Data/Datatable.h"

class DataReader : FileReader<Datatable>
{
public:
	static Datatable* ReadFile(const char* filepath);
	static Datatable* ReadFile(unsigned int assetID);
};