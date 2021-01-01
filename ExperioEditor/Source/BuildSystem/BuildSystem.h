#pragma once
#include <string>
#include <stdint.h>
#include "../Framework/Compilation/CompilationSystem.h"

enum class EAssetType : uint8_t;

namespace ExperioEditor::BuildSystem
{
	enum class EBuildTarget
	{
		None,
		Windows
	};

	enum class EBuildOutcome
	{
		Success,
		CompileFailed
	};

	struct FWindowsBuildSettings
	{

	};

	void StartBuildForWindows(const std::string& buildFolder, const FWindowsBuildSettings& buildSettings);

	bool IsBuilding();

	EBuildTarget GetCurrentBuildTarget();

	float GetCurrentProgress();

	FWindowsBuildSettings DefaultWindowsBuildSettings();

	namespace Detail
	{
		void DoBuildForWindows(const std::string& buildFolder, const FWindowsBuildSettings& buildSettings);

		void RegenerateFiles();

		void BlockUntilCompilationComplete();

		void MoveFilesToBuildFolder(const std::string& buildFolder);

		void StartConversion(const std::string & buildFolder);

		void EndConversion(const std::string & buildFolder);

		void ConvertFile(const std::string& fromFile, const std::string& toFolder);

		bool ShouldBuildIgnoreCopy(EAssetType type);

		std::string GetConvertedFilename(const std::string& fromFile, const std::string& toFolder, EAssetType type);

		void MoveBuildFiles(const std::string& buildFolder);

		void TempMoveExecutable(const std::string& buildFolder);

		void FinishBuild(EBuildOutcome outcome);

		void HandleCompilationFinish(FCompilationResult& result);
	}
}