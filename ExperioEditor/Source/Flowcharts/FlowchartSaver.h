#pragma once
#include "Flowchart.h"

class FlowchartSaver
{
public:
	static void SaveFlowchart(const Flowchart& flowchart, const std::string& filepath);

private:
	static std::vector<std::string> GenerateNameTable(const Flowchart& flowchart, std::vector<size_t>& nameIndices);

	static void SaveHeader(const Flowchart& flowchart, std::ofstream& outFile);

	static void SaveNameTable(const std::vector<std::string>& nameTable, std::ofstream& outFile);

	static unsigned int NameTableLength(const std::vector<std::string>& nameTable);

	static void SaveNodes(const Flowchart& flowchart, std::vector<size_t> nameIndices, std::ofstream& outFile);
};