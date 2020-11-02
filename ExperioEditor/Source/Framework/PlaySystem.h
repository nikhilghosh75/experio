#pragma once

enum class EPlaySystemState
{
	NotPlaying,
	Paused,
	Playing
};

class PlaySystem
{
	static EPlaySystemState playSystemState;

public:
	static EPlaySystemState GetPlaySystemState() { return playSystemState; }

	static void StartGame();

	static void PauseGame();

	static void UnpauseGame();

	static void StopGame();
};