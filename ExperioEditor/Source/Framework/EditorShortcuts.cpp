#include "EditorShortcuts.h"
#include "PlaySystem.h"
#include "UndoSystem.h"
#include "../Core/UpperMenu.h"
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

	Shortcut play(EKeyCode::LeftControl, EKeyCode::P);
	play.shortcutFunction = std::function<void()>([]() {
		if (PlaySystem::GetPlaySystemState() == EPlaySystemState::NotPlaying)
			PlaySystem::StartGame();
		else
			PlaySystem::StopGame();
	});
	Input::shortcuts.push_back(play);

	Shortcut saveAll(EKeyCode::LeftControl, EKeyCode::S);
	saveAll.shortcutFunction = std::function<void()>([]() {	UpperMenu::SaveAll(); });
	Input::shortcuts.push_back(saveAll);
}
