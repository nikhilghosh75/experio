#include "LWindowOperations.h"

float LWindowOperations::GetAspectRatio(const FWindowData & windowData)
{
	return windowData.width / windowData.height;
}
