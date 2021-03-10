#pragma once
#include "Window.h"
#include "../Math/FVector2.h"

/// <summary>
/// A library containing operations on windows
/// </summary>

class LWindowOperations
{
public:
	static float GetAspectRatio(const FWindowData& windowData);

	static float NormalizedToPixelSize(const FWindowData& windowData, const float normalizedSize, EWindowAxisType axis);
	
	static FVector2 NormalizedToPixelPos(const FWindowData& windowData, const FVector2& normalizedPos);

	static float PixelToClippedSize(const FWindowData& data, const float pixelSize, EWindowAxisType axis);

	static FVector2 PixelToClippedPos(const FWindowData& data, const FVector2& pixelPos);

	static float PixelToNormalizedSize(const FWindowData& windowData, const float pixelSize, EWindowAxisType axis);

	static FVector2 PixelToNormalizedPos(const FWindowData& windowData, const FVector2& pixelPos);
};