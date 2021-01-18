#include "VisualStudioProject.h"
#include "../CodeParser/LCodeParser.h"
#include "Runtime/Core/Platform.h"
#include "Runtime/Files/LFileOperations.h"
#include <fstream>

namespace ExperioEditor::VisualStudio 
{
VSProject::VSProject(const std::string & name)
{
	this->name = name;
	this->id = GUID128::Random();
}

void VSProject::SetConfiguration(EVSConfiguration configuration)
{
	this->debugConfiguration = configuration;
	this->releaseConfiguration = configuration;
}

void VSProject::GenerateProjectFile(std::string & filepath)
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
	outFile << "</PropertyGroup>" << std::endl;

	outFile << "<Import Project=" << "\"$(VCTargetsPath)\Microsoft.Cpp.Default.props\"" << "/>" << std::endl;

	outFile << "<PropertyGroup Condition=\"'$(Configuration)|$(Platform)' == 'Debug|x64'\" Label=\"Configuration\">" << std::endl;
	outFile << "<ConfigurationType>" << ConfigurationToString(this->debugConfiguration) << "</ConfigurationType>" << std::endl;
	outFile << "<UseDebugLibraries>" << "true" << "</UseDebugLibraries>" << std::endl;
	outFile << "<PlatformToolset>" << "v141" << "</PlatformToolset>" << std::endl;
	outFile << "<CharacterSet>" << "MultiByte" << "</CharacterSet>" << std::endl;
	outFile << "</PropertyGroup>" << std::endl;

	outFile << "<PropertyGroup Condition=\"'$(Configuration)|$(Platform)' == 'Release|x64'\" Label=\"Configuration\">" << std::endl;
	outFile << "<ConfigurationType>" << ConfigurationToString(this->releaseConfiguration) << "</ConfigurationType>" << std::endl;
	outFile << "<UseDebugLibraries>" << "false" << "</UseDebugLibraries>" << std::endl;
	outFile << "<PlatformToolset>" << "v141" << "</PlatformToolset>" << std::endl;
	outFile << "<WholeProgramOptimization>" << "true" << "</WholeProgramOptimization>" << std::endl;
	outFile << "<CharacterSet>" << "MultiByte" << "</CharacterSet>" << std::endl;
	outFile << "</PropertyGroup>" << std::endl;

	outFile << "<Import Project=" << "\"$(VCTargetsPath)\Microsoft.Cpp.props\"" << "/>" << std::endl;
	outFile << "<ImportGroup Label=\"ExtensionSettings\">" << "</ImportGroup>" << std::endl;
	outFile << "<ImportGroup Label=\"Shared\">" << "</ImportGroup>" << std::endl;
	
	outFile << "<PropertyGroup Label=\"UserMacros\"/>" << std::endl;

	outFile << "<PropertyGroup Condition=\"'$(Configuration)|$(Platform)' == 'Debug|x64'\">" << std::endl;
	outFile << "<OutDir>" << this->outputDirectory << "</OutDir>" << std::endl;
	outFile << "<IntDir>" << this->intermediateDirectory << "</IntDir>" << std::endl;
	outFile << "</PropertyGroup>" << std::endl;
	outFile << "<PropertyGroup Condition=\"'$(Configuration)|$(Platform)' == 'Release|x64'\">" << std::endl;
	outFile << "<OutDir>" << this->outputDirectory << "</OutDir>" << std::endl;
	outFile << "<IntDir>" << this->intermediateDirectory << "</IntDir>" << std::endl;
	outFile << "</PropertyGroup>" << std::endl;

