#pragma once

#include "../CodeStream.h"
#include <fstream>

enum class ECppFileType
{
	None,
	H,
	Cpp
};

struct CppCodeOStream : public CodeOStream
{
private:
	std::ofstream outFile;

	ECppFileType fileType;

public:
	CppCodeOStream();

	CppCodeOStream(const std::string& filepath);

	virtual ~CppCodeOStream() override;

	virtual void Open(const std::string& filepath) override;

	virtual bool IsOpen() const override;

	virtual void Close() override;

	virtual CodeOStream& operator<<(const std::string& str) override;

	virtual CodeOStream& operator<<(const DebugConstant& stream) override;

	virtual CodeOStream& operator<<(const CodeClass& codeClass) override;

	virtual CodeOStream& operator<<(const CodeEnum& codeEnum) override;

	virtual CodeOStream& operator<<(const CodeFunction& codeFunction) override;

private:
	static ECppFileType GetFileTypeFromString(const std::string& str);

	void StreamClassToH(const CodeClass& codeClass);

	void StreamClassToCpp(const CodeClass& codeClass);

	void StreamFunctionToH(const CodeFunction& codeFunction);

	void StreamFunctionToCpp(const CodeFunction& codeFunction);
};