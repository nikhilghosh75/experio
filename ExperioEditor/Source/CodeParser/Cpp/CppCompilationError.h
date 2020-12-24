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

	CppCompilationError();
	CppCompilationError(const std::string& str);

	virtual std::string GetErrorExplanation() const override;

	virtual std::string GetErrorLink() const override;

private:
	void MakeFromString(const std::string& str);
};