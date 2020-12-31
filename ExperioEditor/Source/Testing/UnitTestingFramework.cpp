#include "UnitTestingFramework.h"
#include "Runtime\Debug\Debug.h"

UnitTestSuite::UnitTestSuite()
{
	Debug::Log("Test Suite Created");
}

UnitTestSuite::UnitTestSuite(std::string name, std::string category)
{
	this->name = name;
	this->category = category;
	Debug::Log("Test Suite Created");
	RegisterUnitTestSuite(this);
}

FUnitTestingOutcome UnitTestSuite::RunTests()
{
	FUnitTestingOutcome outcome;
	outcome.testNames.reserve(testFunctions.size());
	outcome.outcomes.reserve(testFunctions.size());

	for (int i = 0; i < testFunctions.size(); i++)
	{
		FAssertionOutcome assertionOutcome = testFunctions[i]();
		outcome.testNames.push_back(testFunctionNames[i]);
		outcome.outcomes.push_back(assertionOutcome);
	}

	return outcome;
}

void UnitTestSuite::RegisterTest(std::function<FAssertionOutcome(void)> func, std::string name)
{
	testFunctions.push_back(func);
	testFunctionNames.push_back(name);
}

bool UnitTestSuite::CompareName(const std::string & str)
{
	return name == str;
}

size_t NumTestsPassed(const std::vector<FUnitTestingOutcome> outcomes)
{
	size_t numPassed = 0;

	for (size_t i = 0; i < outcomes.size(); i++)
	{
		if (outcomes[i].success) numPassed++;
	}

	return numPassed;
}