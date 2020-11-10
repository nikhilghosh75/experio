#include "LCodeParser.h"
#include "Runtime/Containers/Algorithm.h"
#include "Runtime/Files/LFileOperations.h"
#include "Runtime/Debug/Debug.h"
#include "Runtime/Containers/LString.h"
#include "Runtime/Math/LMath.h"
#include <sstream>

#define PB_SERIALIZED_STRING_SIZE 8

std::string LCodeParser::ConcatenateNamespaces(std::vector<std::string> namespaces, ECodingLanguage language)
{
	std::stringstream ss;

	switch (language)
	{
	case ECodingLanguage::CPlusPlus:
		for (int i = 0; i < namespaces.size() - 1; i++)
		{
			ss << namespaces[i] << "::";
		}
		ss << namespaces[namespaces.size() - 1];
		return ss.str();
	case ECodingLanguage::CSharp:
	case ECodingLanguage::Python:
		for (int i = 0; i < namespaces.size() - 1; i++)
		{
			ss << namespaces[i] << ".";
		}
		ss << namespaces[namespaces.size() - 1];
		return ss.str();
	}
	Debug::Log("Language Feature Namespaces not supported");
	return "";
}

TTypedTree<std::string>* LCodeParser::CreateInheritanceHierarchy(const CodeProject & project)
{
	TTypedTree<std::string>* inheritanceHierarchy = new TTypedTree<std::string>("");

	const std::vector<CodeClass>& classes = project.classes;
	std::vector<bool> hasBeenAdded;
	hasBeenAdded.reserve(classes.size());
	size_t numNotAdded = 0;
	for (size_t i = 0; i < classes.size(); i++)
	{
		if (classes[i].inheritance.size() == 0)
		{
			inheritanceHierarchy->AddChildToRoot(classes[i].name);
			hasBeenAdded.push_back(true);
		}
		else
		{
			hasBeenAdded.push_back(false);
			numNotAdded++;
		}
	}

	size_t lastNumNotAdded = numNotAdded;
	while (Experio::Algorithm::ExistsIn(hasBeenAdded, false))
	{
		numNotAdded = 0;
		for (size_t i = 0; i < classes.size(); i++)
		{
			if (hasBeenAdded[i]) continue;
			
			numNotAdded++;
			std::string base = classes[i].inheritance[0];
			TTypedTreeNode<std::string>* foundNode = SearchTree<std::string>(inheritanceHierarchy, 
				[&base](std::string str) {return base == str; });
			
			if (foundNode != nullptr)
			{
				foundNode->AddChild(classes[i].name);
				hasBeenAdded[i] = true;
			}
		}

		if (numNotAdded == lastNumNotAdded) break;

		lastNumNotAdded = numNotAdded;
	}

	return inheritanceHierarchy;
}

bool LCodeParser::DoesLanguageSupport(ECodingLanguage language, ECodingLanguageFeature feature)
{
	switch (language)
	{
	case ECodingLanguage::CPlusPlus:
		switch (feature)
		{
		case ECodingLanguageFeature::Async:
		case ECodingLanguageFeature::Classes:
		case ECodingLanguageFeature::Enums:
		case ECodingLanguageFeature::Foreach:
		case ECodingLanguageFeature::Namespaces:
			return true;
		}
		break;
	case ECodingLanguage::CSharp:
		switch (feature)
		{
		case ECodingLanguageFeature::Classes:
		case ECodingLanguageFeature::Enums:
		case ECodingLanguageFeature::Foreach:
		case ECodingLanguageFeature::Namespaces:
			return true;
		}
		break;
	default:
		Debug::LogError("Language Not Implemented");
	}
	return false;
}

