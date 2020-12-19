#pragma once

class CodeClass;
class CppCodeOStream;

class CodeGenerator
{
public:
	static void GenerateAllFiles();

	static void GenerateComponentManager();

	// static void GenerateProjectFile();

	// static void GenerateComponentParsers();

	static void GenerateTagFile();

private:
	static CodeClass GenerateComponentManagerClass();

	static void GenerateComponentManagerStartImpl(CppCodeOStream& cppFile, const CodeClass& codeClass);
	static void GenerateComponentManagerUpdateImpl(CppCodeOStream& cppFile, const CodeClass& codeClass);
	static void GenerateComponentManagerRenderSceneImpl(CppCodeOStream& cppFile, const CodeClass& codeClass);
	static void GenerateComponentManagerAddComponentImpl(CppCodeOStream& cppFile, const CodeClass& codeClass);
	static void GenerateComponentManagerGetComponentImpl(CppCodeOStream& cppFile, const CodeClass& codeClass);
	static void GenerateComponentManagerGetComponentAtIndexImpl(CppCodeOStream& cppFile, const CodeClass& codeClass);
	static void GenerateComponentManagerDeleteComponentImpl(CppCodeOStream& cppFile, const CodeClass& codeClass);
	static void GenerateComponentManagerOnGameObjectDeletedImpl(CppCodeOStream& cppFile, const CodeClass& codeClass);
	static void GenerateComponentManagerGetComponentIDsImpl(CppCodeOStream& cppFile, const CodeClass& codeClass);
	static void GenerateComponentManagerGetComponentPointersImpl(CppCodeOStream& cppFile, const CodeClass& codeClass);
	static void GenerateComponentManagerGetAllComponentsImpl(CppCodeOStream& cppFile, const CodeClass& codeClass);
	static void GenerateComponentManagerCountImpl(CppCodeOStream& cppFile, const CodeClass& codeClass);
};