#pragma once
#include <stdint.h>
#include "../Rendering/VertexBuffer.h"

// Intended to store only numeric data

class NumericData
{
	EDataType dataType;
	uint8_t size; // 1, 2, 3, 4
	unsigned int numElements; // num of elements of size 
	// (for instance, if size was 2 and there were 40 floats, numElements would be 20).
	void* data;

public:
	NumericData();
	NumericData(EDataType dataType);
	NumericData(EDataType dataType, uint8_t size, unsigned int numElements);
	NumericData(EDataType dataType, uint8_t size, unsigned int numElements, void* data);

	void SetData(void* newData);
	void SetData(void* newData, size_t sizeOfData);

	unsigned int Count();
	unsigned int Size(); // bytes

	uint8_t GetElementSize();
	unsigned int GetNumElements();
	EDataType GetDataType();
	void* GetData();
};