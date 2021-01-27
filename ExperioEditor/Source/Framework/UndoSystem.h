#pragma once
#include "UndoCommand.h"
#include <vector>

class UndoSystem
{
public:
	static std::vector<UndoCommand*> undoStack;
	static std::vector<UndoCommand*> redoStack;

	static void AddCommand(UndoCommand* undoCommand);

	static void Undo();

	static void Redo();

	static void FlushCommands();
};