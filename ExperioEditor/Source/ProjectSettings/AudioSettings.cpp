#include "AudioSettings.h"
#include "../Core/EditorApplication.h"

AudioSettings* AudioSettings::settings;

AudioSettings::AudioSettings()
{
	this->settingsFile = "audio.pbconfig";
	settings = this;
}

void AudioSettings::ReadFromTable(toml::table table)
{
}

void AudioSettings::GenerateSettingsFile()
{
}

void AudioSettings::SaveSettingsFile()
{
}

TTypedTree<std::string>* AudioSettings::DisplayMenu()
{
	TTypedTree<std::string>* tree = new TTypedTree<std::string>("Audio");
	return tree;
}

void AudioSettings::DisplaySettings(const std::string& displayCategory)
{
	if (displayCategory == "Audio")
	{
		ImGui::Text("Audio Settings have not been implemented yet");
	}
}
