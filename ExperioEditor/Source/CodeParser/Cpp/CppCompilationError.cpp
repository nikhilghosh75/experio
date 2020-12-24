#include "CppCompilationError.h"
#include "Runtime/Containers/LString.h"
#include <sstream>

CppCompilationError::CppCompilationError()
{
	this->errorCode = 0;
	this->errorStr = "";
	this->errorType = ECppErrorType::Fatal;
	this->filepath = "";
	this->language = ECodingLanguage::CPlusPlus;
	this->lineNumber = 0;
}

CppCompilationError::CppCompilationError(const std::string & str)
{
	this->language = ECodingLanguage::CPlusPlus;
	MakeFromString(str);
}

std::string CppCompilationError::GetErrorExplanation() const
{
	return this->errorStr;
}

std::string CppCompilationError::GetErrorLink() const
{
	std::stringstream ss;
	switch (this->errorType)
	{
	case ECppErrorType::Fatal:
		ss << "https://docs.microsoft.com/en-us/cpp/error-messages/compiler-errors-1/fatal-error-" 
			<< this->errorCode << "?view=msvc-160";
		break;
	}
	return ss.str();
}

void CppCompilationError::MakeFromString(const std::string & str)
{
	size_t indexOfFirstNumber = LString::FindFirstOfChars(str, { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' });
	this->errorCode = LString::StringToUInt(str.substr(indexOfFirstNumber, 4));
	this->errorStr = str.substr(indexOfFirstNumber + 6);
	
	if (LString::FindFirstOfChar(str, 'C') < indexOfFirstNumber)
	{
		if (errorCode < 2000)
		{
			this->errorType = ECppErrorType::Fatal;
		}
		else
		{
			this->errorType = ECppErrorType::Compile;
		}
	}
	else if (LString::FindFirstOfChar(str, 'L') < indexOfFirstNumber)
	{
		this->errorType = ECppErrorType::Linker;
	}
}
