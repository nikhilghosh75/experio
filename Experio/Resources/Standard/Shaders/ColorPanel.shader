#language GLSL
#version 330 core

#shader vertex

layout(location = 0) in vec2 position;

uniform float cornerPoint;

out vec2 pixelPos;

void main()
{
    pixelPos = position;
    gl_Position = vec4(position, 0, 1);
}

#shader fragment

uniform vec4 panelColor;
uniform vec2 minCorner;
uniform vec2 maxCorner;

uniform float cornerPoint;

in vec2 pixelPos;

out vec4 color;

void main()
{
    float alpha = panelColor.a;
    
    float bottomLeftDist = distance(pixelPos, vec2(minCorner.x, minCorner.y));
    float bottomRightDist = distance(pixelPos, vec2(maxCorner.x, minCorner.y));
    float topLeftDist = distance(pixelPos, vec2(minCorner.x, maxCorner.y));
    float topRightDist = distance(pixelPos, vec2(maxCorner.x, maxCorner.y));

    if (bottomLeftDist < cornerPoint || bottomRightDist < cornerPoint
        || topLeftDist < cornerPoint || topRightDist < cornerPoint)
    {

        bottomLeftDist = distance(pixelPos, vec2(minCorner.x + cornerPoint, minCorner.y + cornerPoint));
        bottomRightDist = distance(pixelPos, vec2(maxCorner.x - cornerPoint, minCorner.y + cornerPoint));
        topLeftDist = distance(pixelPos, vec2(minCorner.x + cornerPoint, maxCorner.y - cornerPoint));
        topRightDist = distance(pixelPos, vec2(maxCorner.x - cornerPoint, maxCorner.y - cornerPoint));

        if (bottomLeftDist < cornerPoint || bottomRightDist < cornerPoint
            || topLeftDist < cornerPoint || topRightDist < cornerPoint)
        {
            color = panelColor;
        }
        else
        {
            color = vec4(0, 0, 0, 0);
        }
    }
    else
    {
        color = panelColor;
    }
}
