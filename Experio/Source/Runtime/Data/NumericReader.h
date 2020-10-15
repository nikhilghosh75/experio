#pragma once
#include "NumericData.h"
#include <string>
#include <fstream>

class NumericReader
{
	static void ReadSingleData(void* dataLocation, EDataType type, std::ifstream& stream);

public:
	static NumericData* ReadData(std::string filename);
};