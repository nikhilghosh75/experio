#pragma once

class UpperMenu
{
public:
	static void CreateUpperMenu();
private:
	static void CreateFileMenu();

	static void CreateEditMenu();

	static void CreateAssetMenu();

	static void CreateProjectMenu();

	static void CreateWindowMenu();

public:
	static void SaveAll();
};