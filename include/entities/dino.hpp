#include "raylib.h"
#include "components/graphics/animated_sprite.hpp"

namespace entities
{
    class Dino : public components::graphics::AnimatedSprite
    {
    private:
        bool is_grounded{false};
        float jump_force{-600.0f};
        bool *game_over{nullptr};

    public:
        Dino(Texture2D tex, Vector2 pos, bool *game_over_flag = nullptr);

        void Update(float delta) override;
        void OnCollision(core::SceneObject &other) override;
        void OnSpawn() override;
        Rectangle GetBounds() const override;

        bool IsGrounded() const { return is_grounded; }
    };
}