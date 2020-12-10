#pragma once

#include "CodeClass.h"
#include "CodeEnum.h"
#include "CodeFunction.h"
#include "CodeProject.h"
#include "Runtime/Debug/Debug.h"

class CodeOStream
{
public:
	CodeOStream() {};

	virtual ~CodeOStream() {};

	virtual void Open(const std::string& filepath) = 0;

	virtual bool IsOpen() const = 0;

	virtual void Close() = 0;

	virtual CodeOStream& operator<<(const std::string& str) = 0;

	virtual CodeOStream& operator<<(const DebugConstant& stream) = 0;

	virtual CodeOStream& operator<<(const CodeClass& codeClass) = 0;

	virtual CodeOStream& operator<<(const CodeEnum& codeEnum) = 0;
	
	virtual CodeOStream& operator<<(const CodeFunction& codeFunction) = 0;
};