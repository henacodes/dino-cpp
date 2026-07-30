#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include "components/graphics/sprite.hpp"

namespace components::graphics
{
    struct AnimationClip
    {
        std::string name;
        std::vector<Rectangle> frames;
        float frame_duration{0.1f};
        bool loop{true};
    };

    // animated sprite is just normal sprite on steroids
    class AnimatedSprite : public Sprite
    {
    private:
        std::unordered_map<std::string, AnimationClip> animations{};
        std::string current_clip{""};
        size_t current_frame_index{0};
        float timer{0.0f};
        bool is_playing{false};

    public:
        AnimatedSprite(Texture2D tex, Vector2 pos);
        ~AnimatedSprite() override = default;

        void AddAnimation(const std::string &name, const AnimationClip &clip);
        void Play(const std::string &name);
        void Stop();

        void Update(float delta) override;
        // Paint() is inherited from Sprite without overriding
    };
}