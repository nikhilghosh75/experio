#pragma once
#include "../Time/FDateTime.h"
#include <string>

class TempProfiler
{
	FDateTime start;
	std::string name;

public:
	TempProfiler();
	TempProfiler(std::string s);
	~TempProfiler();
};

#define PROFILE_SCOPE(__name) TempProfiler profiler(__name)