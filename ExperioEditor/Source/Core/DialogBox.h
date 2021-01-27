#pragma once
#include <string>

enum EDialogBoxValue
{
	None,
	Abort,
	Cancel,
	Continue,
	Ignore,
	No,
	Ok,
	Retry,
	Try,
	Yes
};

enum class EDialogBoxIcon
{
	Asterisk,
	Error,
	Exclamation,
	Hand,
	Information,
	Mask,
	Question,
	Stop,
	Warning,
};

class EditorDialogBox
{
public:
	static EDialogBoxValue AbortRetryIgnore(std::string title, std::string content, EDialogBoxIcon icon = EDialogBoxIcon::Exclamation);
	static EDialogBoxValue CancelTryContinue(std::string title, std::string content, EDialogBoxIcon icon = EDialogBoxIcon::Exclamation);
	static EDialogBoxValue OkCancel(std::string title, std::string content, EDialogBoxIcon icon = EDialogBoxIcon::Exclamation);
	static EDialogBoxValue RetryCancel(std::string title, std::string content, EDialogBoxIcon icon = EDialogBoxIcon::Exclamation);
	static EDialogBoxValue YesNo(std::string title, std::string content, EDialogBoxIcon icon = EDialogBoxIcon::Exclamation);
	static EDialogBoxValue YesNoCancel(std::string title, std::string content, EDialogBoxIcon icon = EDialogBoxIcon::Exclamation);

private:
	static unsigned int IconToFlag(EDialogBoxIcon icon);
};