#include "UndoSystem.h"

std::vector<UndoCommand*> UndoSystem::undoStack;
std::vector<UndoCommand*> UndoSystem::redoStack;

void UndoSystem::AddCommand(UndoCommand * undoCommand)
{
	undoStack.push_back(undoCommand);
}

void UndoSystem::Undo()
{
	if (undoStack.size() == 0) return;

	redoStack.push_back(undoStack[undoStack.size() - 1]);
	undoStack.pop_back();

	redoStack[redoStack.size() - 1]->Unexecute();
}

void UndoSystem::Redo()
{
	if (redoStack.size() == 0) return;

	undoStack.push_back(redoStack[redoStack.size() - 1]);
	redoStack.pop_back();

	undoStack[undoStack.size() - 1]->Execute();
}

void UndoSystem::FlushCommands()
{
	for (size_t i = 0; i < undoStack.size(); i++)
	{
		delete undoStack[i];
	}
	undoStack.clear();

	for (size_t i = 0; i < redoStack.size(); i++)
	{
		delete redoStack[i];
	}
	redoStack.clear();
}

