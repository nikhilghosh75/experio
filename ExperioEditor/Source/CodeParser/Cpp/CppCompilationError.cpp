#include "CppCompilationError.h"
#include <sstream>

std::string CppCompilationError::GetErrorExplanation() const
{
	switch (this->errorType)
	{
	case ECppErrorType::Fatal:
	case ECppErrorType::Compile:
		return GetCompilerErrorExplanation();
	}
	return "";
}

std::string CppCompilationError::GetErrorLink() const
{
	std::stringstream ss;
	switch (this->errorType)
	{
	case ECppErrorType::Fatal:
		ss << "https://docs.microsoft.com/en-us/cpp/error-messages/compiler-errors-1/fatal-error-" << this->errorCode << "?view=msvc-160";
		break;
	}
	return ss.str();
}

std::string CppCompilationError::GetCompilerErrorExplanation() const
{
	switch (this->errorCode)
	{
	case 999: return "Unknowned Error";
	case 1001: return "An Internal Error has occurred in the compiler";
	case 1002: return "Compiler is out of heap space in pass 2, possibly due to a program with too many symbols or complex expressions";
	case 1003: return "Too many errors. Stopping compilation.";
	case 1004: return "Unexpected end-of-file found. You may be missing a closing brace, parenthesis, comment marker, or semicolon.";
	case 1005: return "String too big for buffer";
	case 1007: return "Command-line option contains an invalid string. Check environment variable for errors";
	case 1008: return "No input file specified. Compiler was not given a source file";
	case 1009: return "Macros nested too deeply. Compiler is limited to 256 nested macros.";
	}
	return "";
}
