#include "FileDialog.h"
#include "EditorWindow.h"
#include <Windows.h>
#include <commdlg.h>
#include <CommCtrl.h>
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
	std::cout << "OPEN FOLDER" << std::endl;

#ifdef PLATFORM_WINDOWS
	OPENFILENAMEA ofn;
	CHAR szFile[260] = { 0 };

	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = EditorWindow::GetHWND();
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "Folder\0qqqqqqqqqqqqqqq.qqqqqqqqq\0";
	ofn.nFilterIndex = 1;
	ofn.Flags = OFN_EXPLORER | OFN_NOCHANGEDIR | OFN_ENABLESIZING | OFN_DONTADDTORECENT;
	ofn.lpfnHook = (LPOFNHOOKPROC)DialogHookProc;
	// ofn.Flags = OFN_ENABLEHOOK | OFN_HIDEREADONLY | OFN_EXPLORER | OFN_NOCHANGEDIR | OFN_ENABLESIZING | OFN_DONTADDTORECENT;
	// ofn.lpstrDefExt = "";

	if (GetOpenFileNameA(&ofn) == TRUE)
	{
		return FFileDialogInfo(ofn.lpstrFile);
	}
#endif
	return FFileDialogInfo();
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

/*
LRESULT CALLBACK OFNFolderProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// if the OK button is pressed
	if (uMsg == WM_COMMAND && HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) == IDOK) {

		bool valid = false;

		HWND list = GetDlgItem(GetDlgItem(hWnd, lst2), 1);
		int idx = ListView_GetNextItem(list, -1, LVNI_SELECTED);
		if (GetWindowTextLength(GetDlgItem(hWnd, cmb13)) > 0) {
			// the file name box is not empty
			// use the default processing, which will open the folder with that name
			CallWindowProc(g_OldOFNFolderProc, hWnd, uMsg, wParam, lParam);
			// then clear the text
			SetDlgItemText(hWnd, cmb13, "");
			return TRUE;
		}
		else if (idx >= 0) {
			// if a folder is selected in the list view, its user data is a PIDL
			// get the full folder name as described here: http://msdn.microsoft.com/msdnmag/issues/03/09/CQA/
			LVITEM item = { LVIF_PARAM,idx,0 };
			ListView_GetItem(list, &item);

			int len = SendMessage(hWnd, CDM_GETFOLDERIDLIST, 0, NULL);
			if (len > 0) {
				LPMALLOC pMalloc;
				SHGetMalloc(&pMalloc);
				LPCITEMIDLIST pidlFolder = (LPCITEMIDLIST)pMalloc->Alloc(len);
				SendMessage(hWnd, CDM_GETFOLDERIDLIST, len, (LPARAM)pidlFolder);

				STRRET str = { STRRET_WSTR };

				IShellFolder *pDesktop, *pFolder;
				SHGetDesktopFolder(&pDesktop);
				if (SUCCEEDED(pDesktop->BindToObject(pidlFolder, NULL, IID_IShellFolder, (void**)&pFolder))) {
					if (FAILED(pFolder->GetDisplayNameOf((LPITEMIDLIST)item.lParam, SHGDN_FORPARSING, &str)))
						str.pOleStr = NULL;
					pFolder->Release();
					pDesktop->Release();
				}
				else {
					if (FAILED(pDesktop->GetDisplayNameOf((LPITEMIDLIST)item.lParam, SHGDN_FORPARSING, &str)))
						str.pOleStr = NULL;
					pDesktop->Release();
				}

				if (str.pOleStr) {
					DWORD attrib = GetFileAttributesW(str.pOleStr);
					if (attrib != INVALID_FILE_ATTRIBUTES && (attrib&FILE_ATTRIBUTE_DIRECTORY)) {
#ifdef _UNICODE
						wcsncpy(g_Path, str.pOleStr, _MAX_PATH);
#else
						WideCharToMultiByte(CP_ACP, 0, str.pOleStr, -1, g_Path, _MAX_PATH, NULL, NULL);
#endif
						g_Path[_MAX_PATH - 1] = 0;
						valid = true;
					}
					pMalloc->Free(str.pOleStr);
				}

				pMalloc->Free((void*)pidlFolder);
				pMalloc->Release();
			}
		}
		else {
			// no item is selected, use the current folder
			TCHAR path[_MAX_PATH];
			SendMessage(hWnd, CDM_GETFOLDERPATH, _MAX_PATH, (LPARAM)path);
			DWORD attrib = GetFileAttributes(path);
			if (attrib != INVALID_FILE_ATTRIBUTES && (attrib&FILE_ATTRIBUTE_DIRECTORY)) {
				_tcscpy(g_Path, path);
				valid = true;
			}
		}
		if (valid) {
			EndDialog(hWnd, IDOK);
			return TRUE;
		}
	}

	if (uMsg == WM_SHOWWINDOW && wParam && g_Placement)
		SetWindowPos(hWnd, NULL, g_Placement->left, g_Placement->top, g_Placement->right - g_Placement->left, g_Placement->bottom - g_Placement->top, SWP_NOZORDER);

	if (uMsg == WM_DESTROY && g_Placement)
		GetWindowRect(hWnd, g_Placement);

	return CallWindowProc(g_OldOFNFolderProc, hWnd, uMsg, wParam, lParam);
}

UINT OFNFolderHook(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_INITDIALOG) {
		HWND hWnd = GetParent(hDlg);
		SendMessage(hWnd, CDM_HIDECONTROL, stc2, 0); // hide "Save as type"
		SendMessage(hWnd, CDM_HIDECONTROL, cmb1, 0); // hide the filter combo box
		SendMessage(hWnd, CDM_SETCONTROLTEXT, IDOK, (LPARAM)"Select");
		SendMessage(hWnd, CDM_SETCONTROLTEXT, stc3, (LPARAM)"Folder Name:");
		g_OldOFNFolderProc = (WNDPROC)SetWindowLong(hWnd, GWLP_WNDPROC, (LONG)OFNFolderProc);

		if (g_Placement && (g_Placement->top >= g_Placement->bottom)) {
			// the first time center the dialog relative to its parent
			RECT rc1, rc2;
			HWND parent = GetParent(hWnd);
			if (parent) {
				GetClientRect(parent, &rc1);
				MapWindowPoints(parent, NULL, (POINT*)&rc1, 2);
			}
			else
				GetWindowRect(GetDesktopWindow(), &rc1);
			GetWindowRect(hWnd, &rc2);
			int x = rc1.left + ((rc1.right - rc1.left) - (rc2.right - rc2.left)) / 2;
			int y = rc1.top + ((rc1.bottom - rc1.top) - (rc2.bottom - rc2.top)) / 2;
			if (x < rc1.left) x = rc1.left;
			if (y < rc1.top) y = rc1.top;
			g_Placement->left = x;
			g_Placement->top = y;
			g_Placement->right = x + (rc2.right - rc2.left);
			g_Placement->bottom = y + (rc2.bottom - rc2.top);
		}

		return 1;
	}

	if (uMsg == WM_NOTIFY && ((NMHDR*)lParam)->code == CDN_FILEOK) {
		// reject all files when the OK button is pressed
		// this will stop the dialog from closing
		SetWindowLong(hDlg, 0, TRUE);
		return TRUE;
	}

	return 0;
}
*/
#endif