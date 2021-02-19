#include "EditorCodeGenerator.h"
#include "CodeParser/Cpp/CppCodeStream.h"

void EditorCodeGenerator::GenerateBuild(const std::string & editorPath)
{
	CppCodeOStream outFile(editorPath + "/DemoProjectBuild.cpp");
	outFile << "#ifndef EXPERIO_EDITOR" << Debug::endl;
	outFile << "#define EXPERIO_EDITOR" << Debug::endl;
	outFile << "#endif" << Debug::endl;

	// Add stuff here if necessary
}

void EditorCodeGenerator::GenerateRCCPP(const std::string & editorPath)
{
	// Fix it later
}

void EditorCodeGenerator::GenerateMain(const std::string & editorPath)
{
	CppCodeOStream outFile(editorPath + "/Main.cpp");
	outFile << "#include \"Core / EditorApplication.h\"" << Debug::endl;
	outFile << "#include \"DemoProject.h\"" << Debug::endl;
	outFile << Debug::endl;

	outFile << "void SetupProjectEditor()" << Debug::endl << "{" << Debug::endl;
	outFile << "Project::componentManager = new DemoProjectComponentManager();" << Debug::endl;
	outFile << "Project::materialManager = new DemoProjectMaterialManager();" << Debug::endl;
	outFile << "Project::projectName = \"Demo Project\";" << Debug::endl;
	outFile << "}" << Debug::endl;

	outFile << "void ShutdownProjectEditor()" << Debug::endl << "{" << Debug::endl;
	outFile << "delete Project::componentManager;" << Debug::endl;
	outFile << "delete Project::materialManager;" << Debug::endl;
	outFile << "}" << Debug::endl;

	outFile << "int main(int argc, char** argv)" << Debug::endl << "{" << Debug::endl;
	outFile << "SetupProjectEditor();" << Debug::endl;
	outFile << "EditorApplication application;" << Debug::endl;
	outFile << "application.Setup(\"../Demo Project.pbproj\");" << Debug::endl;
	outFile << "application.LoadScenes();" << Debug::endl;
	outFile << "application.Run();" << Debug::endl;
	outFile << "application.Shutdown();" << Debug::endl;
	outFile << "ShutdownProjectEditor();" << Debug::endl;
	outFile << "}" << Debug::endl;
}

void EditorCodeGenerator::GenerateExecutable(const std::string & generatedPath)
{
	CppCodeOStream outFile(generatedPath + "/Main.cpp");
	outFile << "void SetupProject();" << Debug::endl;
	outFile << "void RunProject();" << Debug::endl;
	outFile << Debug::endl;

	outFile << "int main(int argc, char** argv)" << Debug::endl << "{" << Debug::endl;
	outFile << "SetupProject();" << Debug::endl;
	outFile << "RunProject();" << Debug::endl;
	outFile << "return 0;" << Debug::endl;
	outFile << "}" << Debug::endl;
}