	outFile << "<ItemDefinitionGroup Condition=\"'$(Configuration)|$(Platform)'=='Debug|x64'\">" << std::endl;
	outFile << "<ClCompile>" << std::endl;
	outFile << "<WarningLevel>" << "Level3" << "</WarningLevel>" << std::endl;
	outFile << "<Optimization>" << "Disabled" << "</Optimization>" << std::endl;
	outFile << "<SDLCheck>" << "true" << "</SDLCheck>" << std::endl;
	outFile << "<ConformanceMode>" << "false" << "</ConformanceMode>" << std::endl;
	outFile << "<PreprocessorDefinitions>";
	for (int i = 0; i < this->preprocessorDefines.size() - 1; i++)
	{
		outFile << this->preprocessorDefines[i] << ";";
	}
	outFile << this->preprocessorDefines[this->preprocessorDefines.size() - 1] << "</PreprocessorDefinitions>" << std::endl;
	outFile << "<AdditionalIncludeDirectories>";
	for (int i = 0; i < this->additionalIncludeDirectories.size() - 1; i++)
	{
		outFile << this->additionalIncludeDirectories[i] << ";";
	}
	outFile << this->additionalIncludeDirectories[this->additionalIncludeDirectories.size() - 1] << "</AdditionalIncludeDirectories>" << std::endl;
	outFile << "<EnableModules>" << "false" << "</EnableModules>" << std::endl;
	outFile << "<LanguageStandard>" << LCodeParser::GetLanguageVersionString(this->language, this->version) << "</LanguageStandard>" << std::endl;
	outFile << "</ClCompile>" << std::endl;
	outFile << "</ItemDefinitionGroup>" << std::endl;

	outFile << "<ItemDefinitionGroup Condition=\"'$(Configuration)|$(Platform)'=='Release|x64'\">" << std::endl;
	outFile << "<ClCompile>" << std::endl;
	outFile << "<WarningLevel>" << "Level3" << "</WarningLevel>" << std::endl;
	outFile << "<Optimization>" << "Disabled" << "</Optimization>" << std::endl;
	outFile << "<SDLCheck>" << "true" << "</SDLCheck>" << std::endl;
	outFile << "<ConformanceMode>" << "false" << "</ConformanceMode>" << std::endl;
	outFile << "<PreprocessorDefinitions>";
	for (int i = 0; i < this->preprocessorDefines.size() - 1; i++)
	{
		outFile << this->preprocessorDefines[i] << ";";
	}
	outFile << this->preprocessorDefines[this->preprocessorDefines.size() - 1] << "</PreprocessorDefinitions>" << std::endl;
	outFile << "<AdditionalIncludeDirectories>";
	for (int i = 0; i < this->additionalIncludeDirectories.size() - 1; i++)
	{
		outFile << this->additionalIncludeDirectories[i] << ";";
	}
	outFile << this->additionalIncludeDirectories[this->additionalIncludeDirectories.size() - 1] << "</AdditionalIncludeDirectories>" << std::endl;
	outFile << "<EnableModules>" << "false" << "</EnableModules>" << std::endl;
	outFile << "<LanguageStandard>" << LCodeParser::GetLanguageVersionString(this->language, this->version) << "</LanguageStandard>" << std::endl;
	outFile << "</ClCompile>" << std::endl;
	outFile << "<Link>" << std::endl;
	outFile << "<EnableCOMDATFolding>" << "true" << "</EnableCOMDATFolding>" << std::endl;
	outFile << "<OptimizeReferences>" << "true" << "</OptimizeReferences>" << std::endl;
	outFile << "</Link>" << std::endl;
	outFile << "</ItemDefinitionGroup>" << std::endl;

	outFile << "</Project>" << std::endl;
}

std::string VSProject::ArchitectureToString(EArchitecture architecture)
{
	switch (architecture)
	{
	case EArchitecture::x64: return "x64";
	case EArchitecture::x86: return "x86";
	}
}

std::string VSProject::ConfigurationToString(EVSConfiguration configuration)
{
	switch(configuration)
	{
	case EVSConfiguration::StaticLibrary: return "StaticLibrary";
	case EVSConfiguration::DynamicLibrary: return "DynamicLibrary";
	case EVSConfiguration::Executable: return "Executable";
	}
}
}