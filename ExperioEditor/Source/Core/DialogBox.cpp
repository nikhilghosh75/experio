#include "DialogBox.h"
#include "EditorWindow.h"
#include <Windows.h>

EDialogBoxValue EditorDialogBox::AbortRetryIgnore(std::string title, std::string content, EDialogBoxIcon icon)
{
#ifdef PLATFORM_WINDOWS
	unsigned int flags = MB_ABORTRETRYIGNORE | IconToFlag(icon);

	int msboxID = MessageBox(EditorWindow::GetHWND(), content.c_str(), title.c_str(), flags);

	if (msboxID == IDABORT) return EDialogBoxValue::Abort;
	if (msboxID == IDRETRY) return EDialogBoxValue::Retry;
	return EDialogBoxValue::Ignore;
#endif
	return EDialogBoxValue::None;
}

EDialogBoxValue EditorDialogBox::CancelTryContinue(std::string title, std::string content, EDialogBoxIcon icon)
{
#ifdef PLATFORM_WINDOWS
	unsigned int flags = MB_CANCELTRYCONTINUE | IconToFlag(icon);

	int msboxID = MessageBox(EditorWindow::GetHWND(), content.c_str(), title.c_str(), flags);

	if (msboxID == IDCANCEL) return EDialogBoxValue::Cancel;
	if (msboxID == IDTRYAGAIN) return EDialogBoxValue::Try;
	return EDialogBoxValue::Continue;
#endif
	return EDialogBoxValue::None;
}

EDialogBoxValue EditorDialogBox::OkCancel(std::string title, std::string content, EDialogBoxIcon icon)
{
#ifdef PLATFORM_WINDOWS
	unsigned int flags = MB_OKCANCEL | IconToFlag(icon);

	int msboxID = MessageBox(EditorWindow::GetHWND(), content.c_str(), title.c_str(), flags);

	if (msboxID == IDOK) return EDialogBoxValue::Ok;
	return EDialogBoxValue::Cancel;
#endif
	return EDialogBoxValue::None;
}

EDialogBoxValue EditorDialogBox::RetryCancel(std::string title, std::string content, EDialogBoxIcon icon)
{
#ifdef PLATFORM_WINDOWS
	unsigned int flags = MB_RETRYCANCEL | IconToFlag(icon);

	int msboxID = MessageBox(EditorWindow::GetHWND(), content.c_str(), title.c_str(), flags);

	if (msboxID == IDRETRY) return EDialogBoxValue::Retry;
	return EDialogBoxValue::Cancel;
#endif
	return EDialogBoxValue::None;
}

EDialogBoxValue EditorDialogBox::YesNo(std::string title, std::string content, EDialogBoxIcon icon)
{
#ifdef PLATFORM_WINDOWS
	unsigned int flags = MB_YESNO | IconToFlag(icon);

	int msboxID = MessageBox(EditorWindow::GetHWND(), content.c_str(), title.c_str(), flags);

	if (msboxID == IDYES) return EDialogBoxValue::Yes;
	return EDialogBoxValue::No;
#endif
	return EDialogBoxValue::None;
}

EDialogBoxValue EditorDialogBox::YesNoCancel(std::string title, std::string content, EDialogBoxIcon icon)
{
#ifdef PLATFORM_WINDOWS
	unsigned int flags = MB_YESNOCANCEL | IconToFlag(icon);

	int msboxID = MessageBox(EditorWindow::GetHWND(), content.c_str(), title.c_str(), flags);

	if (msboxID == IDYES) return EDialogBoxValue::Yes;
	else if (msboxID == IDNO) return EDialogBoxValue::No;
	return EDialogBoxValue::Cancel;
#endif
	return EDialogBoxValue::None;
}

unsigned int EditorDialogBox::IconToFlag(EDialogBoxIcon icon)
{
	switch (icon)
	{
	case EDialogBoxIcon::Asterisk: return MB_ICONASTERISK;
	case EDialogBoxIcon::Error: return MB_ICONERROR;
	case EDialogBoxIcon::Exclamation: return MB_ICONEXCLAMATION;
	case EDialogBoxIcon::Hand: return MB_ICONHAND;
	case EDialogBoxIcon::Information: return MB_ICONINFORMATION;
	case EDialogBoxIcon::Mask: return MB_ICONMASK;
	case EDialogBoxIcon::Question: return MB_ICONQUESTION;
	case EDialogBoxIcon::Stop: return MB_ICONSTOP;
	case EDialogBoxIcon::Warning: return MB_ICONWARNING;
	}
	return 0;
}
