#include "../Demo Project/Source/DemoProject.h"
#include <windows.h> 
#include <stdio.h>
#include <iostream>

typedef void(__cdecl *MYPROC)();

int main(int argc, char** argv)
{
	HINSTANCE hinstLib;
	MYPROC ProcSetup, ProcRun;

	hinstLib = LoadLibrary(TEXT("Demo Project.dll"));

	if (hinstLib != NULL)
	{
		ProcSetup = (MYPROC)GetProcAddress(hinstLib, "SetupProject");

		if (NULL != ProcSetup)
		{
			(ProcSetup)();
			ProcRun = (MYPROC)GetProcAddress(hinstLib, "RunProject");
			if (ProcRun != NULL)
			{
				(ProcRun)();
			}
		}
		else
		{
			auto error = GetLastError();
			printf("%i\n", error);
		}

		FreeLibrary(hinstLib);
	}
	else
	{
		printf("Linking failed");
	}
	return 0;
}