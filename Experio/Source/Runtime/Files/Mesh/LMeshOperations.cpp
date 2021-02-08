#include "LMeshOperations.h"
#include "glm/glm.hpp"
#include <limits>
#include "../../Debug/Debug.h"
#include <vector>
#include <map>
#include <string>

void LMeshOperations::CalculateBiTangents(
	VertexBuffer& verticies, VertexBuffer& uvs, VertexBuffer& normals, 
	VertexBuffer& outTangents, VertexBuffer& outBitangents
)
{
	unsigned int vertexCount = verticies.GetCount() / 3;

	glm::vec3* vertexArray = (glm::vec3*)verticies.GetDataAsFloatArray();
	glm::vec2* uvArray = (glm::vec2*)verticies.GetDataAsFloatArray();

	glm::vec3* tangentData = new glm::vec3[vertexCount];
	glm::vec3* bitangentData = new glm::vec3[vertexCount];

	int tangents = 0;

	for(int i = 0; i < vertexCount; i += 3)
	{
		glm::vec3 v0, v1, v2;
		v0 = vertexArray[i];
		v1 = vertexArray[i + 1];
		v2 = vertexArray[i + 2];

		glm::vec2 uv0 = uvArray[i];
		glm::vec2 uv1 = uvArray[i + 1];
		glm::vec2 uv2 = uvArray[i + 2];

		glm::vec3 deltaPos[2] = { v1 - v0, v2 - v0 };
		glm::vec2 deltaUV[2] = { uv2 - uv1, uv2 - uv0 };

		float r = 1.0f / (deltaUV[0].x * deltaUV[1].y - deltaUV[0].y * deltaUV[1].x);
		glm::vec3 tangent = (deltaPos[0] * deltaUV[1].y - deltaPos[1] * deltaUV[0].y) * r;
		glm::vec3 bitangent = (deltaPos[1] * deltaUV[1].x - deltaPos[0] * deltaUV[1].x) * r;

		tangentData[i] = tangent;
		tangents++;
		tangentData[i + 1] = tangent;
		tangents++;
		tangentData[i + 2] = tangent;
		tangents++;

		bitangentData[i] = bitangent;
		bitangentData[i + 1] = bitangent;
		bitangentData[i + 2] = bitangent;
	}

	outTangents.SetData(tangentData, vertexCount * sizeof(glm::vec3), EDataType::FLOAT);
	outBitangents.SetData(bitangentData, vertexCount * sizeof(glm::vec3), EDataType::FLOAT);
}

IndexBuffer* LMeshOperations::IndexMesh(MeshData & data)
{
	unsigned int vertexCount = data.verticies->GetCount() / 3;

	glm::vec3* vertices = (glm::vec3*)data.verticies->GetDataAsFloatArray();
	glm::vec2* uvs = (glm::vec2*)data.uv->GetDataAsFloatArray();
	glm::vec3* normals = (glm::vec3*)data.normals->GetDataAsFloatArray();
	glm::vec3* tangents = (glm::vec3*)data.normals->GetDataAsFloatArray();
	glm::vec3* bitangents = (glm::vec3*)data.normals->GetDataAsFloatArray();

	std::vector<unsigned int> outIndicies;

	std::vector<glm::vec3> outVertices;
	std::vector<glm::vec2> outUVs;
	std::vector<glm::vec3> outNormals;
	std::vector<glm::vec3> outTangents;
	std::vector<glm::vec3> outBitangents;

	for (int i = 0; i < vertexCount; i++)
	{
		unsigned int index = -1;

		for (int j = 0; j < outVertices.size(); j++)
		{
			if (vertices[i] == outVertices[j] &&
				uvs[i] == outUVs[j] &&
				normals[i] == outNormals[j])
			{
				index = j;
				break;
			}
		}
		
		if (index == -1)
		{
			// NOT FOUND
			outVertices.push_back(vertices[i]);
			outUVs.push_back(uvs[i]);
			outNormals.push_back(normals[i]);
			outTangents.push_back(tangents[i]);
			outBitangents.push_back(bitangents[i]);
			outIndicies.push_back((unsigned int)outVertices.size() - 1);
		}
		else
		{
			// FOUND
			outIndicies.push_back(index);
			outTangents[index] += tangents[i];
			outBitangents[index] += bitangents[i];
		}
	}

	unsigned int newVertexCount = outVertices.size();

	glm::vec3* newVertices = new glm::vec3[newVertexCount];
	glm::vec2* newUVs = new glm::vec2[newVertexCount];
	glm::vec3* newNormals = new glm::vec3[newVertexCount];
	glm::vec3* newTangents = new glm::vec3[newVertexCount];
	glm::vec3* newBitangents = new glm::vec3[newVertexCount];

	for (unsigned int i = 0; i < newVertexCount; i++)
	{
		newVertices[i] = outVertices[i];
		newUVs[i] = outUVs[i];
		newNormals[i] = outNormals[i];
		newBitangents[i] = outBitangents[i];
		newTangents[i] = outTangents[i];
	}

	data.verticies->SetData(newVertices, newVertexCount * sizeof(glm::vec3));
	data.uv->SetData(newUVs, newVertexCount * sizeof(glm::vec2));
	data.normals->SetData(newNormals, newVertexCount * sizeof(glm::vec3));
	data.bitangents->SetData(newBitangents, newVertexCount * sizeof(glm::vec3));
	data.tangents->SetData(newTangents, newVertexCount * sizeof(glm::vec3));

	unsigned int* newIndices = new unsigned int[outIndicies.size()];
	for (int i = 0; i < outIndicies.size(); i++)
	{
		newIndices[i] = outIndicies[i];
	}

	return new IndexBuffer(newIndices, outIndicies.size());
}

size_t LMeshOperations::SizeOfMesh(const MeshData & data)
{
	return data.verticies->GetSize() + data.uv->GetSize() + data.normals->GetSize()
		+ data.bitangents->GetSize() + data.tangents->GetSize() + data.indexBuffer->GetSize();
}

uint8_t LMeshOperations::GetIndexType(uint32_t numVerticies)
{
	if (numVerticies < 256)
	{
		return 1;
	}
	if (numVerticies < 65535)
	{
		return 2;
	}
	return 4;
}
