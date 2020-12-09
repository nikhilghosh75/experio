#pragma once
#include "Assert.h"
#include <functional>
#include <vector>

struct FUnitTestingOutcome
{
	bool success;
	std::vector<std::string> testNames;
	std::vector<FAssertionOutcome> outcomes;
};

class UnitTestSuite;
void RegisterUnitTestSuite(UnitTestSuite* suite);
void RegisterUnitTest(std::function<FAssertionOutcome(void)> func, std::string name, std::string category);

class UnitTestSuite
{
	std::string name;
	std::string category;
public:
	UnitTestSuite();
	UnitTestSuite(std::string name, std::string category);

	std::vector<std::function<FAssertionOutcome(void)>> testFunctions;
	std::vector<std::string> testFunctionNames;
	
	FUnitTestingOutcome RunTests();

	void RegisterTest(std::function<FAssertionOutcome(void)> func, std::string name);

	bool CompareName(const std::string& str);
};

class UnitTestRegisterer
{
public:
	UnitTestRegisterer(std::function<FAssertionOutcome(void)> func, std::string name, std::string category)
	{
		RegisterUnitTest(func, name, category);
	}
};

#define TEST_SUITE(_name_, _category_) UnitTestSuite suite(_name_, _category_);

#define TEST_END() return FAssertionOutcome(EAssertionStatus::Success, "", __FILE__, __LINE__);

#define UNIT_TEST(_name_, _category_) \
FAssertionOutcome _name_(); \
UnitTestRegisterer Register##_name_(##_name_, (#_name_), _category_);\
FAssertionOutcome _name_()
