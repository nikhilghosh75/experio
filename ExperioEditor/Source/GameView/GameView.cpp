#include "GameView.h"
#include "Runtime/Core/Window.h"
#include "Runtime/Debug/Profiler.h"
#include "Runtime/Framework/Project.h"
#include "Runtime/Math/ColorPalette.h"
#include "Runtime/Math/LMath.h"
#include "../Core/EditorApplication.h"
#include "../Core/EditorWindow.h"
#include "../Framework/PlaySystem.h"

GameView* GameView::gameView;

void GameView::CreateMenu()
{
	if (ImGui::ImageButton((void*)playButtonImage->GetRendererID(), ImVec2(32, 32)))
	{
		if (PlaySystem::GetPlaySystemState() == EPlaySystemState::NotPlaying)
		{
			PlaySystem::StartGame();
		}
		else
		{
			PlaySystem::UnpauseGame();
		}
	}
	ImGui::SameLine();
	if (ImGui::ImageButton((void*)pauseButtonImage->GetRendererID(), ImVec2(32, 32)))
	{
		PlaySystem::PauseGame();
	}
	ImGui::SameLine();
	if (ImGui::ImageButton((void*)stopButtonImage->GetRendererID(), ImVec2(32, 32)))
	{
		PlaySystem::StopGame();
	}
}

GameView::GameView()
{
	this->name = "Game View";
	this->category = EEditorModuleCategory::Core;

	this->playButtonImage = TextureManager::LoadTexture(EditorApplication::experioEditorFilePath + "/Resources/Textures/Play-Button.bmp");
	this->pauseButtonImage = TextureManager::LoadTexture(EditorApplication::experioEditorFilePath + "/Resources/Textures/Pause-Button.bmp");
	this->stopButtonImage = TextureManager::LoadTexture(EditorApplication::experioEditorFilePath + "/Resources/Textures/Stop-Button.bmp");
	this->locked = false;

	renderer.currentMode = ERenderMode::ToCameraSystem;

	FWindowData data = EditorWindow::GetWindowData();
	this->framebuffer = Framebuffer(data.width, data.height);
	this->lastSize = ImVec2(0, 0);

	gameView = this;
}

void GameView::Display()
{
	PROFILE_SCOPE("GameView::Display");

	if (locked)
	{
		ImGui::Text("Scene Editing is currently locked");
		return;
	}

	renderer.MakeCurrent();
	renderer.SetCull(true);

	CreateMenu();

	ImVec2 currentPosition = ImGui::GetCursorScreenPos();
	ImVec2 currentSize = ImGui::GetContentRegionAvail();
	FRect rect = FRect(currentPosition, (FVector2)currentPosition + (FVector2)currentSize);
	Input::SetGameRect(rect);

	if (!LMath::ApproxEquals(currentSize.x, lastSize.x, 2) || !LMath::ApproxEquals(currentSize.y, lastSize.y, 2))
	{
		framebuffer.SetSpec((unsigned int)currentSize.x, (unsigned int)currentSize.y);
	}
	framebuffer.Bind();
	renderer.SetViewport(0, 0, currentSize.x, currentSize.y);
	renderer.ClearColor(ColorPalette::Black);
	renderer.Clear();
	
	if (PlaySystem::GetPlaySystemState() == EPlaySystemState::NotPlaying)
	{
		Project::componentManager->RenderScene();
	}
	else
	{
		Project::componentManager->Update();
	}

	framebuffer.Unbind();

	ImGui::Image((void*)framebuffer.GetColorAttachment(), currentSize, ImVec2(0, 1), ImVec2(1, 0));

	lastSize = currentSize;
}

void GameView::Lock()
{
	locked = true;
}

void GameView::Unlock()
{
	locked = false;
}
