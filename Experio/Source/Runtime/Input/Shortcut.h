#pragma once
#include "InputCodes.h"
#include <functional>

#define PB_MAX_SHORTCUT_KEYCODES 4

class Shortcut
{
public:
	EKeyCode keycodes[PB_MAX_SHORTCUT_KEYCODES];
	std::function<void()> shortcutFunction;

	Shortcut()
	{
		for (int i = 0; i < PB_MAX_SHORTCUT_KEYCODES; i++)
			keycodes[i] = EKeyCode::None;
	}

	Shortcut(EKeyCode keyCode1)
	{
		keycodes[0] = keyCode1;

		for (int i = 1; i < PB_MAX_SHORTCUT_KEYCODES; i++)
			keycodes[i] = EKeyCode::None;
	}

	Shortcut(EKeyCode keycode1, EKeyCode keycode2)
	{
		keycodes[0] = keycode1;
		keycodes[1] = keycode2;

		for (int i = 2; i < PB_MAX_SHORTCUT_KEYCODES; i++)
			keycodes[i] = EKeyCode::None;
	}

	EKeyCode& operator[](uint8_t index) { return keycodes[index]; }
};