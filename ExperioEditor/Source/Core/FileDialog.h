#pragma once
#include <string>
#include <vector>

struct FFileDialogInfo
{
	std::string filename = "";
	bool canceled = false;

	FFileDialogInfo();
	FFileDialogInfo(const std::string& filename, bool canceled = false);

	bool IsValid() const;

	operator bool();
};

class FileDialog
{
public:
	// Restructure Dialog
	static FFileDialogInfo OpenFile(const char* filter);

	static std::vector<FFileDialogInfo> OpenMultipleFiles(const char* filter);

	static FFileDialogInfo OpenFolder();

	static FFileDialogInfo SaveFile(const char* filter);
};