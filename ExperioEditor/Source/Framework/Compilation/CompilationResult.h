#pragma once
#include <vector>
#include "../../CodeParser/Cpp/CppCompilationError.h"

struct FCompilationResult
{
	std::vector<CppCompilationError> errors;
	bool succeeded;

	FCompilationResult() = default;

	FCompilationResult(std::vector<CppCompilationError> errors, bool succeeded)
	{
		this->errors = errors;
		this->succeeded = succeeded;
	}
};