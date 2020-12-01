#include "VisualStudioSolution.h"
#include <fstream>

namespace ExperioEditor::VisualStudio
{
void VSSolution::GenerateSolutionFile(std::string & filepath)
{
	std::ofstream outFile(filepath);
	outFile << std::endl;

	outFile << "Microsoft Visual Studio Solution File, Format Version 12.00" << std::endl;
	outFile << "# Visual Studio 15" << std::endl;
	outFile << "VisualStudioVersion = 15.0.28307.168" << std::endl;
	outFile << "MinimumVisualStudioVersion = 10.0.40219.1" << std::endl;

	for (size_t i = 0; i < projects.size(); i++)
	{
		outFile << "Project(\"{" << GetProjectTypeGUIDString(projects[i].projectType) << "}\") = ";
		outFile << "\"" << projects[i].name << "\", \"" << projects[i].filepath << 
			"\", \"{" << projects[i].id.ToVisualStudioString() << "}\"" << std::endl;
		outFile << "EndProject" << std::endl;
	}
}

GUID128 VSSolution::GetProjectTypeGUID(EVSProjectType type)
{
	switch (type)
	{
	case EVSProjectType::CSharp:
		return GUID128("FAE04EC0-301F-11D3-BF4B-00C04F79EFBC");
	case EVSProjectType::Cpp:
		return GUID128("8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942");
	case EVSProjectType::Database:
		return GUID128("A9ACE9BB-CECE-4E62-9AA4-C7E7C5BD2124");
	case EVSProjectType::MicroFramework:
		return GUID128("B69E3092-B931-443C-ABE7-7E7B65F2A37F");
	case EVSProjectType::ProjectFolder:
		return GUID128("66A26720-8FB5-11D2-AA7E-00C04F688DDE");
	}
	return GUID128();
}

std::string VSSolution::GetProjectTypeGUIDString(EVSProjectType type)
{
	switch (type)
	{
	case EVSProjectType::CSharp:
		return "FAE04EC0-301F-11D3-BF4B-00C04F79EFBC";
	case EVSProjectType::Cpp:
		return "8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942";
	case EVSProjectType::Database:
		return "A9ACE9BB-CECE-4E62-9AA4-C7E7C5BD2124";
	case EVSProjectType::MicroFramework:
		return "B69E3092-B931-443C-ABE7-7E7B65F2A37F";
	case EVSProjectType::ProjectFolder:
		return "66A26720-8FB5-11D2-AA7E-00C04F688DDE";
	}
	return "";
}

}