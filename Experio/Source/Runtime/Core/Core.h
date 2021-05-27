#pragma once

#ifdef PLATFORM_WINDOWS
	#ifdef BUILD_DLL
		#define ENGINE_API __declspec(dllexport)
	#else
		#define API __declspec(dllimport)
	#endif
#else
	#error Platform Not Supported
#endif

#define EXPERIO_BUILD_MAJOR 0
#define EXPERIO_BUILD_MINOR 15
#define EXPERIO_BUILD_PATCH 0
