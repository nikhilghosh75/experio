#pragma once
#include <string>

struct FFileDialogInfo
{
	std::string filename = "";
	bool canceled = false;

	FFileDialogInfo();
	FFileDialogInfo(const std::string& filename, bool canceled = false);

	bool IsValid() const;
};

class FileDialog
{
public:
	// Restructure Dialog
	static FFileDialogInfo OpenFile(const char* filter);
	static FFileDialogInfo OpenFolder();

	static FFileDialogInfo SaveFile(const char* filter);
};