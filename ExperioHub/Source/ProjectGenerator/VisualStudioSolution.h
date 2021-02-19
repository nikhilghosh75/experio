#pragma once
#include "VisualStudioProject.h"

namespace ExperioEditor::VisualStudio
{
class VSSolution
{
public:
	std::vector<VSProject> projects;

	void GenerateSolutionFile(const std::string& filepath);

private:
	static GUID128 GetProjectTypeGUID(EVSProjectType type);

	static std::string GetProjectTypeGUIDString(EVSProjectType type);
};
}