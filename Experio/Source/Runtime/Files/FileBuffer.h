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

	// Start inclusive, end exclusive
	std::string Substr(size_t start, size_t end) const
	{
		if (end == std::string::npos)
			end = this->size;

		std::string str;
		str.reserve(end - start);
		
		for (size_t i = start; i < end; i++)
		{
			str.append({ this->data[i] });
		}
		return str;
	}

	bool CompareSubstr(const std::string& str, size_t offset = 0) const
	{
		for (size_t i = 0; i < str.size(); i++)
		{
			if (str[i] != (*this)[i + offset])
				return false;
		}
		return true;
	}

	size_t Find(char c, size_t offset = 0) const
	{
		for (size_t i = offset; i < size; i++)
		{
			if (data[i] == c)
				return i;
		}
		return std::string::npos;
	}

	size_t Find(const std::string& substr, size_t offset = 0) const
	{
		for (size_t i = offset; i < size; i++)
		{
			bool compare = true;
			for (size_t j = 0; j < substr.size(); j++)
			{
				if (data[i + j] != substr[j])
				{
					compare = false; break;
				}
			}
			if (compare)
				return i;
		}
		return std::string::npos;
	}

	size_t ReverseFind(char c, size_t offset = 0) const
	{
		if(offset == 0)
			offset = size - 1;

		for (size_t i = offset; i < size; i--)
		{
			if (data[i] == c)
				return i;
		}

		return std::string::npos;
	}

	size_t ReverseFind(const std::string& substr, size_t offset = 0) const
	{
		if (offset == 0 || offset > size - substr.size())
			offset = size - 1 - substr.size();

		for (size_t i = offset; i < size; i--)
		{
			bool compare = true;
			for (size_t j = 0; j < substr.size(); j++)
			{
				if (data[i + j] != substr[j])
					compare = false; break;
			}
			if (compare)
				return i;
		}

		return std::string::npos;
	}

	size_t NumOfCharacter(char c, size_t offset = 0) const
	{
		size_t count = 0;

		for (size_t i = offset; i < size; i++)
		{
			if (data[i] == c)
			{
				count++;
			}
		}

		return count;
	}
};