#pragma once

#include "raylib.h"
#include "core/scene_object.hpp"

namespace components::graphics
{
    class Sprite : public core::SceneObject
    {
    protected:
        Texture2D texture{};
        Rectangle source_rect{0.0f, 0.0f, 0.0f, 0.0f};
        Vector2 scale{1.0f, 1.0f};
        Color tint{WHITE};

    public:
        Sprite(Texture2D tex, Vector2 pos);
        ~Sprite() override = default;

        void Update(float delta) override;
        void Paint() override;

        Rectangle GetBounds() const;

        // Configuration
        void SetSourceRect(Rectangle rect) { source_rect = rect; }
        void SetScale(Vector2 s) { scale = s; }
        void SetTint(Color c) { tint = c; }
        void SetSize(float width, float height);

        void OnCollision(core::SceneObject &other) override;
    };
}