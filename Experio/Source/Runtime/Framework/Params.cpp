#include "Params.h"
#include "Project.h"
#include "../Files/Data/DataReader.h"

bool ParseBool(std::string str)
{
	return str.find("true") != std::string::npos;
}

uint8_t ParseByte(std::string str)
{
	return (uint8_t)std::stoi(str);
}

int16_t ParseShort(std::string str)
{
	return (int16_t)std::stoi(str);
}

uint16_t ParseUShort(std::string str)
{
	return (uint16_t)std::stoi(str);
}

float ParseFloat(std::string str)
{
	return std::stof(str);
}

int ParseInt(std::string str)
{
	return std::stoi(str);
}

unsigned int ParseUInt(std::string str)
{
	return (unsigned int)std::stoull(str);
}

double ParseDouble(std::string str)
{
	return std::stod(str);
}

long long ParseLongLong(std::string str)
{
	return (long long)std::stoull(str);
}

unsigned long long ParseULongLong(std::string str)
{
	return std::stoull(str);
}

FVector2 ParseVector2(std::string str)
{
	float coordinates[2];
	int currentIndex = 0, lastSpace = 0;

	for (int i = 1; i < str.size(); i++)
	{
		if (str[i] == ' ')
		{
			coordinates[currentIndex] = LString::StringToFloat(str.substr(lastSpace + 1, i));
			currentIndex++;
			lastSpace = i;
		}
	}

	if (currentIndex < 2)
	{
		coordinates[currentIndex] = LString::StringToFloat(str.substr(lastSpace + 1));
	}

	return FVector2(coordinates[0], coordinates[1]);
}

FVector3 ParseVector3(std::string str)
{
	float coordinates[3];
	int currentIndex = 0, lastSpace = 0;

	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == ' ')
		{
			coordinates[currentIndex] = LString::StringToFloat(str.substr(lastSpace + 1, i));
			currentIndex++;
			lastSpace = i;
		}
	}

	if (currentIndex < 3)
	{
		coordinates[currentIndex] = LString::StringToFloat(str.substr(lastSpace + 1));
	}

	return FVector3(coordinates[0], coordinates[1], coordinates[2]);
}

FVector4 ParseVector4(std::string str)
{
	float coordinates[4];
	int currentIndex = 0, lastSpace = 0;

	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == ' ')
		{
			coordinates[currentIndex] = LString::StringToFloat(str.substr(lastSpace + 1, i));
			currentIndex++;
			lastSpace = i;
		}
	}

	if (currentIndex < 4)
	{
		coordinates[currentIndex] = LString::StringToFloat(str.substr(lastSpace + 1));
	}

	return FVector4(coordinates[0], coordinates[1], coordinates[2], coordinates[3]);
}

FColor ParseColor(std::string str)
{
	float coordinates[4];
	int currentIndex = 0, lastSpace = 0;

	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == ' ')
		{
			coordinates[currentIndex] = LString::StringToFloat(str.substr(lastSpace + 1, i));
			currentIndex++;
			lastSpace = i;
		}
	}

	if (currentIndex < 4)
	{
		coordinates[currentIndex] = LString::StringToFloat(str.substr(lastSpace + 1));
	}

	return FColor(coordinates[0], coordinates[1], coordinates[2], coordinates[3]);
}

FQuaternion ParseQuaternion(std::string str)
{
	float coordinates[4];
	int currentIndex = 0, lastSpace = 0;

	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == ' ')
		{
			coordinates[currentIndex] = LString::StringToFloat(str.substr(lastSpace + 1, i));
			currentIndex++;
			lastSpace = i;
		}
	}

	if (currentIndex < 4)
	{
		coordinates[currentIndex] = LString::StringToFloat(str.substr(lastSpace + 1));
	}

	return FQuaternion(coordinates[0], coordinates[1], coordinates[2], coordinates[3]);
}

FRect ParseRect(std::string str)
{
	float coordinates[4];
	int currentIndex = 0, lastSpace = 0;

	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == ' ')
		{
			coordinates[currentIndex] = LString::StringToFloat(str.substr(lastSpace + 1, i));
			currentIndex++;
			lastSpace = i;
		}
	}

	if (currentIndex < 4)
	{
		coordinates[currentIndex] = LString::StringToFloat(str.substr(lastSpace + 1));
	}

	return FRect(coordinates[0], coordinates[1], coordinates[2], coordinates[3]);
}

FBox ParseBox(std::string str)
{
	float coordinates[6];
	int currentIndex = 0, lastSpace = 0;

	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == ' ')
		{
			coordinates[currentIndex] = LString::StringToFloat(str.substr(lastSpace + 1, i));
			currentIndex++;
			lastSpace = i;
		}
	}

	if (currentIndex < 6)
	{
		coordinates[currentIndex] = LString::StringToFloat(str.substr(lastSpace + 1));
	}
	
	return FBox(coordinates[0], coordinates[1], coordinates[2], coordinates[3], coordinates[4], coordinates[5]);
}

FCurve ParseCurve(std::string str)
{
	Debug::LogError("THIS FUNCTION IS NOT COMPLETE YET");
	return FCurve();
}

FSphericalPoint ParseSphericalPoint(std::string str)
{
	float coordinates[3];
	int currentIndex = 0, lastSpace = 0;

	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == ' ')
		{
			coordinates[currentIndex] = LString::StringToFloat(str.substr(lastSpace + 1, i));
			currentIndex++;
			lastSpace = i;
		}
	}

	if (currentIndex < 3)
	{
		coordinates[currentIndex] = LString::StringToFloat(str.substr(lastSpace + 1));
	}

	return FSphericalPoint(coordinates[0], coordinates[1], coordinates[2]);
}

FAudioClip ParseAudio(std::string str)
{
	Debug::LogError("THIS FUNCTION IS NOT COMPLETE YET");
	return FAudioClip();
}

Datatable* ParseData(std::string str)
{
	std::string filePath = LFileOperations::GetFullFilePath(str);
	return DataReader::ReadFile(filePath.c_str());
}

FontRef ParseFont(std::string str)
{
	std::string filePath = LFileOperations::GetFullFilePath(str);
	return FontManager::LoadFont(filePath);
}

Material* ParseMaterial(std::string str)
{
	std::string filePath = LFileOperations::GetFullFilePath(str);
	return Project::materialManager->LoadMaterialFromFile(filePath);
}

MeshRef ParseMesh(std::string str)
{
	std::string filePath = LFileOperations::GetFullFilePath(str);
	return MeshManager::LoadMesh(filePath);
}

Shader* ParseShader(std::string str)
{
	std::vector<std::string> filePaths = LString::SeperateStringByChar(str, ' ');

	std::vector<std::string> fullPaths;
	fullPaths.reserve(filePaths.size());

	for (int i = 0; i < filePaths.size(); i++)
	{
		fullPaths.push_back(LFileOperations::GetFullFilePath(filePaths[i]));
	}

	if (filePaths.size() == 2)
	{
		return new Shader(fullPaths[0], fullPaths[1]);
	}
	return nullptr;
}

TextureRef ParseTexture(std::string str)
{
	std::string filePath = LFileOperations::GetFullFilePath(str);
	return TextureManager::LoadTexture(filePath);
}
