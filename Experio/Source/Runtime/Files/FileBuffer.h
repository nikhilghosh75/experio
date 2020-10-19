#pragma once
#include <string>

class FileBuffer
{
	char* data;
	size_t size;
public:
	FileBuffer()
	{
		this->data = nullptr;
		this->size = 0;
	}

	FileBuffer(char* data, size_t size)
	{
		this->data = new char[size];
		this->size = size;
		memcpy(this->data, data, this->size);
	}

	FileBuffer(const FileBuffer& filebuffer)
	{
		this->data = new char[filebuffer.size];
		this->size = filebuffer.size;

		memcpy(this->data, filebuffer.data, this->size);
	}

	~FileBuffer()
	{
		delete this->data;
	}

	char* Data() const { return this->data; }
	size_t Size() const { return this->size; }

	char& operator[](size_t index) { return data[index]; }
	const char& operator[](size_t index) const { return data[index]; }
};