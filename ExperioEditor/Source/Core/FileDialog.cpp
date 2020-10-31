#include "FileDialog.h"
#include "EditorWindow.h"
#include <Windows.h>
#include <commdlg.h>

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
