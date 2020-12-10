#pragma once
#include "CodeProject.h"
#include "CodeEnum.h"
#include <string>
#include <vector>
#include "Runtime/Containers/TTypedTree.h"
#include "Runtime/Files/FileBuffer.h"

class FileBuffer;

enum class ECodingLanguageFeature : uint8_t
{
	Async,
	Classes,
	Coroutines,
	Enums,
	Foreach,
	Modules,
	Namespaces
};

class LCodeParser
{
public:
	static std::string ConcatenateNamespaces(std::vector<std::string> namespaces, ECodingLanguage language);

	static TTypedTree<std::string>* CreateInheritanceHierarchy(const CodeProject& project);

	static bool DoesLanguageSupport(ECodingLanguage langauge, ECodingLanguageFeature feature);
	static bool DoesLanguageSupport(ECodingLanguage language, ECodingLanguageFeature feature, uint16_t version);

	static std::string EnumDataTypeToString(EEnumDataType dataType, ECodingLanguage language);

	static EEnumDataType GetEnumDataType(unsigned int numValues);
	static EEnumDataType GetEnumDataType(const std::string& string, ECodingLanguage language);

	static std::string GetClassNameFromDeclaration(std::string className);

	static void GetEnumNameValue(const std::string& valueText, int& currentValue, std::string& name, int& value);

	static std::string GetLanguageVersionString(ECodingLanguage language, uint16_t version);

	static std::vector<std::string> GetInheritanceFromDeclaration(std::string className);

	static bool InheritsFrom(const CodeClass& codeClass, const std::string& baseClass);
	static bool InheritsFrom(const CodeClass& codeClass, const CodeClass& baseClass);

	static bool IsAbstract(const CodeClass& codeClass);

	static bool IsDefaultType(const std::string& name, ECodingLanguage language);
	static bool IsString(const std::string& name, ECodingLanguage language);

	static bool IsCompiled(ECodingLanguage language);
	static bool IsInterpreted(ECodingLanguage language);
	static bool IsSupported(ECodingLanguage language);

	static bool IsEnumToken(const FileBuffer& buffer, size_t currentIndex, ECodingLanguage language);
	static bool IsClassToken(const FileBuffer& buffer, size_t currentIndex, ECodingLanguage language);
	static bool IsFunctionToken(const std::string& str, ECodingLanguage language);

	static bool IsFilepathOfLanguage(ECodingLanguage language, std::string path);

	static CodeArg ParseCodeArg(const std::string& str, ECodingLanguage language);
	static CodeFunction ParseCodeFunction(const std::string& str, ECodingLanguage language);
	static CodeParam ParseCodeParam(const std::string& str, ECodingLanguage language);

	static size_t SerializedSizeOf(const CodeClass& codeClass, const CodeProject& codeProject, ECodingLanguage language);
	static size_t SizeOfDefaultType(const std::string& name, ECodingLanguage language);
	static size_t SizeOfParam(const CodeParam& param, const CodeProject& codeProject, ECodingLanguage language);
	static size_t SizeOfEnum(const CodeEnum& codeEnum);
	static size_t SizeOfEnum(EEnumDataType dataType);
	static size_t SizeOfExperioSerializedType(const std::string& name);
	static size_t SizeOfGLMSerializedType(const std::string& name);
};