#include "components/graphics/sprite.hpp"

namespace components::graphics
{
    Sprite::Sprite(Texture2D tex, Vector2 pos)
        : texture(tex)
    {
        position = pos;
        tag = "Sprite";

        // Default sourceRect spans the full texture width and height
        sourceRect = Rectangle{
            0.0f,
            0.0f,
            static_cast<float>(texture.width),
            static_cast<float>(texture.height)};
    }

    void Sprite::Update(float delta)
    {
        // Translate position based on current velocity
        position.x += velocity.x * delta;
        position.y += velocity.y * delta;
    }

    void Sprite::Paint()
    {
        // Guard against uninitialized GPU textures
        if (texture.id == 0)
            return;

        // Map the source portion to screen destination space
        Rectangle destRect{
            position.x,
            position.y,
            sourceRect.width * scale.x,
            sourceRect.height * scale.y};

        Vector2 origin{0.0f, 0.0f}; // Rotation origin relative to top-left

        DrawTexturePro(texture, sourceRect, destRect, origin, rotation.x, tint);
    }

    Rectangle Sprite::GetBounds() const
    {
        return Rectangle{
            position.x,
            position.y,
            sourceRect.width * scale.x,
            sourceRect.height * scale.y};
    }
}