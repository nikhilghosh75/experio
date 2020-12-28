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
	if (!MakeFromString(str))
	{
		this->errorType = ECppErrorType::None;
		this->errorCode = 0;
	}
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

bool CppCompilationError::IsValid() const
{
	return IsError() || IsWarning();
}

bool CppCompilationError::IsError() const
{
	return this->errorType == ECppErrorType::Compile || this->errorType == ECppErrorType::Fatal
		|| this->errorType == ECppErrorType::Linker;
}

bool CppCompilationError::IsWarning() const
{
	return this->errorType == ECppErrorType::Warning;
}

bool CppCompilationError::MakeFromString(const std::string & str)
{
	size_t indexOfFirstParen = LString::FindFirstOfChar(str, '(');
	if (indexOfFirstParen >= str.size()) return false;
	this->filepath = str.substr(0, indexOfFirstParen);

	size_t indexOfEndParen = LString::FindFirstOfChar(str, ')');
	if (indexOfEndParen >= str.size()) return false;
	this->lineNumber = LString::StringToUInt(str.substr(indexOfFirstParen + 1, indexOfEndParen - indexOfFirstParen - 1));

	size_t indexOfFirstNumber = LString::FindFirstOfChars(str.substr(indexOfEndParen), { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' });
	this->errorCode = LString::StringToUInt(str.substr(indexOfFirstNumber + indexOfEndParen, 4));
	this->errorStr = str.substr(indexOfFirstNumber + indexOfEndParen + 6);
	
	if (str.find("warning") != std::string::npos)
	{
		this->errorType = ECppErrorType::Warning;
	}
	else if (LString::FindFirstOfChar(str, 'C') < indexOfFirstNumber + indexOfEndParen)
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
	return true;
}
