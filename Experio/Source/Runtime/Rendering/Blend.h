#pragma once

// This needs to be put in a better place later

enum class EBlendFunc
{
	None, // corresponds to GL_ZERO
	Complete, // corresponds to GL_ONE
	SourceColor,
	DestinationColor,
	OneMinusSourceColor,
	OneMinusDestinationColor
};