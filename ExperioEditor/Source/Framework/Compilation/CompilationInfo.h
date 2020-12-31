#pragma once

struct FCompilationInfo
{
	bool isCompiling;
	float timeSinceLastCompile;

	FCompilationInfo()
	{
		this->isCompiling = false;
		this->timeSinceLastCompile = 0.0f;
	}

	FCompilationInfo(bool isCompiling, float time)
	{
		this->isCompiling = isCompiling;
		this->timeSinceLastCompile = time;
	}
};