bool LCodeParser::DoesLanguageSupport(ECodingLanguage language, ECodingLanguageFeature feature, uint16_t version)
{
	switch (language)
	{
	case ECodingLanguage::CPlusPlus:
		switch (feature)
		{
		case ECodingLanguageFeature::Classes:
		case ECodingLanguageFeature::Enums:
		case ECodingLanguageFeature::Namespaces:
			return true;
		case ECodingLanguageFeature::Async: return version >= 11;
		case ECodingLanguageFeature::Coroutines: return version >= 20;
		case ECodingLanguageFeature::Foreach: return version >= 11;
		case ECodingLanguageFeature::Modules: return version >= 23;
		}
		break;
	case ECodingLanguage::CSharp:
		switch (feature)
		{
		case ECodingLanguageFeature::Classes:
		case ECodingLanguageFeature::Enums:
		case ECodingLanguageFeature::Foreach:
		case ECodingLanguageFeature::Namespaces:
			return true;
		case ECodingLanguageFeature::Async: return version >= 5;
		case ECodingLanguageFeature::Coroutines: return version >= 5;
		case ECodingLanguageFeature::Modules: return version >= 9;
		}
		break;
	default:
		Debug::LogError("Language Not Implemented");
	}
	return false;
}

EEnumDataType LCodeParser::GetEnumDataType(unsigned int numValues)
{
	// Note that the following is based on the face that the underlying type is the smallest possible type
	if (numValues <= LMath::PowOfTwo(8)) return EEnumDataType::BYTE;
	if (numValues <= LMath::PowOfTwo(16)) return EEnumDataType::SHORT;
	if (numValues <= LMath::PowOfTwo(32)) return EEnumDataType::INT;
	return EEnumDataType::LONGLONG;
}

#define PB_COMPARE_DATA_TYPE(_typename_, _type_) if(string.find(_typename_) != std::string::npos) return _type_;

EEnumDataType LCodeParser::GetEnumDataType(std::string string, ECodingLanguage language)
{
	switch (language)
	{
	case ECodingLanguage::CPlusPlus:
		PB_COMPARE_DATA_TYPE("char", EEnumDataType::BYTE);
		PB_COMPARE_DATA_TYPE("uint8_t", EEnumDataType::UBYTE);
		PB_COMPARE_DATA_TYPE("unsigned char", EEnumDataType::UBYTE);
		PB_COMPARE_DATA_TYPE("short", EEnumDataType::SHORT);
		PB_COMPARE_DATA_TYPE("uint16_t", EEnumDataType::USHORT);
		PB_COMPARE_DATA_TYPE("unsigned short", EEnumDataType::USHORT);
		PB_COMPARE_DATA_TYPE("int", EEnumDataType::INT);
		PB_COMPARE_DATA_TYPE("uint32_t", EEnumDataType::UINT);
		PB_COMPARE_DATA_TYPE("unsigned int", EEnumDataType::UINT);
		PB_COMPARE_DATA_TYPE("long long", EEnumDataType::LONGLONG);
		PB_COMPARE_DATA_TYPE("uint64_t", EEnumDataType::ULONGLONG);
		PB_COMPARE_DATA_TYPE("unsigned long long", EEnumDataType::ULONGLONG);
	}
	return EEnumDataType::NONE;
}

void LCodeParser::GetEnumNameValue(std::string valueText, int & currentValue, std::string & name, int & value)
{
	size_t equalsPosition = valueText.find('=');
	if (equalsPosition == std::string::npos)
	{
		name = LString::Trim(valueText);
		value = currentValue;
		currentValue++;
		return;
	}
}

std::string LCodeParser::GetClassNameFromDeclaration(std::string className)
{
	size_t firstSpace = className.find(' ');
	size_t secondSpace = LString::FindFirstOfChars(className, { ' ', '\n', '\t' }, firstSpace + 1);
	// size_t secondSpace = className.find(' ', firstSpace + 1);
	return className.substr(firstSpace + 1, secondSpace - firstSpace - 1);
}

std::vector<std::string> LCodeParser::GetInheritanceFromDeclaration(std::string className)
{
	size_t colonIndex = className.find(':');

	if (colonIndex == std::string::npos)
	{
		return std::vector<std::string>();
	}

	std::string afterColon = className.substr(colonIndex);
	std::vector<std::string> tempInheritance = LString::SeperateStringByChar(afterColon, ' ');

	// Cull Public and Private
	std::vector<std::string> inheritance;
	inheritance.reserve(tempInheritance.size());
	for (int i = 0; i < tempInheritance.size(); i++)
	{
		if (tempInheritance[i].find("public") != std::string::npos) continue;
		if (tempInheritance[i].find("private") != std::string::npos) continue;
		if (tempInheritance[i].find(":") != std::string::npos) continue;
		inheritance.push_back(tempInheritance[i]);
	}

	for (int i = 0; i < inheritance.size(); i++)
	{
		if (inheritance[i][inheritance[i].size() - 1] == '\n')
		{
			inheritance[i] = inheritance[i].substr(0, inheritance[i].size() - 1);
		}
	}

	return inheritance;
}

