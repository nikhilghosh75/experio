#pragma once
#include "../Time/FDateTime.h"
#include <string>
#include <fstream>

enum class EProfilerCategory
{
	None,
	Container,
	Math,
	Files,
	Rendering
};

class ScopeProfiler
{
	FDateTime start;
	FDateTime end;
	char name[32];
	EProfilerCategory category;

public:
	ScopeProfiler();
	ScopeProfiler(const char* name);
	ScopeProfiler(const char* name, EProfilerCategory category);

	~ScopeProfiler();

	void End();
};

struct FProfileInfo
{
	long long start;
	long long duration;
	char name[32];
	EProfilerCategory category;
	uint8_t threadID;
};

class ProfilerManager
{
	std::ofstream logFile;

public:
	ProfilerManager();

	~ProfilerManager();

	void Write(const FProfileInfo& info);

	void Write(long long start, long long duration, char* name, EProfilerCategory category, uint8_t threadID);
};

#ifdef EXPERIO_DEBUG
#define PROFILE_SCOPE(__name__) ScopeProfiler __nameProfiler(__name__)
#define PROFILE_SCOPE_CATEGORY(__name__, __category__) ScopeProfiler __name__Profiler(__name__, __category__)
#else
#define PROFILE_SCOPE(__name)
#define PROFILE_SCOPE_CATEGORY(__name__, __category__)
#endif