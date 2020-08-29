#pragma once
#include "../Math/FVector2.h"

#define PB_NUM_KEY_CODES 116

enum class EInputType
{
	Keyboard,
	Mouse
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
	Space,
	KeypadZero,
	KeypadOne,
	KeypadTwo,
	KeypadThree,
	KeypadFour,
	KeypadFive,
	KeypadSix,
	KeypadSeven,
	KeypadEight,
	KeypadNine,
	Period,
	Divide,
	Multiply,
	Minus,
	Plus,
	KeypadEnter,
	Up,
	Down,
	Left,
	Right,
	Insert,
	Home,
	End,
	PageUp,
	PageDown,
	F1,
	F2,
	F3,
	F4,
	F5,
	F6,
	F7,
	F8,
	F9,
	F10,
	F11,
	F12,
	F13,
	F14,
	F15,
	F16,
	F17,
	F18,
	F19,
	F20,
	AlphaZero,
	AlphaOne,
	AlphaTwo,
	AlphaThree,
	AlphaFour,
	AlphaFive,
	AlphaSix,
	AlphaSeven,
	AlphaEight,
	AlphaNine,
	LeftBracket,
	RightBracket,
	Backslash,
	Underscore,
	Equals,
	Comma,
	Other,
	Slash,
	A,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P,
	Q,
	R,
	S,
	T,
	U,
	V,
	W,
	X,
	Y,
	Z,
	Tilde,
	Numlock,
	Capslock,
	Scrolllock,
	LeftShift,
	RightShift,
	LeftControl,
	RightControl,
	LeftAlt,
	RightAlt,
	LeftCommand,
	RightCommand,
	LeftPlatform,
	RightPlatform,
	AltGr,
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

class Input
{
private:
	static EKeyStatus keyStatuses[PB_NUM_KEY_CODES];

	static EMouseStatus leftMouseStatus;
	static EMouseStatus middleMouseStatus;
	static EMouseStatus rightMouseStatus;

	static FVector2 mousePosition;
	static float mouseScrollDelta;
public:
	Input();

	static EKeyCode SystemToKeycode(unsigned int keycode);

	static void OnKeyPressed(unsigned int keycode);
	static void OnKeyReleased(unsigned int keycode);

	static void OnMouseButtonDown(EMouseButton button);
	static void OnMouseButtonUp(EMouseButton button);

	static void OnMouseMove(const FVector2& newPosition);
	static void OnMouseScroll(float newMouseScrollDelta);

	static bool GetKey(EKeyCode keycode);
	static bool GetKeyDown(EKeyCode keycode);
	static bool GetKeyUp(EKeyCode keycode);

	static bool GetMouseButton(EMouseButton button = EMouseButton::Left);
	static bool GetMouseButtonDown(EMouseButton button = EMouseButton::Left);
	static bool GetMouseButtonUp(EMouseButton button = EMouseButton::Left);

	static FVector2 GetMousePosition() { return mousePosition; }
	static float GetMouseScrollDelta() { return mouseScrollDelta; }

	static void OnFrameEnd();
};