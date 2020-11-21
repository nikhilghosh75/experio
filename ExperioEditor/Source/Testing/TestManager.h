#pragma once

#include "Assert.h"
#include "UnitTestingFramework.h"
#include <vector>

class TestingManager
{
public:
	static std::vector<UnitTestSuite*> unitTestSuites;

	static void RegisterUnitTest(UnitTestSuite* suite);

	static std::vector<FUnitTestingOutcome> RunTests();
};

void RegisterUnitTest(std::function<FAssertionOutcome(void)> func, std::string name, std::string category);

void RegisterUnitTestSuite(UnitTestSuite* suite);