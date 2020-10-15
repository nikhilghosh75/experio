#include "NumericReader.h"
#include "../Files/LFileOperations.h"
#include "../Rendering/LOpenGL.h"
#include "../Debug/Debug.h"

void NumericReader::ReadSingleData(void * dataLocation, EDataType type, std::ifstream & stream)
{
	switch (type)
	{
	case EDataType::NONE:
		return;
	case EDataType::FLOAT:
		float tempFloat;
		stream >> tempFloat;
		*(float*)dataLocation = tempFloat;
		break;
	case EDataType::INT:
		int tempInt;
		stream >> tempInt;
		*(int*)dataLocation = tempInt;
		break;
	}
}

NumericData * NumericReader::ReadData(std::string filename)
{
	if (!LFileOperations::DoesFileHaveExtension(filename, "pbnumdata"))
	{
		Debug::LogError("Loaded Scene is not a .pbnumdata file");
		return false;
	}

	std::ifstream numericFile(filename);
	if (numericFile.fail())
	{
		Debug::LogError("File " + filename + " could not be opened");
		return false;
	}

	char word[256];

	numericFile >> word;
	EDataType type = LOpenGL::StringToDataType(std::string(word));

	uint8_t size;
	numericFile >> size;

	unsigned int count;
	numericFile >> count;

	NumericData* numericData = new NumericData(type, size, count);
	void* data = malloc(numericData->Size());
	unsigned int numElements = numericData->GetNumElements();
	size_t sizeOfElement = LOpenGL::GetSizeOfType(type);
	
	for (int i = 0; i < numElements; i++)
	{
		ReadSingleData((void*)((char*)data + i * sizeOfElement), type, numericFile);
	}
	numericData->SetData(data);
	return numericData;
}
