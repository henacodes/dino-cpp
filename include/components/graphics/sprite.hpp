#pragma once

#include "raylib.h"
#include "core/scene_object.hpp"

namespace components::graphics
{
    class Sprite : public core::SceneObject
    {
    private:
        Texture2D texture{};
        Rectangle sourceRect{0.0f, 0.0f, 0.0f, 0.0f};
        Vector2 scale{1.0f, 1.0f};
        Color tint{WHITE};

    public:
        Sprite(Texture2D tex, Vector2 pos);

        void Update(float delta) override;
        void Paint() override;

        // Custom bounds calculator based on texture frame and scale
        Rectangle GetBounds() const;

        // Configuration helpers
        void SetSourceRect(Rectangle rect) { sourceRect = rect; }
        void SetScale(Vector2 s) { scale = s; }
        void SetTint(Color c) { tint = c; }
    };
}