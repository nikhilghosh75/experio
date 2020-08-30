#include "LWindowOperations.h"
#include "../Debug/Debug.h"

float LWindowOperations::GetAspectRatio(const FWindowData & windowData)
{
	if (windowData.height == 0)
	{
		return 1;
	}
	return (float)windowData.width / windowData.height;
}

float LWindowOperations::PixelToNormalizedSize(const FWindowData & windowData, const float pixelSize, EWindowAxisType axis)
{
	switch (axis)
	{
	case EWindowAxisType::None:
		Debug::LogError("Axis Type is None");
		return 0;
	case EWindowAxisType::X:
		return pixelSize / windowData.width;
	case EWindowAxisType::Y:
		return pixelSize / windowData.height;
	default:
		return 0;
	}
}

FVector2 LWindowOperations::PixelToNormalizedPos(const FWindowData & windowData, const FVector2 & pixelPos)
{
	return FVector2(PixelToNormalizedSize(windowData, pixelPos.x, EWindowAxisType::X), PixelToNormalizedSize(windowData, pixelPos.y, EWindowAxisType::Y));
}

float LWindowOperations::NormalizedToPixelSize(const FWindowData & windowData, const float normalizedSize, EWindowAxisType axis)
{
	switch (axis)
	{
	case EWindowAxisType::None:
		Debug::LogError("Axis Type is None");
		return 0;
	case EWindowAxisType::X:
		return normalizedSize * windowData.width;
	case EWindowAxisType::Y:
		return normalizedSize * windowData.height;
	default:
		return 0;
	}
}

FVector2 LWindowOperations::NormalizedToPixelPos(const FWindowData & windowData, const FVector2 & normalizedPos)
{
	return FVector2(NormalizedToPixelSize(windowData, normalizedPos.x, EWindowAxisType::X), NormalizedToPixelSize(windowData, normalizedPos.y, EWindowAxisType::Y));
}

float LWindowOperations::PixelToClippedSize(const FWindowData & windowData, const float pixelSize, EWindowAxisType axis)
{
	switch (axis)
	{
	case EWindowAxisType::None:
		Debug::LogError("Axis Type is None");
		return 0;
	case EWindowAxisType::X:
		return (pixelSize / windowData.width) * 2 - 1.f;
	case EWindowAxisType::Y:
		return (pixelSize / windowData.height) * 2 - 1.f;
	default:
		return 0;
	}
}

FVector2 LWindowOperations::PixelToClippedPos(const FWindowData & data, const FVector2 & pixelPos)
{
	return FVector2(PixelToClippedSize(data, pixelPos.x, EWindowAxisType::X), PixelToClippedSize(data, pixelPos.y, EWindowAxisType::Y));
}

