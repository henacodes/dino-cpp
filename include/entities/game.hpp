#pragma once

#include "raylib.h"
#include "components/graphics/sprite.hpp"
#include "core/scene.hpp"
namespace entities
{
    enum class State
    {
        Idle,
        Playing,
        GameOver
    };
    class Game
    {

        core::Scene scene;
        int score;
        State state = State::Idle;
    };
}