#pragma once
#include "Terminal.h"

// Asset Commands
int NumAssets(const std::vector<std::string>& args);

// Code Analysis Commands
int CodeStats(const std::vector<std::string>& args);

// Scene Commands
int LoadScene(const std::vector<std::string>& args);

// Screen Commands
int Resolution(const std::vector<std::string>& args);

// Size Commands
int SizeOf(const std::vector<std::string>& args);

// Value Commands
int AddLayer(const std::vector<std::string>& args);
int AddTag(const std::vector<std::string>& args);