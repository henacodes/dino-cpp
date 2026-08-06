#pragma once

#include "raylib.h"
#include "components/graphics/sprite.hpp"

namespace entities
{
    struct CactusVariant
    {
        Rectangle source_rect;
        float y_offset;
    };

    class Cactus : public components::graphics::Sprite
    {
    private:
        float scroll_speed{300.0f};

    public:
        Cactus(Texture2D tex, Vector2 pos, float speed = 300.0f);

        void Update(float delta) override;
    };
}