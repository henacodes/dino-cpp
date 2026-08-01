#include "entities/ground.hpp"
#include <cmath>

namespace entities
{
    Ground::Ground(Texture2D tex, Vector2 pos, float speed)
        : Sprite(tex, pos), scroll_speed(speed)
    {
        tag = "Ground";

        // Enable repeating wrap mode so texture coordinates seamlessly loop
        SetTextureWrap(texture, TEXTURE_WRAP_REPEAT);

        SetSourceRect(Rectangle{
            base_source_x,
            104.0f,
            static_cast<float>(texture.width),
            24.0f});
    }

    void Ground::Update(float delta)
    {
        Sprite::Update(delta);

        // Advance scroll offset and keep it bounded within texture width
        scroll_x += scroll_speed * delta;
        scroll_x = std::fmod(scroll_x, static_cast<float>(texture.width));

        // Shift the source rect horizontally
        SetSourceRect(Rectangle{
            base_source_x + scroll_x,
            104.0f,
            static_cast<float>(texture.width),
            24.0f});
    }
}