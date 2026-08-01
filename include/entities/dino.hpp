#include "raylib.h"
#include "components/graphics/animated_sprite.hpp"

namespace entities
{
    class Dino : public components::graphics::AnimatedSprite
    {
    private:
        bool is_grounded;
        float jump_force{-350.0f};

    public:
        Dino(Texture2D tex, Vector2 pos);

        void Update(float delta) override;
        void OnCollision(core::SceneObject &other) override;

        bool IsGrounded() const { return is_grounded; }
    };
}