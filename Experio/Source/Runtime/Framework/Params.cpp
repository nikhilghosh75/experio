#include "Params.h"
#include "Project.h"

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

FCurve ParseCurve(std::string str)
{
	Debug::LogError("THIS FUNCTION IS NOT COMPLETE YET");
	return FCurve();
}

AudioClip ParseAudio(std::string str)
{
	Debug::LogError("THIS FUNCTION IS NOT COMPLETE YET");
	return AudioClip();
}

Datatable ParseData(std::string str)
{
	Debug::LogError("THIS FUNCTION IS NOT COMPLETE YET");
	return Datatable();
}

FontData* ParseFont(std::string str)
{
	std::string filePath = LFileOperations::GetFullFilePath(str);
	return FontReader::ReadFile(filePath.c_str());
}

Material* ParseMaterial(std::string str)
{
	std::string filePath = LFileOperations::GetFullFilePath(str);
	return Project::materialManager->LoadMaterialFromFile(filePath);
}

MeshData* ParseMesh(std::string str)
{
	std::string filePath = LFileOperations::GetFullFilePath(str);
	return MeshReader::ReadFile(filePath.c_str());
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

Texture* ParseTexture(std::string str)
{
	std::string filePath = LFileOperations::GetFullFilePath(str);
	return new Texture(ImageReader::ReadFile(filePath.c_str()));
}