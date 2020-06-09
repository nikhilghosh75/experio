#pragma once
#include "../Time/FDateTime.h"
#include <string>
using namespace std;

class TempProfiler
{
	FDateTime start;
	string name;

public:
	TempProfiler();
	TempProfiler(string s);
	~TempProfiler();
};

#define PROFILE_SCOPE(__name) TempProfiler profiler(__name)