#pragma once
#include "../Math/FVector2.h"
#include "../Math/FRect.h"

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

class GameTime;
class Window;

class Input
{
	friend class GameTime;
	friend class Window;
private:
	static EKeyStatus keyStatuses[PB_NUM_KEY_CODES];

	static EMouseStatus leftMouseStatus;
	static EMouseStatus middleMouseStatus;
	static EMouseStatus rightMouseStatus;

	static FVector2 mousePosition;
	static FVector2 lastMousePosition;

	static float mouseScrollDelta;
	static float mouseScrollHDelta;

	static void Init();

	static EKeyCode SystemToKeycode(unsigned int keycode);

	static void OnKeyPressed(unsigned int keycode);
	static void OnKeyReleased(unsigned int keycode);

	static void OnMouseButtonDown(EMouseButton button);
	static void OnMouseButtonUp(EMouseButton button);

	static void OnMouseMove(const FVector2& newPosition);
	static void OnMouseScroll(float newMouseScrollDelta);
	static void OnMouseHScroll(float newMouseScrollDelta);

	static void OnImguiUpdate();

	// Use wisely
	static void Reset();
public:
	static void SetGameRect(FRect rect);

	static bool GetKey(EKeyCode keycode);
	static bool GetKeyDown(EKeyCode keycode);
	static bool GetKeyUp(EKeyCode keycode);

	static bool GetMouseButton(EMouseButton button = EMouseButton::Left);
	static bool GetMouseButtonDown(EMouseButton button = EMouseButton::Left);
	static bool GetMouseButtonUp(EMouseButton button = EMouseButton::Left);

	static FVector2 GetMousePosition() { return mousePosition; }
	static FVector2 GetMouseDelta() { return mousePosition - lastMousePosition; }
	static float GetMouseScrollDelta() { return mouseScrollDelta; }
	static float GetMouseHScrollDelta() { return mouseScrollHDelta; }

	static void OnFrameEnd();

	static void DebugInput();
};