#include "LWindowOperations.h"
#include "../Debug/GDebug.h"

float LWindowOperations::GetAspectRatio(const FWindowData & windowData)
{
	return windowData.width / windowData.height;
}

float LWindowOperations::PixelToNormalizedSize(const FWindowData & windowData, const float pixelSize, EWindowAxisType axis)
{
	switch (axis)
	{
	case EWindowAxisType::None:
		GDebug::LogError("Axis Type is None");
		return 0;
	case EWindowAxisType::X:
		return pixelSize / windowData.width;
	case EWindowAxisType::Y:
		return pixelSize / windowData.height;
	default:
		return 0;
	}
}

float LWindowOperations::NormalizedToPixelSize(const FWindowData & windowData, const float normalizedSize, EWindowAxisType axis)
{
	switch (axis)
	{
	case EWindowAxisType::None:
		GDebug::LogError("Axis Type is None");
		return 0;
	case EWindowAxisType::X:
		return normalizedSize * windowData.width;
	case EWindowAxisType::Y:
		return normalizedSize * windowData.height;
	default:
		return 0;
	}
}

float LWindowOperations::PixelToClippedSize(const FWindowData & windowData, const float pixelSize, EWindowAxisType axis)
{
	switch (axis)
	{
	case EWindowAxisType::None:
		GDebug::LogError("Axis Type is None");
		return 0;
	case EWindowAxisType::X:
		return (pixelSize / windowData.width) * 2 - 1.f;
	case EWindowAxisType::Y:
		return (pixelSize / windowData.height) * 2 - 1.f;
	default:
		return 0;
	}
}
