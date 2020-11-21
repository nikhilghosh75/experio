#include "TestManager.h"

std::vector<UnitTestSuite*> TestingManager::unitTestSuites;

void TestingManager::RegisterUnitTest(UnitTestSuite * suite)
{
	unitTestSuites.push_back(suite);
}

std::vector<FUnitTestingOutcome> TestingManager::RunTests()
{
	std::vector<FUnitTestingOutcome> outcomes;
	outcomes.reserve(unitTestSuites.size());

	for (int i = 0; i < unitTestSuites.size(); i++)
	{
		outcomes.push_back(unitTestSuites[i]->RunTests());
	}
	return outcomes;
}

void RegisterUnitTest(std::function<FAssertionOutcome(void)> func, std::string name, std::string category)
{
	for (int i = 0; i < TestingManager::unitTestSuites.size(); i++)
	{
		UnitTestSuite* suite = TestingManager::unitTestSuites[i];
		if (suite->CompareName(category))
		{
			suite->RegisterTest(func, name);
		}
	}
}

void RegisterUnitTestSuite(UnitTestSuite * suite)
{
	TestingManager::RegisterUnitTest(suite);
}