bool LCodeParser::InheritsFrom(const CodeClass & codeClass, const std::string & baseClass)
{
	return Experio::Algorithm::ExistsIn(codeClass.inheritance, baseClass);
}

bool LCodeParser::InheritsFrom(const CodeClass & codeClass, const CodeClass & baseClass)
{
	return Experio::Algorithm::ExistsIn(codeClass.inheritance, baseClass.name);
}

bool LCodeParser::IsAbstract(const CodeClass & codeClass)
{
	return codeClass.functions.size() > 0 && codeClass.params.size() == 0;
}

bool LCodeParser::IsDefaultType(const std::string & name, ECodingLanguage language)
{
	switch (language)
	{
	case ECodingLanguage::CPlusPlus:
		if (name == "char") return true;
		if (name == "unsigned char") return true;
		if (name == "short") return true;
		if (name == "unsigned short") return true;
		if (name == "int") return true;
		if (name == "unsigned int") return true;
		if (name == "long long") return true;
		if (name == "unsigned long long") return true;
		if (name == "uint8_t") return true;
		if (name == "int8_t") return true;
		if (name == "uint16_t") return true;
		if (name == "int16_t") return true;
		if (name == "uint32_t") return true;
		if (name == "int32_t") return true;
		if (name == "uint64_t") return true;
		if (name == "int64_t") return true;
		if (name == "float") return true;
		if (name == "double") return true;
		if (name == "bool") return true;
		break;
	case ECodingLanguage::CSharp:
		if (name == "bool") return true;
		if (name == "byte") return true;
		if (name == "char") return true;
		if (name == "decimal") return true;
		if (name == "float") return true;
		if (name == "int") return true;
		if (name == "long") return true;
		if (name == "uint") return true;
		if (name == "ulong") return true;
		break;
	}
	return false;
}

bool LCodeParser::IsString(const std::string & name, ECodingLanguage language)
{
	switch (language)
	{
	case ECodingLanguage::None:
		break;
	case ECodingLanguage::CPlusPlus:
		if (name == "string") return true;
		if (name == "std::string") return true;
		if (name == "char*") return true;
		if (name == "char *") return true;
		break;
	}
	return false;
}

bool LCodeParser::IsCompiled(ECodingLanguage language)
{
	return language == ECodingLanguage::CPlusPlus 
		|| language == ECodingLanguage::CSharp 
		|| language == ECodingLanguage::Java;
}

bool LCodeParser::IsInterpreted(ECodingLanguage language)
{
	return language == ECodingLanguage::Python;
}

bool LCodeParser::IsSupported(ECodingLanguage language)
{
	return language == ECodingLanguage::CPlusPlus;
}

#define PB_COMPARE_TOKEN(_token_, _tokenLength_) if(currentIndex + _tokenLength_ < buffer.Size())\
{\
	int compareIndex = 0;\
	for (int j = 0; j < _tokenLength_; j++)\
	{\
		if (buffer[currentIndex + j] != _token_[j])\
		{\
			break;\
		}\
		compareIndex++;\
	}\
	if(compareIndex == _tokenLength_)\
	{\
		if(LString::IsWhitespace(buffer[currentIndex - 1]) && LString::IsWhitespace(buffer[currentIndex + _tokenLength_]))\
		{\
			return true;\
		}\
	}\
}

bool LCodeParser::IsEnumToken(const FileBuffer& buffer, size_t currentIndex, ECodingLanguage language)
{
	const char* enumToken = "enum";
	switch (language)
	{
	case ECodingLanguage::CPlusPlus:
	case ECodingLanguage::CSharp:
	case ECodingLanguage::Java:
		PB_COMPARE_TOKEN(enumToken, 4);
		break;
	case ECodingLanguage::Python:
		return false;
	}
	return false;
}

