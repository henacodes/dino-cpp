#include "ground.hpp"
#include "raylib.h"

Ground::Ground()
{
    rectangle = {
    0.0f,
    294.0f,
    800.0f,
    156.0f
    };
}

void Ground::Update(float delta)
{
}
void Ground::Paint()
{
    DrawRectangleRec(rectangle, DARKGRAY);
}