#pragma once
#include "CodeProject.h"

class CodeAnalytics
{
public:
	size_t numLines;
	size_t numFiles;

	size_t numClasses;
	size_t numEnums;
	size_t numFunctions;

	// Experio Specific
	size_t numComponents;
	size_t numLibraries;

	CodeAnalytics();

	void Clear();
};

void GenerateCodeAnalyticsFromProject(CodeAnalytics& analytics, const CodeProject& project);