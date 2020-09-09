#pragma once

// Add Platform Specific Preprocessor Macros here

#ifdef PLATFORM_WINDOWS
	#define PLATFORM_DESKTOP
#elif defined PLATFORM_MAC
	#define PLATFORM_DESKTOP
#elif defined PLATFORM_LINUX
	#define PLATFORM_DESKTOP
#endif

