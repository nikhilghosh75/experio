#pragma once

class CodeGenerator
{
public:
	static void GenerateAllFiles();

// private:
public:
	static void GenerateComponentManager();

	static void GenerateProjectFile();

	static void GenerateComponentParsers();

public:
	static void GenerateTagFile();
};