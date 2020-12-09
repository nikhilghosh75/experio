#pragma once

#include "../CompilationError.h"

enum class ECppErrorType
{
	Fatal,
	Compile,
	Linker,
	Math,
	ExpressionEvaluator
};

struct CppCompilationError : public CompilationError
{
	ECppErrorType errorType;

	virtual std::string GetErrorExplanation() const override;

	virtual std::string GetErrorLink() const override;

private:
	std::string GetCompilerErrorExplanation() const;
};