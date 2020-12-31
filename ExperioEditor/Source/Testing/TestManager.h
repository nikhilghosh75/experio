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

	static std::vector<std::string> GetTestNames();

	static size_t GetNumTests();
};

void RegisterUnitTest(std::function<FAssertionOutcome(void)> func, std::string name, std::string category);

void RegisterUnitTestSuite(UnitTestSuite* suite);