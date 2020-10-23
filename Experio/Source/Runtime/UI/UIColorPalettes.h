#pragma once

#include "../Math/FColor.h"

struct FButtonColorPalette
{
	FColor defaultColor;
	FColor hoveredColor;
	FColor activeColor;

	FButtonColorPalette()
	{
		defaultColor = FColor();
		hoveredColor = FColor();
		activeColor = FColor();
	}

	FButtonColorPalette(FColor color)
	{
		defaultColor = color;
		hoveredColor = color;
		activeColor = color;
	}

	FButtonColorPalette(FColor defaultColor, FColor hoveredColor, FColor activeColor)
	{
		this->defaultColor = defaultColor;
		this->hoveredColor = hoveredColor;
		this->activeColor = activeColor;
	}

	static FButtonColorPalette redPalette;
	static FButtonColorPalette greenPalette;
	static FButtonColorPalette bluePalette;
	static FButtonColorPalette yellowPalette;
};