#include "AdminTools.h"
#include "../CodeParser/CodeProjectWriter.h"
#include "../Core/EditorApplication.h"

AdminTools::AdminTools()
{
	this->category = EEditorModuleCategory::Admin;
	this->name = "Admin Tools";

	this->isAdmin = true;
}

void AdminTools::Display()
{
	if (ImGui::Button("Generate Engine Project File"))
	{
		CodeProject project(EditorApplication::experioFilePath + "/Source/Runtime");
		project.codingLanguage = ECodingLanguage::CPlusPlus;
		project.Generate();

		CodeProjectWriter::WriteToFile(project, EditorApplication::generatedFilePath + "/Engine.pbcodeproj");
	}
}
