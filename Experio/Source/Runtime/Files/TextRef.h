#pragma once
#include <string>

class TextRef
{
public:
	TextRef();

	TextRef(unsigned int id);

	TextRef(const std::string filepath);

	std::string filepath;

	size_t FileSize() const;
};