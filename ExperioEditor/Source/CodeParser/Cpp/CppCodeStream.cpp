#include "CppCodeStream.h"
#include "LCpp.h"
#include "Runtime/Files/LFileOperations.h"

CppCodeOStream::CppCodeOStream()
{
	fileType = ECppFileType::None;
}

CppCodeOStream::CppCodeOStream(const std::string & filepath)
{
	outFile.open(filepath);
	fileType = GetFileTypeFromString(filepath);

	if (fileType == ECppFileType::H)
	{
		outFile << "#pragma once" << std::endl;
	}
}

CppCodeOStream::~CppCodeOStream()
{
	Close();
}

void CppCodeOStream::Open(const std::string & filepath)
{
	outFile.open(filepath);
	fileType = GetFileTypeFromString(filepath);

	if (fileType == ECppFileType::H)
	{
		outFile << "#pragma once" << std::endl;
	}
}

bool CppCodeOStream::IsOpen() const
{
	return outFile.is_open();
}

void CppCodeOStream::Close()
{
	outFile.close();
}

CodeOStream & CppCodeOStream::operator<<(const std::string & str)
{
	outFile << str;
	return *this;
}

CodeOStream & CppCodeOStream::operator<<(const DebugConstant & constant)
{
	switch (constant.constant)
	{
	case 5807:
		outFile << std::endl; break;
	}

	return *this;
}

CodeOStream & CppCodeOStream::operator<<(const CodeClass & codeClass)
{
	switch (fileType)
	{
	case ECppFileType::Cpp:
		StreamClassToCpp(codeClass); break;
	case ECppFileType::H:
		StreamClassToH(codeClass); break;
	}
	return *this;
}

CodeOStream & CppCodeOStream::operator<<(const CodeEnum & codeEnum)
{
	outFile << "enum class " << codeEnum.name << " : " << 
		LCodeParser::EnumDataTypeToString(codeEnum.dataType, ECodingLanguage::CPlusPlus) << std::endl;
	outFile << "{" << std::endl;

	outFile << "}" << std::endl;
	return *this;
}

CodeOStream & CppCodeOStream::operator<<(const CodeFunction & codeFunction)
{
	Debug::LogError("This function is not implemented yet");
	return *this;
}

ECppFileType CppCodeOStream::GetFileTypeFromString(const std::string& str)
{
	if (LFileOperations::DoesFileHaveExtension(str, "h")) return ECppFileType::H;
	if (LFileOperations::DoesFileHaveExtension(str, "hpp")) return ECppFileType::H;
	if (LFileOperations::DoesFileHaveExtension(str, "cpp")) return ECppFileType::Cpp;

	return ECppFileType::None;
}

void CppCodeOStream::StreamClassToH(const CodeClass & codeClass)
{
	outFile << "class " << codeClass.name;

	if (codeClass.inheritance.size() != 0)
	{
		outFile << " : ";
		for (int i = 0; i < codeClass.inheritance.size() - 1; i++)
		{
			outFile << "public " << codeClass.inheritance[i] << ", ";
		}
		outFile << "public " << codeClass.inheritance[codeClass.inheritance.size() - 1];
	}

	outFile << std::endl << "{" << std::endl;

	ECodeAccessType currentAccessType = ECodeAccessType::Private;
	for (int i = 0; i < codeClass.params.size(); i++)
	{
		const CodeParam& param = codeClass.params[i];

		if (param.accessType != currentAccessType)
		{
			switch (param.accessType)
			{
			case ECodeAccessType::Private:
				outFile << "private:" << std::endl; break;
			case ECodeAccessType::Protected:
				outFile << "protected:" << std::endl; break;
			case ECodeAccessType::Public:
				outFile << "public:" << std::endl; break;
			}
			currentAccessType = param.accessType;
		}

		outFile << param.type << " " << param.name << ";" << std::endl;
	}

	for (int i = 0; i < codeClass.functions.size(); i++)
	{
		const CodeFunction& function = codeClass.functions[i];

		if (function.accessType != currentAccessType)
		{
			switch (function.accessType)
			{
			case ECodeAccessType::Private:
				outFile << "private:" << std::endl; break;
			case ECodeAccessType::Protected:
				outFile << "protected:" << std::endl; break;
			case ECodeAccessType::Public:
				outFile << "public:" << std::endl; break;
			}
			currentAccessType = function.accessType;
		}

		if (function.keywords == ECodeFunctionKeyword::Virtual) { outFile << "virtual "; }

		outFile << function.returnType << " " << function.functionName << "(";
		for (int j = 0; j < function.arguments.size(); j++)
		{
			if (function.arguments[j].isConst) { outFile << "const "; }

			outFile << function.arguments[j].type << " " << function.arguments[j].name;
			if (j < function.arguments.size() - 1) { outFile << ","; }
		}
		outFile << ")";

		if (function.keywords == ECodeFunctionKeyword::Virtual) { outFile << " override"; }
		
		outFile << ";" << std::endl;
	}

	outFile << std::endl << "}" << std::endl;
}

void CppCodeOStream::StreamClassToCpp(const CodeClass & codeClass)
{
	for (int i = 0; i < codeClass.params.size(); i++)
	{
		if (codeClass.params[i].keywords == ECodeParamKeyword::Static)
		{
			outFile << codeClass.params[i].type << " " << codeClass.name << "::" << codeClass.params[i].name << std::endl;
		}
	}

	for (int i = 0; i < codeClass.functions.size(); i++)
	{
		const CodeFunction& function = codeClass.functions[i];

		outFile << function.returnType << " " << codeClass.name << "::" << function.functionName << "(";

		for (int j = 0; j < function.arguments.size(); j++)
		{
			if (function.arguments[j].isConst) { outFile << "const "; }

			outFile << function.arguments[j].type << " " << function.arguments[j].name;
			if (j < function.arguments.size() - 1) { outFile << ","; }
		}
		outFile << ")" << std::endl << "{" << std::endl << std::endl << "}" << std::endl << std::endl;
	}
}
