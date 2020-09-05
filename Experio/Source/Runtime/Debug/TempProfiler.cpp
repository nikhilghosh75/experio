#include "TempProfiler.h"
#include <iostream>

TempProfiler::TempProfiler()
{
	start = FDateTime::NowHighRes();
	name = "Unnamed";
}

TempProfiler::TempProfiler(std::string s)
{
	start = FDateTime::NowHighRes();
	name = s;
}

TempProfiler::~TempProfiler()
{
	FDateTime end = FDateTime::NowHighRes();
	long long elapsed = (end - start).ticks;
	std::cout << "Process " << name << " took " << FDateTime::SecondsToString(elapsed) << " seconds" << std::endl;
}
