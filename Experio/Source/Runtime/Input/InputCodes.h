#pragma once
#include <stdint.h>

#define PB_NUM_KEY_CODES 116

enum class EInputType : uint8_t
{
	Keyboard,
	Mouse,
	Gamepad,
	Joystick,
	Pen,
	Touchscreen
};

struct Inputmask
{
	uint16_t mask;

	operator uint16_t() const { return mask; }

	Inputmask()
	{
		this->mask = 63;
	}

	Inputmask(uint16_t mask)
	{
		this->mask = mask;
	}

	Inputmask(bool* arr)
	{
		for (uint8_t i = 0; i < 6; i++)
		{
			if (arr[i])
				SetBitTrue(i);
			else
				SetBitFalse(i);
		}
	}

	bool CompareInputType(EInputType inputType) const
	{
		return (mask & (1 << (uint8_t)inputType)) != 0;
	}

	void SetBitTrue(uint8_t bit)
	{
		this->mask = this->mask | (1 << bit);
	}

	void SetBitFalse(uint8_t bit)
	{
		this->mask = this->mask & (~(1 << bit));
	}

	void SetBitsTrue(uint8_t start = 0, uint8_t end = 64)
	{
		for (uint8_t i = start; i < end; i++)
		{
			this->mask = this->mask | (1 << i);
		}
	}

	void SetBitsFalse(uint8_t start = 0, uint8_t end = 64)
	{
		for (uint8_t i = start; i < end; i++)
		{
			this->mask = this->mask & (~(1 << i));
		}
	}

	static Inputmask AND(Inputmask i1, Inputmask i2)
	{
		return Inputmask(i1.mask & i2.mask);
	}

	void FillBoolArray(bool* arr) const
	{
		for (uint8_t i = 0; i < 6; i++)
		{
			arr[i] = CompareInputType((EInputType)i);
		}
	}
};

enum class EKeyCode
{
	None,
	Backspace,
	Delete,
	Tab,
	Clear,
	Return,
	Pause,
	Escape,
	Space, // 8
	KeypadZero,
	KeypadOne,
	KeypadTwo,
	KeypadThree,
	KeypadFour,
	KeypadFive,
	KeypadSix,
	KeypadSeven, // 16
	KeypadEight,
	KeypadNine,
	Period,
	Divide,
	Multiply,
	Minus,
	Plus,
	KeypadEnter, // 24
	Up,
	Down,
	Left,
	Right,
	Insert,
	Home,
	End,
	PageUp, // 32
	PageDown,
	F1,
	F2,
	F3,
	F4,
	F5,
	F6,
	F7, // 40
	F8,
	F9,
	F10,
	F11,
	F12,
	F13,
	F14,
	F15, // 48
	F16,
	F17,
	F18,
	F19,
	F20,
	AlphaZero,
	AlphaOne,
	AlphaTwo, // 56
	AlphaThree,
	AlphaFour,
	AlphaFive,
	AlphaSix,
	AlphaSeven,
	AlphaEight,
	AlphaNine,
	LeftBracket, // 64
	RightBracket,
	Backslash,
	Underscore,
	Equals,
	Comma,
	Other,
	Slash,
	A, // 72
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I, // 80
	J,
	K,
	L,
	M,
	N,
	O,
	P,
	Q, // 88
	R,
	S,
	T,
	U,
	V,
	W,
	X,
	Y, // 96
	Z,
	Tilde,
	Numlock,
	Capslock,
	Scrolllock,
	LeftShift,
	RightShift,
	LeftControl, // 104
	RightControl,
	LeftAlt,
	RightAlt,
	LeftCommand,
	RightCommand,
	LeftPlatform,
	RightPlatform,
	AltGr, // 112
	Print,
	Select,
	PrintScreen,
	Help
};

enum class EKeyStatus
{
	Pressed,
	PressedThisFrame,
	Released,
	ReleasedThisFrame
};

enum class EMouseButton
{
	Left,
	Middle,
	Right
};

enum class EMouseStatus
{
	Down,
	DownThisFrame,
	Up,
	UpThisFrame
};

enum class EGamepadButton
{
	None,
	DPadNorth,
	DPadSouth,
	DPadEast,
	DPadWest,
	ButtonNorth,
	ButtonSouth,
	ButtonEast,
	ButtonWest,
	LeftShoulder,
	RightShoulder,
	LeftTrigger,
	RightTrigger,
	Start,
	Select,
	LeftStick,
	RightStick
};

struct InputCode
{
	union
	{
		EKeyCode keycode;
		EGamepadButton gamepadButton;
	};
};