bool LCodeParser::IsClassToken(const FileBuffer & buffer, size_t currentIndex, ECodingLanguage language)
{
	const char* classToken = "class";
	const char* structToken = "struct";
	switch (language)
	{
	case ECodingLanguage::CPlusPlus:
	case ECodingLanguage::CSharp:
		PB_COMPARE_TOKEN(classToken, 5);
		PB_COMPARE_TOKEN(structToken, 6);
		break;
	}
	return false;
}

bool LCodeParser::IsFunctionToken(const std::string & str, ECodingLanguage language)
{
	return str.find('(') != std::string::npos;
}

#define PB_COMPARE_EXT(_language_, _ext_) if(_language_ == language && ext == _ext_) return true;

bool LCodeParser::IsFilepathOfLanguage(ECodingLanguage language, std::string path)
{
	if (language == ECodingLanguage::None) return false;

	std::string ext = LFileOperations::GetExtension(path);
	
	PB_COMPARE_EXT(ECodingLanguage::CPlusPlus, "cpp");
	PB_COMPARE_EXT(ECodingLanguage::CPlusPlus, "h");
	PB_COMPARE_EXT(ECodingLanguage::CPlusPlus, "hpp");

	PB_COMPARE_EXT(ECodingLanguage::CSharp, "cs");

	PB_COMPARE_EXT(ECodingLanguage::Java, "java");

	PB_COMPARE_EXT(ECodingLanguage::Python, "python");

	return false;
}

CodeArg LCodeParser::ParseCodeArg(std::string str, ECodingLanguage language)
{
	CodeArg arg;
	str = LString::TrimLeft(str);

	size_t argTypeStart = 0;
	if (str.find("const ") != std::string::npos)
	{
		argTypeStart = str.find("const ") + 6;
		arg.isConst = true;
	}
	else
	{
		arg.isConst = false;
	}

	size_t firstSpace = str.find(' ');
	arg.type = str.substr(argTypeStart, firstSpace - argTypeStart);
	arg.name = str.substr(firstSpace + 1);

	return arg;
}

CodeFunction LCodeParser::ParseCodeFunction(std::string str, ECodingLanguage language)
{
	CodeFunction func;

	switch (language)
	{
	case ECodingLanguage::CPlusPlus: // C++
	{
		func.accessType = ECodeAccessType::Unknown;

		size_t returnTypeStart = 0;
		if (str.find("static ") != std::string::npos)
		{
			returnTypeStart = str.find("static ") + 7;
			func.keywords = ECodeFunctionKeyword::Static;
		}
		size_t firstSpace = str.find(' ', returnTypeStart);
		func.returnType = str.substr(returnTypeStart, firstSpace - returnTypeStart);

		size_t firstParen = str.find('(');
		func.functionName = str.substr(firstSpace + 1, firstParen - firstSpace - 1);

		size_t firstRightParen = str.find(')');
		if (firstRightParen == firstParen + 1)
		{
			func.arguments = std::vector<CodeArg>();
		}
		else
		{
			std::vector<std::string> argStrings = LString::SeperateStringByChar(
				str.substr(firstParen + 1, firstRightParen - firstParen - 1), ',');
			std::vector<CodeArg> args;
			args.reserve(argStrings.size());
			for (int i = 0; i < argStrings.size(); i++)
			{
				args.push_back(ParseCodeArg(argStrings[i], language));
			}
			func.arguments = args;
		}
	}
		break;
	default:
		Debug::LogError("Language is not supported");
		break;
	}

	return func;
}

CodeParam LCodeParser::ParseCodeParam(std::string str, ECodingLanguage language)
{
	CodeParam param;

	switch (language)
	{
	case ECodingLanguage::CPlusPlus: // C++
	{
		param.accessType = ECodeAccessType::Unknown;

		size_t returnTypeStart = 0;
		if (str.find("static ") != std::string::npos)
		{
			returnTypeStart = str.find("static ") + 7;
			param.keywords = ECodeParamKeyword::Static;
		}
		size_t firstSpace = str.find(' ', returnTypeStart);
		param.type = str.substr(returnTypeStart, firstSpace - returnTypeStart);

		size_t firstParen = str.find('(');
		param.name = str.substr(firstSpace + 1, firstParen - firstSpace - 1);
	}
	break;
	default:
		Debug::LogError("Language is not supported");
		break;
	}

	return param;
}

