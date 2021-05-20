#include "FlowchartSaver.h"
#include "Runtime/Containers/TSet.h"
#include <fstream>

void FlowchartSaver::SaveFlowchart(const Flowchart& flowchart, const std::string& filepath)
{
	std::vector<size_t> nameIndices;
	std::vector<std::string> names = GenerateNameTable(flowchart, nameIndices);

	std::ofstream outFile(filepath, std::ios::binary);
	SaveHeader(flowchart, outFile);
	SaveNameTable(names, outFile);
	SaveNodes(flowchart, nameIndices, outFile);
}

std::vector<std::string> FlowchartSaver::GenerateNameTable(const Flowchart& flowchart, std::vector<size_t>& nameIndices)
{
	std::vector<std::string> names;

	for (size_t i = 0; i < flowchart.nodes.size(); i++)
	{
		bool found = false;
		size_t foundIndex = 0;
		for (size_t j = 0; j < names.size(); j++)
		{
			if (names[j] == flowchart.nodes[i].name)
			{
				found = true;
				foundIndex = j;
				break;
			}
		}

		if (found)
		{
			nameIndices.push_back(foundIndex);
		}
		else
		{
			nameIndices.push_back(names.size());
			names.push_back(flowchart.nodes[i].name);
		}
	}

	return names;
}

void FlowchartSaver::SaveHeader(const Flowchart& flowchart, std::ofstream& outFile)
{
	unsigned int numNodes = flowchart.nodes.size();
	unsigned int numTransitions = flowchart.transitions.size();

	outFile.write("PB_FLOWCHART", 12);
	outFile.write((char*)&numNodes, 4);
	outFile.write((char*)&numTransitions, 4);
}

void FlowchartSaver::SaveNameTable(const std::vector<std::string>& nameTable, std::ofstream& outFile)
{
	unsigned int numNames = nameTable.size();
	unsigned int nameTableLength = NameTableLength(nameTable);

	outFile.write((char*)&numNames, 4);
	outFile.write((char*)&numNames, 4);
	
	for (unsigned int i = 0; i < nameTable.size(); i++)
	{
		unsigned int nameLength = nameTable[i].size();
		outFile.write((char*)&nameLength, 4);
		outFile.write(nameTable[i].data(), nameLength);
	}
}

unsigned int FlowchartSaver::NameTableLength(const std::vector<std::string>& nameTable)
{
	// Each name must be 4 tables
	unsigned int nameTableLength = nameTable.size() * 4;

	for (size_t i = 0; i < nameTable.size(); i++)
	{
		nameTableLength += nameTable[i].size();
	}

	return nameTableLength;
}

void FlowchartSaver::SaveNodes(const Flowchart& flowchart, std::vector<size_t> nameIndices, std::ofstream& outFile)
{
	for (size_t i = 0; i < flowchart.nodes.size(); i++)
	{
		FColor color = flowchart.nodes[i].color;
		FVector2 position = flowchart.nodes[i].position;
		FVector2 size = flowchart.nodes[i].size;
		uint16_t nameIndex = nameIndices[i];
		uint8_t shape = (uint8_t)flowchart.nodes[i].shape;

		outFile.write((char*)&color, 16);
		outFile.write((char*)&position, 8);
		outFile.write((char*)&size, 8);
		outFile.write((char*)&nameIndex, 2);
		outFile.write((char*)&shape, 1);
		outFile.write("a", 1);
	}
}