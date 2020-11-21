#include "VisualStudioProject.h"
#include "Runtime/Core/Platform.h"
#include "Runtime/Files/LFileOperations.h"
#include <fstream>

void ExperioEditor::VisualStudio::VSProject::GenerateProjectFile(std::string & filepath)
{
	std::ofstream outFile(filepath);

	outFile << "<?xml version=\"1.0\" encoding=\"utf - 8\"?>" << std::endl;
	outFile << "<Project DefaultTargets=\"Build\" ToolsVersion=\"15.0\" xmlns=\"http://schemas.microsoft.com/developer/msbuild/2003 \">" << std::endl;
	
	std::string architectureStr = ArchitectureToString(this->architecture);
	outFile << "<ItemGroup Label=\"ProjectConfigurations\">" << std::endl;
	outFile << "<ProjectConfiguration Include=\"Debug|" << architectureStr << "\">" << std::endl;
	outFile << "<Configuration>Debug</Configuration>" << std::endl << "<Platform>" << architectureStr << "</Platform>" << std::endl;
	outFile << "</ProjectConfiguration>" << std::endl;
	outFile << "<ProjectConfiguration Include=\"Release|" << architectureStr << "\">" << std::endl;
	outFile << "<Configuration>Release</Configuration>" << std::endl << "<Platform>" << architectureStr << "</Platform>" << std::endl;
	outFile << "</ProjectConfiguration>" << std::endl;
	outFile << "</ItemGroup>" << std::endl;

	outFile << "<ItemGroup>" << std::endl;
	for (int i = 0; i < this->includePaths.size(); i++)
	{
		outFile << "<ClInclude Include=\"" << this->includePaths[i] << "\"/>" << std::endl;
	}
	outFile << "</ItemGroup>" << std::endl;

	outFile << "<ItemGroup>" << std::endl;
	for (int i = 0; i < this->compilePaths.size(); i++)
	{
		outFile << "<ClCompile Include=\"" << this->compilePaths[i] << "\"/>" << std::endl;
	}
	outFile << "</ItemGroup>" << std::endl;

	outFile << "<PropertyGroup Label=\"Globals\">" << std::endl;
	outFile << "<VCProjectVersion>15.0</VCProjectVersion>" << std::endl;
	outFile << "<ProjectGuid>{" << this->id.ToVisualStudioString() << "}</ProjectGuid>" << std::endl;
	outFile << "<WindowsTargetPlatformVersion>" << GetVersionString() << "</WindowsTargetPlatformVersion>" << std::endl;
	outFile << "<ProjectName>" << this->name << "</ProjectName>" << std::endl;
	outFile << "</PropertyGroup>";
}

std::string ExperioEditor::VisualStudio::VSProject::ArchitectureToString(EArchitecture architecture)
{
	switch (architecture)
	{
	case EArchitecture::x64: return "x64";
	case EArchitecture::x86: return "x86";
	}
}
