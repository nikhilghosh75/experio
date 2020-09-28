#pragma once
#include "Core.h"
#include <string>
#include <Windows.h>
#include <thread>
#include "../Debug/Debug.h"

typedef void(__cdecl *VOIDPROC)();

class DllLoader
{
#ifdef PLATFORM_WINDOWS
	HINSTANCE hinstLib;
#endif // PLATFORM_WINDOWS

public:
	DllLoader()
	{
#ifdef PLATFORM_WINDOWS
		hinstLib = NULL;
#endif // PLATFORM_WINDOWS
	}

	DllLoader(std::string filePath)
	{
#ifdef PLATFORM_WINDOWS
		hinstLib = LoadLibrary(TEXT(filePath.c_str()));

		if (hinstLib == NULL)
		{
			Debug::LogError("Dll could not be loaded");
		}
#endif
	}

	~DllLoader()
	{
#ifdef PLATFORM_WINDOWS
		if (hinstLib != NULL)
		{
			FreeLibrary(hinstLib);
		}
#endif // PLATFORM_WINDOWS
	}

	void LoadDll(std::string filePath)
	{
#ifdef PLATFORM_WINDOWS
		hinstLib = LoadLibrary(TEXT(filePath.c_str()));

		if (hinstLib == NULL)
		{
			Debug::LogError("Dll could not be loaded");
		}
#endif // PLATFORM_WINDOWS
	}

	void UnloadDll()
	{
#ifdef PLATFORM_WINDOWS
		if (hinstLib != NULL)
		{
			FreeLibrary(hinstLib);
		}
#endif // PLATFORM_WINDOWS
	}

	bool CallFunction(std::string functionName)
	{
#ifdef PLATFORM_WINDOWS
		VOIDPROC proc = (VOIDPROC)GetProcAddress(hinstLib, functionName.c_str());

		if (proc != NULL)
		{
			(proc)();
		}
		return proc != NULL;
#endif
	}

	template <typename ReturnType, typename ProcType, typename... Args>
	bool CallFunction(std::string functionName, ReturnType& returnValue, Args ... args)
	{
		ProcType proc = (ProcType)GetProcAddress(hinstLib, functionName.c_str());
		if (proc != NULL)
		{
			returnValue = (proc)(args ...);
		}
		return proc != NULL;
	}

	template <typename ProcType, typename... Args>
	bool CallVoidFunction(std::string functionName, Args ... args)
	{
		ProcType proc = (ProcType)GetProcAddress(hinstLib, functionName.c_str());
		if (proc != NULL)
		{
			(proc)(args ...);
		}
		return proc != NULL;
	}

	void CallFunctionAsync(std::string functionName)
	{
		//std::thread worker(&DllLoader::CallFunction, this, functionName);
		//worker.detach();
	}
};

typedef void(__cdecl *VOIDHWNDPROC)(HWND);
typedef void(__cdecl *VOIDINT2PROC)(int, int);
typedef void(__cdecl *VOIDSTRINGPROC)(std::string);
typedef void(__cdecl *VOIDSTRINGINTPROC)(std::string, int);
typedef bool(__cdecl *BOOLSTRINGINTPROC)(std::string, int);