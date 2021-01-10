#include "EditorShortcuts.h"
#include "UndoSystem.h"
#include "../SceneView/SceneView.h"
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

	Shortcut switchToTranslate(EKeyCode::W);
	switchToTranslate.shortcutFunction = std::function<void()>([]() {
		if (SceneView::sceneView != nullptr)
		{
			SceneView::sceneView->SetEditMode(ESceneEditMode::Translate);
		}});
	Input::shortcuts.push_back(switchToTranslate);

	Shortcut switchToRotate(EKeyCode::E);
	switchToRotate.shortcutFunction = std::function<void()>([]() {
		if (SceneView::sceneView != nullptr)
		{
			SceneView::sceneView->SetEditMode(ESceneEditMode::Rotate);
		}});
	Input::shortcuts.push_back(switchToRotate);

	Shortcut switchToScale(EKeyCode::W);
	switchToScale.shortcutFunction = std::function<void()>([]() {
		if (SceneView::sceneView != nullptr)
		{
			SceneView::sceneView->SetEditMode(ESceneEditMode::Scale);
		}});
	Input::shortcuts.push_back(switchToScale);
}
