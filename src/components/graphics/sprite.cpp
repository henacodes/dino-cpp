#include "components/graphics/sprite.hpp"

namespace components::graphics
{
    Sprite::Sprite(Texture2D tex, Vector2 pos)
        : texture(tex)
    {
        position = pos;
        tag = "Sprite";

        // Default to the full texture dimensions
        source_rect = Rectangle{
            0.0f,
            0.0f,
            static_cast<float>(texture.width),
            static_cast<float>(texture.height)};
    }

    void Sprite::Update(float delta)
    {
        position.x += velocity.x * delta;
        position.y += velocity.y * delta;
    }

    void Sprite::Paint()
    {
        if (texture.id == 0)
            return;

        Rectangle dest_rect{
            position.x,
            position.y,
            source_rect.width * scale.x,
            source_rect.height * scale.y};

        Vector2 origin{0.0f, 0.0f};

        DrawTexturePro(texture, source_rect, dest_rect, origin, rotation.x, tint);
    }

    Rectangle Sprite::GetBounds() const
    {
        return Rectangle{
            position.x,
            position.y,
            source_rect.width * scale.x,
            source_rect.height * scale.y};
    }
}