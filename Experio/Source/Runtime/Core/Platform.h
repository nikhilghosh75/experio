#pragma once

enum class EPlatform
{
	Windows,
	Mac,
	Linux
};

enum class EArchitecture
{
	x86,
	x64
};

#include <stdint.h>
#include <string>
#ifdef PLATFORM_WINDOWS
#include <Windows.h>
#endif

#ifdef PLATFORM_WINDOWS
	#define PLATFORM_DESKTOP
	#define OWNER_MICROSOFT
#elif defined PLATFORM_MAC
	#define PLATFORM_DESKTOP
	#define OWNER_APPLE
#elif defined PLATFORM_LINUX
	#define PLATFORM_DESKTOP
#endif

std::string GetVersionString();
uint32_t GetMajorVersion();
uint32_t GetMinorVersion();
uint32_t GetBuildVersion();