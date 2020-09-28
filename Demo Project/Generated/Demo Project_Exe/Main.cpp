#include "../../Demo Project/Source/DemoProject.h"
#include <windows.h> 
#include <stdio.h>
#include <iostream>

typedef void(__cdecl *MYPROC)();

void SetupProject();
void RunProject();

int main(int argc, char** argv)
{
	SetupProject();
	RunProject();
	return 0;
}