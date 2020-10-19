#pragma once
#include "CodeProject.h"
#include <string>
#include <vector>
#include "Runtime/Files/FileBuffer.h"

class FileBuffer;

enum class ECodingLanguageFeature : uint8_t
{
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

	static bool DoesLanguageSupport(ECodingLanguage langauge, ECodingLanguageFeature feature);
	static bool DoesLanguageSupport(ECodingLanguage language, ECodingLanguageFeature feature, uint16_t version);

	static bool IsAbstract(const CodeClass& codeClass);

	static bool IsCompiled(ECodingLanguage language);
	static bool IsInterpreted(ECodingLanguage language);
	static bool IsSupported(ECodingLanguage language);

	static bool IsEnumToken(const FileBuffer& buffer, size_t currentIndex, ECodingLanguage language);
	// static bool IsClassToken(const FileBuffer& buffer, size_t currentIndex, ECodingLanguage language);

	static bool IsFilepathOfLanguage(ECodingLanguage language, std::string path);
};