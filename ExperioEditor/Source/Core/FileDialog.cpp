#include "FileDialog.h"
#include "EditorWindow.h"
#include "ThirdParty/Native File Dialog/include/nfd.h"
#include <Windows.h>
#include <commdlg.h>
#include <iostream>

#ifdef PLATFORM_WINDOWS
UINT DialogHookProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

static WNDPROC g_OldOFNFolderProc;
static TCHAR *g_Path;
static RECT *g_Placement;
#endif

FFileDialogInfo::FFileDialogInfo()
{
	this->filename = "";
	this->canceled = false;
}

FFileDialogInfo::FFileDialogInfo(const std::string & filename, bool canceled)
{
	this->filename = filename;
	this->canceled = canceled;
}

bool FFileDialogInfo::IsValid() const
{
	return !this->canceled && this->filename.size() != 0;
}

FFileDialogInfo::operator bool()
{
	return IsValid();
}


FFileDialogInfo FileDialog::OpenFile(const char * filter)
{
#ifdef PLATFORM_WINDOWS
	OPENFILENAMEA ofn;
	CHAR szFile[260] = { 0 };

	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = EditorWindow::GetHWND();
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = filter;
	ofn.nFilterIndex = 1;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

	if (GetOpenFileNameA(&ofn) == TRUE)
	{
		return FFileDialogInfo(ofn.lpstrFile);
	}
#endif
	return FFileDialogInfo("", true);
}

FFileDialogInfo FileDialog::OpenFolder()
{
#ifdef PLATFORM_WINDOWS
	char* outPath = nullptr;
	nfdresult_t result = NFD_PickFolder(nullptr, &outPath);
	if (result == NFD_OKAY)
	{
		return FFileDialogInfo(outPath);
	}
#endif
	return FFileDialogInfo("", true);
}

FFileDialogInfo FileDialog::SaveFile(const char * filter)
{
#ifdef PLATFORM_WINDOWS
	OPENFILENAMEA ofn;
	CHAR szFile[260] = { 0 };

	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = EditorWindow::GetHWND();
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = filter;
	ofn.nFilterIndex = 1;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

	if (GetSaveFileNameA(&ofn) == TRUE)
	{
		return FFileDialogInfo(ofn.lpstrFile);
	}
#endif
	return FFileDialogInfo("", true);
}

#ifdef PLATFORM_WINDOWS
UINT DialogHookProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	std::cout << msg << std::endl;
	return 0;
}

#endif