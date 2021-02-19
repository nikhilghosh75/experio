#include "Profiler.h"
#include <thread>

// #define PB_DEBUG_PROFILER

#ifdef PB_DEBUG_PROFILER
#include <iostream>
#endif

static ProfilerManager manager;

ScopeProfiler::ScopeProfiler()
{
	category = EProfilerCategory::None;
	name[0] = '\0';
	start = FDateTime::NowHighRes();
}

ScopeProfiler::ScopeProfiler(const char * newName)
{
	category = EProfilerCategory::None;
	strcpy(name, newName);
	start = FDateTime::NowHighRes();
}

ScopeProfiler::ScopeProfiler(const char * newName, EProfilerCategory newCategory)
{
	category = newCategory;
	strcpy(name, newName);
	start = FDateTime::NowHighRes();
}

ScopeProfiler::~ScopeProfiler()
{
	End();
}

void ScopeProfiler::End()
{
	end = FDateTime::NowHighRes();

	uint8_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
	manager.Write(start.ticks, (end - start).ticks, name, category, threadID);

	FDateTime::SecondsToString((end - start).ticks);

#ifdef PB_DEBUG_PROFILER
	std::cout << "Process " << name << " took " << FDateTime::SecondsToString((end - start).ticks) << std::endl;
#endif
}

ProfilerManager::ProfilerManager()
{
	logFile.open("log.pblog");
	logFile << "GameStart: " << FDateTime::NowHighRes().ticks << std::endl;
}

ProfilerManager::~ProfilerManager()
{
	logFile.close();
}

void ProfilerManager::Write(const FProfileInfo & info)
{
	logFile << "Start: " << info.start << " Duration: " << info.duration << " Category: " << (uint16_t)info.category
		<< " Thread: " << info.threadID << " Name: " << info.name << std::endl;
}

void ProfilerManager::Write(long long start, long long duration, char * name, EProfilerCategory category, uint8_t threadID)
{
	logFile << "Start: " << start << " Duration: " << duration << " Category: " << (uint16_t)category
		<< " Thread: " << threadID << " Name: " << name << std::endl;
}
