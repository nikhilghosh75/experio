#pragma once
#include "GWindow.h"
#include "WindowEnums.h"

class LWindowOperations
{
public:
	static float GetAspectRatio(const FWindowData& windowData);

	static float NormalizedToPixelSize(const FWindowData& windowData, const float normalizedSize, EWindowAxisType axis);

	static float PixelToClippedSize(const FWindowData& data, const float pixelSize, EWindowAxisType axis);

	static float PixelToNormalizedSize(const FWindowData& windowData, const float pixelSize, EWindowAxisType axis);
};