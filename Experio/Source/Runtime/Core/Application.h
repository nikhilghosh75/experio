#pragma once
#include "Core.h"

/// <summary>
/// A class representing an Application
/// Meant only for the Project, not the Editor
/// </summary>

class Application
{
public:
	Application();
	virtual ~Application();

	void Run();
};

