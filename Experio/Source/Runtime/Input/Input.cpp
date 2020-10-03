#include "Input.h"
#include "../Core/Core.h"
#include "imgui.h"
#include "../Debug/Debug.h"
#include <sstream>

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
};

const int KEYCODETOSYSTEM[PB_NUM_KEY_CODES] = {
	0x00, 0x08, 0x2E, 0x09, 0x0C, 0x0D, 0x13, 0x1B,
	0x20, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
	0x67, 0x68, 0x69, 0x6E, 0x6F, 0x6A, 0x6D, 0x6B,
	0x0D, 0x26, 0x28, 0x25, 0x27, 0x2D, 0x24, 0x23,
	0x21, 0x22, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75,
	0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D,
	0x7E, 0x7F, 0x80, 0x81, 0x82, 0x83, 0x30, 0x31,
	0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,
	0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50,
	0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58,
	0x59, 0x5A, 0x00, 0x90, 0x14, 0x91, 0x10, 0x00,
	0x11, 0x00, 0x12, 0x00, 0x00, 0x00, 0x5B, 0x5C,
	0x00, 0x2A, 0x00, 0x2C
};
#endif

EKeyStatus Input::keyStatuses[PB_NUM_KEY_CODES];
EMouseStatus Input::leftMouseStatus = EMouseStatus::Up;
EMouseStatus Input::middleMouseStatus = EMouseStatus::Up;
EMouseStatus Input::rightMouseStatus = EMouseStatus::Up;
FVector2 Input::mousePosition = FVector2(0, 0);
FVector2 Input::lastMousePosition = FVector2(0, 0);
float Input::mouseScrollDelta = 0.f;
float Input::mouseScrollHDelta = 0.f;

void Input::Init()
{
	for (int i = 0; i < PB_NUM_KEY_CODES; i++)
	{
		keyStatuses[i] = EKeyStatus::Released;
	}

	mousePosition = FVector2(0, 0);
	lastMousePosition = FVector2(0, 0);

	leftMouseStatus = EMouseStatus::Up;
	middleMouseStatus = EMouseStatus::Up;
	rightMouseStatus = EMouseStatus::Up;

	mouseScrollDelta = 0;
	mouseScrollHDelta = 0;
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
	lastMousePosition = mousePosition;
	mousePosition = newPosition;
}

void Input::OnMouseScroll(float newMouseScrollDelta)
{
	mouseScrollDelta = newMouseScrollDelta;
}

void Input::OnMouseHScroll(float newMouseScrollDelta)
{
	mouseScrollHDelta = newMouseScrollDelta;
}

void Input::OnImguiUpdate()
{
	ImGuiIO& io = ImGui::GetIO();
	for (int i = 0; i < PB_NUM_KEY_CODES; i++)
	{
		if (KEYCODETOSYSTEM[i] == 0)
		{
			continue;
		}

		if ((keyStatuses[i] == EKeyStatus::Released 
			|| keyStatuses[i] == EKeyStatus::ReleasedThisFrame)
			&& io.KeysDown[KEYCODETOSYSTEM[i]])
		{
			keyStatuses[i] = EKeyStatus::PressedThisFrame;
		}
		else if ((keyStatuses[i] == EKeyStatus::Pressed
			|| keyStatuses[i] == EKeyStatus::PressedThisFrame)
			&& !io.KeysDown[KEYCODETOSYSTEM[i]])
		{
			keyStatuses[i] = EKeyStatus::ReleasedThisFrame;
		}
	}

	if (io.MouseClicked[0]) leftMouseStatus = EMouseStatus::DownThisFrame;
	else if (io.MouseReleased[0]) leftMouseStatus = EMouseStatus::UpThisFrame;

	if (io.MouseClicked[1]) rightMouseStatus = EMouseStatus::DownThisFrame;
	else if (io.MouseReleased[1]) rightMouseStatus = EMouseStatus::UpThisFrame;

	if (io.MouseClicked[2]) middleMouseStatus = EMouseStatus::DownThisFrame;
	else if (io.MouseReleased[2]) middleMouseStatus = EMouseStatus::UpThisFrame;

	mouseScrollDelta = io.MouseWheel;
	mouseScrollHDelta = io.MouseWheelH;

	lastMousePosition = mousePosition;
	mousePosition = io.MousePos;
}

void Input::Reset()
{
	for (int i = 0; i < PB_NUM_KEY_CODES; i++)
	{
		keyStatuses[i] = EKeyStatus::Released;
	}

	leftMouseStatus = EMouseStatus::Up;
	middleMouseStatus = EMouseStatus::Up;
	rightMouseStatus = EMouseStatus::Up;

	mouseScrollDelta = 0;
	mouseScrollHDelta = 0;
}

void Input::SetGameRect(FRect rect)
{
	mousePosition = mousePosition - rect.min;
	lastMousePosition = lastMousePosition - rect.min;
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
	mouseScrollHDelta = 0.f;
}

void Input::DebugInput()
{
	std::stringstream ss;
	ss << "Input: ";

	for (int i = 0; i < PB_NUM_KEY_CODES; i++)
	{
		if (keyStatuses[i] == EKeyStatus::Pressed || keyStatuses[i] == EKeyStatus::PressedThisFrame)
		{
			ss << i << " ";
		}
	}

	Debug::Log(ss.str());
}