size_t LCodeParser::SerializedSizeOf(const CodeClass & codeClass, const CodeProject& codeProject, ECodingLanguage language)
{
	const std::vector<CodeParam> params = codeClass.params;
	size_t size = 0;
	for (size_t i = 0; i < params.size(); i++)
	{
		size += SizeOfParam(params[i], codeProject, language);
	}
	return size;
}

size_t LCodeParser::SizeOfDefaultType(const std::string & name, ECodingLanguage language)
{
	switch (language)
	{
	case ECodingLanguage::CPlusPlus:
		if (name == "char") return 1;
		if (name == "unsigned char") return 1;
		if (name == "short") return 2;
		if (name == "unsigned short") return 2;
		if (name == "int") return 4;
		if (name == "unsigned int") return 4;
		if (name == "long long") return 8;
		if (name == "unsigned long long") return 8;
		if (name == "uint8_t") return 1;
		if (name == "int8_t") return 1;
		if (name == "uint16_t") return 2;
		if (name == "int16_t") return 2;
		if (name == "uint32_t") return 4;
		if (name == "int32_t") return 4;
		if (name == "uint64_t") return 8;
		if (name == "int64_t") return 8;
		if (name == "float") return 4;
		if (name == "double") return 8;
		if (name == "bool") return 1;
		break;
	case ECodingLanguage::CSharp:
		if (name == "bool") return 1;
		if (name == "byte") return 1;
		if (name == "char") return 1;
		if (name == "decimal") return 4;
		if (name == "float") return 4;
		if (name == "int") return 4;
		if (name == "long") return 8;
		if (name == "uint") return 4;
		if (name == "ulong") return 8;
		break;
	}
	return 0;
}

size_t LCodeParser::SizeOfParam(const CodeParam& param, const CodeProject & codeProject, ECodingLanguage language)
{
	const std::string& paramTypename = param.type;

	// Search for Default Types
	size_t foundSize = SizeOfDefaultType(paramTypename, language);
	if (foundSize != 0)
	{
		return foundSize;
	}
	if (IsString(param.type, language))
	{
		return PB_SERIALIZED_STRING_SIZE;
	}

	// Search for Experio Types that can be serialized
	foundSize = SizeOfExperioSerializedType(paramTypename);
	if (foundSize != 0)
	{
		return foundSize;
	}

	// Search for types in dependencies that can be serialized
	foundSize = SizeOfGLMSerializedType(paramTypename);
	if (foundSize != 0)
	{
		return foundSize;
	}

	// Search for Enums
	for (size_t i = 0; i < codeProject.enums.size(); i++)
	{
		if (codeProject.enums[i].name == paramTypename)
		{
			return SizeOfEnum(codeProject.enums[i]);
		}
	}

	return 0;
}

size_t LCodeParser::SizeOfEnum(const CodeEnum & codeEnum)
{
	return SizeOfEnum(codeEnum.dataType);
}

size_t LCodeParser::SizeOfEnum(EEnumDataType dataType)
{
	switch (dataType)
	{
	case EEnumDataType::BYTE: return 1;
	case EEnumDataType::UBYTE: return 1;
	case EEnumDataType::SHORT: return 2;
	case EEnumDataType::USHORT: return 2;
	case EEnumDataType::INT: return 4;
	case EEnumDataType::UINT: return 4;
	case EEnumDataType::LONGLONG: return 8;
	case EEnumDataType::ULONGLONG: return 8;
	}
	return 0;
}

size_t LCodeParser::SizeOfExperioSerializedType(const std::string & name)
{
	if (name == "FVector2") return 8;
	if (name == "FVector3") return 12;
	if (name == "FVector4") return 16;
	if (name == "FCurve") return 0;
	if (name == "MeshRef") return 4;
	if (name == "FQuaternion") return 16;
	if (name == "FRect") return 16;
	if (name == "Shader") return 8;
	if (name == "FSphericalPoint") return 12;
	if (name == "TextureRef") return 4;
	if (name == "Datatable") return 4;
	return 0;
}

size_t LCodeParser::SizeOfGLMSerializedType(const std::string & name)
{
	if (name == "glm::mat4") return 64;
	if (name == "glm::mat3") return 16;
	// Add other types here
	return 0;
}
