#include "OBJReader.h"
#include "glm/glm.hpp"
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include "../../Debug/GDebug.h"
#include "../../Debug/TempProfiler.h"
#include "../../Containers/LString.h"

MeshData * OBJReader::ReadFile(const char * fileName)
{
	TempProfiler profiler("Reading OBJ");

	std::vector<unsigned int> vertexIndicies;
	std::vector<unsigned int> uvIndicies;
	std::vector<unsigned int> normalIndicies;

	std::vector<glm::vec3> tempVertices;
	std::vector<glm::vec2> tempUVs;
	std::vector<glm::vec3> tempNormals;

	ifstream objFile(fileName);
	if (objFile.fail())
	{
		GDebug::LogError("OBJ Reader " + (std::string)fileName + " cannot be loaded");
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
					GDebug::LogError((std::string)fileName + " is not properly formatted");
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

	float* vertexData = new float[vertexIndicies.size() * 3];
	for (int i = 0; i < vertexIndicies.size(); i++)
	{
		glm::vec3 currentVertex = tempVertices[vertexIndicies[i] - 1];
		vertexData[i * 3] = currentVertex.x;
		vertexData[i * 3 + 1] = currentVertex.y;
		vertexData[i * 3 + 2] = currentVertex.z;
	}

	float* uvData = new float[uvIndicies.size() * 2];
	for (int i = 0; i < uvIndicies.size(); i++)
	{
		glm::vec2 currentUV = tempUVs[uvIndicies[i] - 1];
		uvData[i * 2] = currentUV.x;
		uvData[i * 2 + 1] = currentUV.y;
	}

	float* normalData = new float[normalIndicies.size() * 3];
	for (int i = 0; i < normalIndicies.size(); i++)
	{
		glm::vec3 currentNormal = tempNormals[normalIndicies[i] - 1];
		normalData[i * 3] = currentNormal.x;
		normalData[i * 3 + 1] = currentNormal.y;
		normalData[i * 3 + 2] = currentNormal.z;
	}

	MeshData* meshData = new MeshData();
	meshData->fileType = EMeshFileType::OBJ;
	meshData->verticies = new VertexBuffer(vertexData, vertexIndicies.size() * 3 * sizeof(float));
	meshData->uv = new VertexBuffer(uvData, uvIndicies.size() * 2 * sizeof(float));
	meshData->normals = new VertexBuffer(normalData, normalIndicies.size() * 3 * sizeof(float));

	return meshData;
}
