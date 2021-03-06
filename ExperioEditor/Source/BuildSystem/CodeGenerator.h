#pragma once

class CodeClass;
class CppCodeOStream;

class CodeGenerator
{
public:
	static void GenerateAllFiles();

	static void GenerateComponentManager();

	static void GenerateProjectFile();

	static void GenerateComponentSerializers();

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

	static void GenerateProjectHFile();
	static void GenerateProjectCppFile();

	static void GenerateSetupProjectImpl(CppCodeOStream& cppFile);
	static void GenerateRunProjectImpl(CppCodeOStream& cppFile);
	static void GenerateCreateComponentManagerImpl(CppCodeOStream& cppFile);
	static void GenerateCreateMaterialManagerImpl(CppCodeOStream& cppFile);

	static void GenerateParamsListImpl(CppCodeOStream& cppFile);
	static void GenerateSetComponentParamsImpl(CppCodeOStream& cppFile);
	static void GenerateSetComponentBinaryParamsImpl(CppCodeOStream& cppFile);
	static void GenerateAddComponentToSceneImpl(CppCodeOStream& cppFile);
	static void GenerateSizeOfImpl(CppCodeOStream& cppFile);
	static void GenerateSerializedSizeOfImpl(CppCodeOStream& cppFile);
};