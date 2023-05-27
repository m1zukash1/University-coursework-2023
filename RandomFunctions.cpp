#include "RandomFunctions.h"

namespace gameplay
{
    bool toggleDebug = false;
}

float lenght(sf::Vector2f source)
{
    return sqrt((source.x * source.x) + (source.y * source.y));
}

sf::Vector2f normalize(sf::Vector2f source)
{
    float _length = lenght(source);

    if (_length != 0)
        return sf::Vector2f(source.x / _length, source.y / _length);
    else
        return source;
}

float lerp(float a, float b, float t)
{
    return (1 - t) * a + t * b;
}

float lerpAngle(float a, float b, float t)
{
    float angle = fmod(b - a + 360, 360);
    if (angle > 180)
    {
        angle -= 360;
    }
    return a + angle * t;
}


int randIntRange(int from, int to)
{
    return from + rand() % ((to + 1) - from);
}

float randFloatRange(float from, float to)
{
    float r = (float)rand() / (float)RAND_MAX;
    return from + r * (to - from);
}