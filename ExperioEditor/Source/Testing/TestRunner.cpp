#include "TestRunner.h"
#include <sstream>
#include "Runtime/Math/FColor.h"
#include "Runtime/Time/FDateTime.h"

TestRunner::TestRunner()
{
	this->category = EEditorModuleCategory::Testing;
	this->name = "Test Runner";
}

void TestRunner::Display()
{
	if (ImGui::Button("Run Tests"))
	{
		FDateTime startTime = FDateTime::Now();
		// Make multi-threaded
		this->outcomes = TestingManager::RunTests();
		FDateTime endTime = FDateTime::Now();
		this->testDuration = endTime - startTime;
		this->testNames = TestingManager::GetTestNames();
		this->testsRun = true;
	}

	ImGui::Text(("Tests Availible: " + std::to_string(TestingManager::GetNumTests())).c_str());

	if (!this->testsRun) return;

	if (this->testDuration > FDuration::microsecond)
	{
		ImGui::Text(FDuration::ToString(this->testDuration).c_str());
	}

	size_t numTests = this->outcomes.size();

	size_t numTestsPassed = NumTestsPassed(this->outcomes);
	for (int i = 0; i < numTests; i++)
	{
		if (this->outcomes[i].success)
		{
			ImGui::TextColored(FColor(0, 1, 0, 0), (this->testNames[i] + " (Passed)").c_str());
		}
		else
		{
			ImGui::TextColored(FColor(1, 0, 0, 0), (this->testNames[i] + " (Failed)").c_str());
		}

		if (ImGui::TreeNode("Details"))
		{
			for (int j = 0; j < this->outcomes[i].outcomes.size(); j++)
			{
				FAssertionOutcome& currentOutcome = this->outcomes[i].outcomes[j];
				std::string currentOutcomeName = this->outcomes[i].testNames[j];

				if (currentOutcome.status == EAssertionStatus::Success)
				{
					ImGui::TextColored(FColor(0, 1, 0, 0), (currentOutcomeName + " (Passed)").c_str());
				}
				else
				{
					std::stringstream ss;
					ss << currentOutcomeName << " (Failed) - Line Number: " << currentOutcome.lineNumber;
					ImGui::TextColored(FColor(1, 0, 0, 0), ss.str().c_str());
				}
			}
			ImGui::TreePop();
		}
	}
}
