#include "entities/dino.hpp"

namespace entities
{
    Dino::Dino(Texture2D tex, Vector2 pos)
        : AnimatedSprite(tex, pos)
    {
        tag = "AnimatedSprite:Dino";
        is_rigid_body = true;

        components::graphics::AnimationClip run_clip{
            .name = "run",
            .frames = {
                Rectangle{1854.0f, 2.0f, 88.0f, 94.0f},
                Rectangle{1942.0f, 2.0f, 88.0f, 94.0f}},
            .frame_duration = 0.1f,
            .loop = true};

        AddAnimation("run", run_clip);
        Play("run");
        SetScale(Vector2{0.5f, 0.5f});
    }

    void Dino::Update(float delta)
    {
        if (IsKeyPressed(KEY_SPACE) && is_grounded)
        {
            velocity.y = jump_force;
            is_grounded = false;
        }

        AnimatedSprite::Update(delta);
    }

    void Dino::OnCollision(core::SceneObject &other)
    {
        // First let base Sprite handle positional pushback
        Sprite::OnCollision(other);

        // Evaluate grounded state based on collision orientation
        Rectangle my_bounds = GetBounds();
        Rectangle other_bounds = other.GetBounds();
        Rectangle overlap = GetCollisionRec(my_bounds, other_bounds);

        if (overlap.width >= overlap.height && my_bounds.y < other_bounds.y)
        {
            is_grounded = true;
        }
    }
}