#pragma once

#include "../../Data/Datatable.h"

class DataReader
{
public:
	static Datatable* ReadFile(const char* filepath);
	static Datatable* ReadFile(unsigned int assetID);
};