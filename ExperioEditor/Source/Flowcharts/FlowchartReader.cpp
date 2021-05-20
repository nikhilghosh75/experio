#include "FlowchartReader.h"
#include "Runtime/Files/LFileOperations.h"
#include <fstream>

Flowchart FlowchartReader::ReadFlowchart(const std::string& filepath)
{
    Flowchart flowchart;

    if (!LFileOperations::DoesFileHaveExtension(filepath, "pbflow"))
        return flowchart;

    std::ifstream inFile(filepath, std::ios::binary);

    ReadFlowchartHeader(inFile, flowchart);
    std::vector<std::string> nameTable = ReadFlowchartNameTable(inFile);
    ReadFlowchartNodes(inFile, flowchart, nameTable);

    return flowchart;
}

void FlowchartReader::ReadFlowchartHeader(std::ifstream& inFile, Flowchart& flowchart)
{
    char checksum[12];
    inFile.read(checksum, 12);

    char header[8];
    inFile.read(header, 8);

    unsigned int numNodes = *(unsigned int*)&header[0];
    unsigned int numTransitions = *(unsigned int*)&header[4];

    flowchart.nodes.resize(numNodes);
    flowchart.transitions.resize(numTransitions);
}

std::vector<std::string> FlowchartReader::ReadFlowchartNameTable(std::ifstream& inFile)
{
    std::vector<std::string> nameTable;
    
    char header[8];
    inFile.read(header, 8);

    unsigned int numNames = *(unsigned int*)&header[0];
    nameTable.reserve(numNames);

    char nameHeader[4];
    char name[64];
    std::memset(name, '\0', 64);

    for (unsigned int i = 0; i < numNames; i++)
    {
        inFile.read(nameHeader, 4);
        unsigned int nameLength = *(unsigned int*)&nameHeader[0];

        std::memset(name, '\0', 64);
        inFile.read(name, nameLength);

        nameTable.emplace_back(name);
    }

    return nameTable;
}

void FlowchartReader::ReadFlowchartNodes(std::ifstream& inFile, Flowchart& flowchart, const std::vector<std::string>& nameTable)
{
    unsigned int numNodes = flowchart.nodes.size();

    char node[36];

    for (unsigned int i = 0; i < numNodes; i++)
    {
        inFile.read(node, 36);

        FlowchartNode& currentNode = flowchart.nodes[i];
        currentNode.color = *(FColor*)&node[0];
        currentNode.position = *(FVector2*)&node[16];
        currentNode.size = *(FVector2*)&node[24];
        uint16_t nameIndex = *(uint16_t*)&node[32];
        currentNode.shape = *(EFlowchartNodeShape*)&node[34];

        currentNode.name = nameTable[nameIndex];
    }
}
