#pragma once
#include "../Math/FVector2.h"
#include "../Math/FRect.h"
#include "InputCodes.h"
#include "Shortcut.h"

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

	static void CheckShortcuts();
public:
	static std::vector<Shortcut> shortcuts;

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