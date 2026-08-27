#include "entities/cactus.hpp"
#include <vector>

namespace entities
{
    static const std::vector<CactusVariant> VARIANTS = {
        {Rectangle{445.0f, 1.0f, 34.0f, 67.0f}, 27.0f},
        {Rectangle{445.0f, 1.0f, 68.0f, 67.0f}, 27.0f},
        {Rectangle{445.0f, 1.0f, 102.0f, 67.0f}, 27.0f},

        // Large Cacti (1x, 2x, 3x) -> Height 94px, 0px offset
        {Rectangle{651.0f, 1.0f, 52.0f, 94.0f}, 0.0f},
        {Rectangle{651.0f, 1.0f, 100.0f, 94.0f}, 0.0f},
        {Rectangle{651.0f, 1.0f, 150.0f, 94.0f}, 0.0f}};

    Cactus::Cactus(Texture2D tex, Vector2 base_pos, float speed)
        : Sprite(tex, base_pos), scroll_speed(speed)
    {
        tag = "Obstacle";

        int index = GetRandomValue(0, static_cast<int>(VARIANTS.size()) - 1);
        CactusVariant variant = VARIANTS[index];

        SetSourceRect(variant.source_rect);
        position.y += variant.y_offset;
    }

    void Cactus::Update(float delta)
    {
        Sprite::Update(delta);

        position.x -= scroll_speed * delta;

        if (position.x < -source_rect.width)
        {
            pendingDestroy = true;
        }
    }
}