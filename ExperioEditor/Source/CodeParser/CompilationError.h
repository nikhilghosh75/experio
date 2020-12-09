#pragma once

#include "CodeProject.h"

struct CompilationError
{
	uint32_t errorCode;
	ECodingLanguage language;

	uint32_t lineNumber;
	std::string filepath;

	std::string errorStr;

	virtual std::string GetErrorExplanation() const = 0;

	virtual std::string GetErrorLink() const = 0;
};