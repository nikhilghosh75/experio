#pragma once
#include <type_traits>
#include <string>

class TFileData
{
public:
	TFileData()
	{
		originalFileName = "";
	}

	TFileData(const char* filename)
	{
		originalFileName = filename;
	}

private:
	std::string originalFileName;
};

template <class T>
class FileReader
{
	// static_assert(std::is_base_of<TFileData, T>::value);

public:
	FileReader() {};
	FileReader(const char* fileName);

	virtual T* ReadFile(const char* fileName) { return nullptr;  };
};