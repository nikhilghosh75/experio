#include "LCodeParser.h"
#include "Runtime/Files/LFileOperations.h"
#include "Runtime/Debug/Debug.h"
#include "Runtime/Containers/LString.h"
#include "Runtime/Math/LMath.h"
#include <sstream>

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

#define PB_COMPARE_DATA_TYPE(_typename_, _type_) if(string.find(_typename_)) return _type_;

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

bool LCodeParser::IsAbstract(const CodeClass & codeClass)
{
	return codeClass.functions.size() > 0 && codeClass.params.size() == 0;
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