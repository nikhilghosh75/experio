#include "GInput.h"
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

EKeyCode GInput::SystemToKeycode(unsigned int keycode)
{
	if (keycode > 145)
	{
		return EKeyCode::None;
	}
	int convertedKeyCode = SYSTEMTOKEYCODE[keycode];
	return *(EKeyCode*)&convertedKeyCode;
}
