#pragma once
#include <stdint.h>
#include "../Debug/Debug.h"

enum class EAudioSystemInitStatus : uint8_t
{
	InitFailed,
	NoSpeakers,
	Successful
};

class AudioSystem
{
public:
	static EAudioSystemInitStatus Initialize();

	static std::string GetDriverName();
};