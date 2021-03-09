#include "OBJReader.h"
#include "glm/glm.hpp"
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include "../../Debug/Debug.h"
#include "../../Debug/Profiler.h"
#include "../../Containers/LString.h"
#include "LMeshOperations.h"

MeshData * OBJReader::ReadFile(const char * fileName)
{
	PROFILE_SCOPE_CATEGORY("Read OBJ", EProfilerCategory::Files);

	std::vector<unsigned int> vertexIndicies;
	std::vector<unsigned int> uvIndicies;
	std::vector<unsigned int> normalIndicies;

	std::vector<glm::vec3> tempVertices;
	std::vector<glm::vec2> tempUVs;
	std::vector<glm::vec3> tempNormals;

	std::ifstream objFile(fileName);
	if (objFile.fail())
	{
		Debug::LogError("OBJ Reader " + (std::string)fileName + " cannot be loaded");
		Debug::LogError(strerror(errno));
		objFile.close();
		return nullptr;
	}

	std::string word;
	while (objFile >> word)
	{
		if (word == "v")
		{
			glm::vec3 vertex;
			objFile >> vertex.x;
			objFile >> vertex.y;
			objFile >> vertex.z;
			tempVertices.push_back(vertex);
		}
		else if (word == "vt")
		{
			glm::vec2 uv;
			objFile >> uv.x;
			objFile >> uv.y;
			tempUVs.push_back(uv);
		}
		else if (word == "vn")
		{
			glm::vec3 normal;
			objFile >> normal.x;
			objFile >> normal.y;
			objFile >> normal.z;
			tempNormals.push_back(normal);
		}
		else if (word == "f")
		{
			std::string vertexes[3];
			// Assumes file is formatted as "f 1/2/3 4/5/6 7/8/9"
			objFile >> vertexes[0] >> vertexes[1] >> vertexes[2];
			for (int i = 0; i < 3; i++)
			{
				std::vector<std::string> seperatedIndicies = LString::SeperateStringByChar(vertexes[i], '/');

				if (seperatedIndicies.size() != 3)
				{
					Debug::LogError((std::string)fileName + " is not properly formatted");
					objFile.close();
					return nullptr;
				}

				vertexIndicies.push_back(std::stoi(seperatedIndicies[0]));
				uvIndicies.push_back(std::stoi(seperatedIndicies[1]));
				normalIndicies.push_back(std::stoi(seperatedIndicies[2]));
			}
		}
		else
		{
			getline(objFile, word);
		}
	}

	// Debug::Log("Read Entire File");
	objFile.close();

	glm::vec3* vertexData = new glm::vec3[vertexIndicies.size()];
	for (int i = 0; i < vertexIndicies.size(); i++)
	{
		vertexData[i] = tempVertices[vertexIndicies[i] - 1];
	}

	glm::vec2* uvData = new glm::vec2[uvIndicies.size()];
	for (int i = 0; i < uvIndicies.size(); i++)
	{
		uvData[i] = tempUVs[uvIndicies[i] - 1];
	}

	glm::vec3* normalData = new glm::vec3[normalIndicies.size()];
	for (size_t i = 0; i < normalIndicies.size(); i++)
	{
		normalData[i] = tempNormals[normalIndicies[i] - 1];
	}

	MeshData* meshData = new MeshData();
	meshData->verticies = new VertexBuffer(vertexData, vertexIndicies.size() * sizeof(glm::vec3), EDataType::FLOAT);
	meshData->uv = new VertexBuffer(uvData, uvIndicies.size() * sizeof(glm::vec2), EDataType::FLOAT);
	meshData->normals = new VertexBuffer(normalData, normalIndicies.size() * sizeof(glm::vec3), EDataType::FLOAT);

	VertexBuffer* tangentBuffer = new VertexBuffer(); 
	VertexBuffer* bitangentBuffer = new VertexBuffer();
	LMeshOperations::CalculateBiTangents(*meshData->verticies, *meshData->uv, *meshData->normals, *tangentBuffer, *bitangentBuffer);
	meshData->tangents = tangentBuffer;
	meshData->bitangents = bitangentBuffer;

	// Debug::Log("Read Tangents and Bitangents");

	meshData->indexBuffer = LMeshOperations::IndexMesh(*meshData);
	//meshData->isIndexed = false;
	meshData->isIndexed = true;
	return meshData;
}

size_t OBJReader::SerializedSizeOf(const char * filename)
{
	std::ifstream objFile(filename);

	size_t numVerticies = 0;
	size_t numIndicies = 0;

	std::string word;
	while (objFile >> word)
	{
		if (word == "v")
		{
			numVerticies++;
		}
		else if (word == "f")
		{
			numIndicies++;
		}
		getline(objFile, word);
	}

	uint8_t indexType = LMeshOperations::GetIndexType(numVerticies);
	size_t headerSize = 20;
	size_t vertexBufferSize = numVerticies * 14 * 4;
	size_t indexBufferSize = numIndicies * indexType;

	return headerSize + vertexBufferSize + indexBufferSize;
}
