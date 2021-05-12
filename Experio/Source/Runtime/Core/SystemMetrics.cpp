#include "SystemMetrics.h"
#include <Windows.h>

#ifdef PLATFORM_WINDOWS

FResolution SystemMetrics::Resolution()
{
    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);
    return FResolution(width, height);
}

FVector2Int SystemMetrics::CursorDimensions()
{
    int cursorWidth = GetSystemMetrics(SM_CXCURSOR);
    int cursorHeight = GetSystemMetrics(SM_CYCURSOR);
    return FVector2Int(cursorWidth, cursorHeight);
}

#endif
