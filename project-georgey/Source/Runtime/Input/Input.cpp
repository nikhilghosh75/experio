#include "Input.h"
#include "../Core/Core.h"

#ifdef PLATFORM_WINDOWS
const int SYSTEMTOKEYCODE[145] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	1, 3, 0, 0, 4, 5, 0, 0,
	102, 104, 106, 6, 100, 0, 0, 0, 
	0, 0, 0, 7, 0, 0, 0, 0,
	8, 32, 33, 31, 30, 27, 25, 28,
	26, 114, 113, 0, 115, 29, 2, 116,
	54, 55, 56, 57, 58, 59, 60, 61, 
	62, 63, 0, 0, 0, 0, 0, 0,
	0, 72, 73, 74, 75, 76, 77, 78, 
	79, 80, 81, 82, 83, 84, 85, 86, 
	87, 88, 89, 90, 91, 92, 93, 94, 
	95, 96, 97, 110, 111, 0, 0, 0,
	9, 10, 11, 12, 13, 14, 15, 16,
	17, 18, 21, 23, 0, 22, 19, 20,
	34, 35, 36, 37, 38, 39, 40, 41,
	42, 43, 44, 45, 46, 47, 48, 49,
	50, 51, 52, 53, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	99
}; // 48 (0x30)
#endif

EKeyStatus Input::keyStatuses[116];
EMouseStatus Input::leftMouseStatus = EMouseStatus::Up;
EMouseStatus Input::middleMouseStatus = EMouseStatus::Up;
EMouseStatus Input::rightMouseStatus = EMouseStatus::Up;
FVector2 Input::mousePosition = FVector2(0, 0);
float Input::mouseScrollDelta = 0.f;

Input::Input()
{
	for (int i = 0; i < 116; i++)
	{
		keyStatuses[i] = EKeyStatus::Released;
	}
}

EKeyCode Input::SystemToKeycode(unsigned int keycode)
{
	if (keycode > 145)
	{
		return EKeyCode::None;
	}
	int convertedKeyCode = SYSTEMTOKEYCODE[keycode];
	return *(EKeyCode*)&convertedKeyCode;
}

void Input::OnKeyPressed(unsigned int keycode)
{
	EKeyCode convertedKeyCode = SystemToKeycode(keycode);
	keyStatuses[(unsigned int)convertedKeyCode] = EKeyStatus::PressedThisFrame;
}

void Input::OnKeyReleased(unsigned int keycode)
{
	EKeyCode convertedKeyCode = SystemToKeycode(keycode);
	keyStatuses[(unsigned int)convertedKeyCode] = EKeyStatus::ReleasedThisFrame;
}

void Input::OnMouseButtonDown(EMouseButton button)
{
	switch (button)
	{
	case EMouseButton::Left:
		leftMouseStatus = EMouseStatus::DownThisFrame;
		break;
	case EMouseButton::Middle:
		middleMouseStatus = EMouseStatus::DownThisFrame;
		break;
	case EMouseButton::Right:
		middleMouseStatus = EMouseStatus::DownThisFrame;
		break;
	}
}

void Input::OnMouseButtonUp(EMouseButton button)
{
	switch (button)
	{
	case EMouseButton::Left:
		leftMouseStatus = EMouseStatus::UpThisFrame;
		break;
	case EMouseButton::Middle:
		middleMouseStatus = EMouseStatus::UpThisFrame;
		break;
	case EMouseButton::Right:
		rightMouseStatus = EMouseStatus::UpThisFrame;
		break;
	}
}

void Input::OnMouseMove(const FVector2 & newPosition)
{
	mousePosition = newPosition;
}

void Input::OnMouseScroll(float newMouseScrollDelta)
{
	mouseScrollDelta = newMouseScrollDelta;
}

bool Input::GetKey(EKeyCode keycode)
{
	return (keyStatuses[(unsigned int)keycode] == EKeyStatus::Pressed || keyStatuses[(unsigned int)keycode] == EKeyStatus::PressedThisFrame);
}

bool Input::GetKeyDown(EKeyCode keycode)
{
	return keyStatuses[(unsigned int)keycode] == EKeyStatus::PressedThisFrame;
}

bool Input::GetKeyUp(EKeyCode keycode)
{
	return keyStatuses[(unsigned int)keycode] == EKeyStatus::ReleasedThisFrame;
}

bool Input::GetMouseButton(EMouseButton button)
{
	switch (button)
	{
	case EMouseButton::Left:
		return leftMouseStatus == EMouseStatus::Down || leftMouseStatus == EMouseStatus::DownThisFrame;
	case EMouseButton::Middle:
		return middleMouseStatus == EMouseStatus::Down || middleMouseStatus == EMouseStatus::DownThisFrame;
	case EMouseButton::Right:
		return rightMouseStatus == EMouseStatus::Down || rightMouseStatus == EMouseStatus::DownThisFrame;
	}
	return false;
}

bool Input::GetMouseButtonDown(EMouseButton button)
{
	switch (button)
	{
	case EMouseButton::Left:
		return leftMouseStatus == EMouseStatus::DownThisFrame;
	case EMouseButton::Middle:
		return middleMouseStatus == EMouseStatus::DownThisFrame;
	case EMouseButton::Right:
		return rightMouseStatus == EMouseStatus::DownThisFrame;
	}
	return false;
}

bool Input::GetMouseButtonUp(EMouseButton button)
{
	switch (button)
	{
	case EMouseButton::Left:
		return leftMouseStatus == EMouseStatus::UpThisFrame;
	case EMouseButton::Middle:
		return middleMouseStatus == EMouseStatus::UpThisFrame;
	case EMouseButton::Right:
		return rightMouseStatus == EMouseStatus::UpThisFrame;
	}
	return false;
}

void Input::OnFrameEnd()
{
	for (int i = 0; i < PB_NUM_KEY_CODES; i++)
	{
		if (keyStatuses[i] == EKeyStatus::PressedThisFrame)
		{
			keyStatuses[i] = EKeyStatus::Pressed;
		}
		else if (keyStatuses[i] == EKeyStatus::ReleasedThisFrame)
		{
			keyStatuses[i] = EKeyStatus::Released;
		}
	}

	if (leftMouseStatus == EMouseStatus::DownThisFrame)
	{
		leftMouseStatus = EMouseStatus::Down;
	}
	else if (leftMouseStatus == EMouseStatus::UpThisFrame)
	{
		leftMouseStatus = EMouseStatus::Up;
	}

	if (middleMouseStatus == EMouseStatus::DownThisFrame)
	{
		middleMouseStatus = EMouseStatus::Down;
	}
	else if (middleMouseStatus == EMouseStatus::UpThisFrame)
	{
		middleMouseStatus = EMouseStatus::Up;
	}

	if (rightMouseStatus == EMouseStatus::DownThisFrame)
	{
		rightMouseStatus = EMouseStatus::Down;
	}
	else if (rightMouseStatus == EMouseStatus::UpThisFrame)
	{
		rightMouseStatus = EMouseStatus::Up;
	}
	mouseScrollDelta = 0.f;
}
