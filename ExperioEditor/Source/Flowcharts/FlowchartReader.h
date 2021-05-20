#pragma once

#include "Flowchart.h"

class FlowchartReader
{
public:
	static Flowchart ReadFlowchart(const std::string& filepath);

private:
	static void ReadFlowchartHeader(std::ifstream& inFile, Flowchart& flowchart);

	static std::vector<std::string> ReadFlowchartNameTable(std::ifstream& inFile);

	static void ReadFlowchartNodes(std::ifstream& inFile, Flowchart& flowchart, const std::vector<std::string>& nameTable);
};