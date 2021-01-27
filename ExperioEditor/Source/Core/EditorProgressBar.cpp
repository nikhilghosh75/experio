#include "EditorProgressBar.h"
#include "EditorWindow.h"
#include <CommCtrl.h>

EditorProgressBar::EditorProgressBar()
{
	
}

EditorProgressBar::EditorProgressBar(unsigned int numSteps, std::string name)
{
	SetupBar(numSteps, name);
}

EditorProgressBar::~EditorProgressBar()
{
	Close();
}

void EditorProgressBar::SetupBar(unsigned int numSteps, std::string name)
{
	RECT rcClient;
	int cyVScroll;

	HWND hwnd = EditorWindow::GetHWND();
	GetClientRect(hwnd, &rcClient);
	cyVScroll = GetSystemMetrics(SM_CYVSCROLL);

	this->hwndPB = CreateWindowEx(0, PROGRESS_CLASS, name.c_str(),
		WS_CHILD | WS_VISIBLE, rcClient.left, rcClient.bottom - cyVScroll,
		rcClient.right, cyVScroll, hwnd, (HMENU)0, NULL, NULL);

	SendMessage(hwndPB, PBM_SETRANGE, 0, MAKELPARAM(0, numSteps));
	SendMessage(hwndPB, PBM_SETSTEP, (WPARAM)1, 0);

	open = true;
}

void EditorProgressBar::Step()
{
	SendMessage(hwndPB, PBM_STEPIT, 0, 0);
}

void EditorProgressBar::Step(unsigned int steps)
{
	for (size_t i = 0; i < steps; i++)
	{
		SendMessage(hwndPB, PBM_STEPIT, 0, 0);
	}
}

void EditorProgressBar::Close()
{
	if (open)
	{
		DestroyWindow(hwndPB);
		open = false;
	}
}
