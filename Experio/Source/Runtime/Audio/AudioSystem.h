#pragma once
#include <stdint.h>
#include "../Debug/Debug.h"

/// <summary>
/// The system that manages the game's audio, including the initization and shutdown.
/// </summary>

enum class EAudioSystemInitStatus : uint8_t
{
	InitFailed,
	IrrKlangNotFound,
	NoSpeakers,
	Successful
};

class AudioSystem
{
public:
	static EAudioSystemInitStatus Initialize();

	static std::string GetDriverName();
};