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
    void Sprite::SetSize(float width, float height)
    {
        if (source_rect.width > 0.0f && source_rect.height > 0.0f)
        {
            scale.x = width / source_rect.width;
            scale.y = height / source_rect.height;
        }
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

    void Sprite::OnCollision(core::SceneObject &other)
    {
        if (!is_rigid_body)
            return;

        Rectangle my_bounds = GetBounds();
        Rectangle other_bounds = other.GetBounds();
        Rectangle overlap = GetCollisionRec(my_bounds, other_bounds);

        if (overlap.width < overlap.height)
        {
            if (my_bounds.x < other_bounds.x)
                position.x -= overlap.width;
            else
                position.x += overlap.width;
            velocity.x = 0.0f;
        }
        else
        {
            if (my_bounds.y < other_bounds.y)
                position.y -= overlap.height;
            else
                position.y += overlap.height;
            velocity.y = 0.0f;
        }
    }

}