#pragma once

#include "raylib.h"
#include "components/graphics/sprite.hpp"

namespace entities
{
    class Ground : public components::graphics::Sprite
    {
    private:
        float scroll_x{0.0f};
        float scroll_speed{300.0f};
        float base_source_x{2.0f};

    public:
        Ground(Texture2D tex, Vector2 pos, float speed = 300.0f);

        void Update(float delta) override;
        void SetScrollSpeed(float speed) { scroll_speed = speed; }
    };
}