#include "Canvas.h"

float Canvas::canvasHeight;
float Canvas::canvasWidth;

void Canvas::UpdateWindow(float height, float width)
{
    canvasHeight = height;
    canvasWidth = width;
}

float Canvas::GetCanvasHeight()
{
    return canvasHeight;
}

float Canvas::GetCanvasWidth()
{
    return canvasWidth;
}
