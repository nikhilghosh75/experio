#pragma once
#include "../Core/EditorModule.h"
#include "TestManager.h"
#include "UnitTestingFramework.h"
#include "Runtime/Time/FDuration.h"

class TestRunner : public EditorModule
{
	bool testsRun = false;

	std::vector<std::string> testNames;

	std::vector<FUnitTestingOutcome> outcomes;

	FDuration testDuration;

public:
	TestRunner();

	virtual void Display() override;
};