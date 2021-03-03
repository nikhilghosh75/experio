#include "SystemMetrics.h"
#include <Windows.h>

#ifdef PLATFORM_WINDOWS

FResolution SystemMetrics::Resolution()
{
    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);
    return FResolution(width, height);
}

#endif
