#include "TempProfiler.h"
#include <iostream>
using namespace std;

TempProfiler::TempProfiler()
{
	start = FDateTime::NowHighRes();
	name = "Unnamed";
}

TempProfiler::TempProfiler(string s)
{
	start = FDateTime::NowHighRes();
	name = s;
}

TempProfiler::~TempProfiler()
{
	FDateTime end = FDateTime::NowHighRes();
	long long elapsed = (end - start).ticks;
	cout << "Process " << name << " took " << FDateTime::SecondsToString(elapsed) << " seconds" << endl;
}
