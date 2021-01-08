#include "EditorShortcuts.h"
#include "UndoSystem.h"
#include "Runtime/Debug/Debug.h"
#include "Runtime/Input/Input.h"

void EditorShortcuts::Initialize()
{
	Shortcut undo(EKeyCode::LeftControl, EKeyCode::Z);
	undo.shortcutFunction = std::function<void()>([]() { UndoSystem::Undo(); });
	Input::shortcuts.push_back(undo);

	Shortcut redo(EKeyCode::LeftControl, EKeyCode::X);
	redo.shortcutFunction = std::function<void()>([]() { UndoSystem::Redo(); });
	Input::shortcuts.push_back(redo);

	// Add Copy and Paste here

	// Add Scene Controls Here
}
