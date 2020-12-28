#include "ExperioTests.h"

std::vector<FUnitTestingOutcome> RunExperioTests()
{
	std::vector<FUnitTestingOutcome> outcomes;
	
	outcomes.push_back(RunVector3Tests());
	outcomes.push_back(RunLMathTests());

	return outcomes;
}