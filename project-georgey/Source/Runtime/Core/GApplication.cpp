#include "GApplication.h"
#include "GWindow.h"
#include <iostream>
#include "../Debug/TempProfiler.h"
using namespace std;

GApplication::GApplication()
{
}


GApplication::~GApplication()
{
}

void GApplication::Run()
{
	TempProfiler* windowProfiler = new TempProfiler();
	GWindow newWindow;
	newWindow.InstantiateWindow();
	delete windowProfiler;
	while (newWindow.isActive)
	{
		newWindow.OnUpdate();
	}
	cin.get();
}
