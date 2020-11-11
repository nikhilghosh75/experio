#include "GameView.h"
#include "Runtime/Core/Window.h"
#include "Runtime/Framework/Project.h"
#include "../Core/EditorWindow.h"
#include "../Framework/PlaySystem.h"

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

	this->playButtonImage = TextureManager::LoadTexture("C:/Users/debgh/source/repos/project-bloo/ExperioEditor/Resources/Textures/Play-Button.bmp");
	this->pauseButtonImage = TextureManager::LoadTexture("C:/Users/debgh/source/repos/project-bloo/ExperioEditor/Resources/Textures/Pause-Button.bmp");
	this->stopButtonImage = TextureManager::LoadTexture("C:/Users/debgh/source/repos/project-bloo/ExperioEditor/Resources/Textures/Stop-Button.bmp");

	renderer.currentMode = ERenderMode::ToCameraSystem;
}

void GameView::Display()
{
	renderer.MakeCurrent();

	ImVec2 currentSize = ImGui::GetWindowSize();
	currentSize = ImVec2(currentSize.x - 12, currentSize.y - 77);

	CreateMenu();

	FWindowData data = EditorWindow::GetWindowData();
	Framebuffer framebuffer(data.width, data.height);
	framebuffer.Bind();
	
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
}
