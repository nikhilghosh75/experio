#pragma once

#include "../CompilationError.h"

enum class ECppErrorType
{
	Fatal,
	Compile,
	Linker,
	Math,
	ExpressionEvaluator,
	Warning,
	None
};

struct CppCompilationError : public CompilationError
{
	ECppErrorType errorType;

	CppCompilationError();
	CppCompilationError(const std::string& str);

	virtual std::string GetErrorExplanation() const override;

	virtual std::string GetErrorLink() const override;

	bool IsValid() const;

	bool IsError() const;
	bool IsWarning() const;

private:
	bool MakeFromString(const std::string& str);
};