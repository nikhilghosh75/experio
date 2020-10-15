#include "NumericData.h"
#include "../Rendering/LOpenGL.h"

NumericData::NumericData()
{
	this->dataType = EDataType::NONE;
	this->size = 0;
	this->numElements = 0;
	this->data = nullptr;
}

NumericData::NumericData(EDataType dataType)
{
	this->dataType = dataType;
	this->size = 0;
	this->numElements = 0;
	this->data = nullptr;
}

NumericData::NumericData(EDataType dataType, uint8_t size, unsigned int numElements)
{
	this->dataType = dataType;
	this->size = size;
	this->numElements = numElements;
	this->data = nullptr;
}

NumericData::NumericData(EDataType dataType, uint8_t size, unsigned int numElements, void * data)
{
	this->dataType = dataType;
	this->size = size;
	this->numElements = numElements;
	this->data = data;
}

void NumericData::SetData(void * newData)
{
	this->data = newData;
}

void NumericData::SetData(void * newData, size_t sizeOfData)
{
	this->data = newData;
	this->numElements = sizeOfData / (this->numElements * LOpenGL::GetSizeOfType(dataType));
}

unsigned int NumericData::Count()
{
	return numElements * size;
}

unsigned int NumericData::Size()
{
	return numElements * size * LOpenGL::GetSizeOfType(dataType);
}

uint8_t NumericData::GetElementSize()
{
	return size;
}

unsigned int NumericData::GetNumElements()
{
	return numElements;
}

EDataType NumericData::GetDataType()
{
	return dataType;
}

void * NumericData::GetData()
{
	return data;
}
