#include "Platform.h"
#include <sstream>

#ifdef PLATFORM_WINDOWS
#pragma comment(lib, "version.lib" )

bool GetOSVersionString(char* version, size_t maxlen)
{
	/*
	char path[_MAX_PATH];
	if (!GetSystemDirectory(path, _MAX_PATH))
		return false;

	strcat_s(path, "\\kernel32.dll");

	//
	// Based on example code from this article
	// http://support.microsoft.com/kb/167597
	//

	DWORD handle;
#if (_WIN32_WINNT >= _WIN32_WINNT_VISTA)
	DWORD len = GetFileVersionInfoSizeExA(FILE_VER_GET_NEUTRAL, path, &handle);
#else
	DWORD len = GetFileVersionInfoSizeW(path, &handle);
#endif
	if (!len)
		return false;

	std::unique_ptr<uint8_t> buff(new (std::nothrow) uint8_t[len]);
	if (!buff)
		return false;

#if (_WIN32_WINNT >= _WIN32_WINNT_VISTA)
	if (!GetFileVersionInfoExA(FILE_VER_GET_NEUTRAL, path, 0, len, buff.get()))
#else
	if (!GetFileVersionInfoW(path, 0, len, buff.get()))
#endif
		return false;

	VS_FIXEDFILEINFO *vInfo = nullptr;
	UINT infoSize;

	if (!VerQueryValueW(buff.get(), L"\\", reinterpret_cast<LPVOID*>(&vInfo), &infoSize))
		return false;

	if (!infoSize)
		return false;

	sprintf_s(version, maxlen, "%u.%u.%u.%u",
		HIWORD(vInfo->dwFileVersionMS),
		LOWORD(vInfo->dwFileVersionMS),
		HIWORD(vInfo->dwFileVersionLS),
		LOWORD(vInfo->dwFileVersionLS));

		*/

	return true;
}

std::string GetVersionString()
{
	char versionString[32];
	GetOSVersionString(versionString, 32);

	return std::string(versionString);
}

uint32_t GetMajorVersion()
{
	DWORD version = 0;
	// DWORD version = GetVersion();
	return (DWORD)(LOBYTE(LOWORD(version)));
}

uint32_t GetMinorVersion()
{
	DWORD version = 0;
	// DWORD version = GetVersion();
	return (DWORD)(HIBYTE(LOWORD(version)));
}

uint32_t GetBuildVersion()
{
	DWORD version = 0;
	// DWORD version = GetVersion();
	DWORD build = 0;
	if (version < 0x80000000)
	{
		build = (DWORD)(HIWORD(version));
	}
	return build;
}
#endif