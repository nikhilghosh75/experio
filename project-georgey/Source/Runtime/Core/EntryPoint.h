#pragma once
#include "GApplication.h"

#include <stdio.h>

#ifdef PLATFORM_WINDOWS

extern GApplication* CreateApplication();

int main(int argc, char** argv)
{
	GApplication* app = CreateApplication();
	app->Run();
	delete app;
}

GApplication* CreateApplication();

#endif