#include "components/graphics/animated_sprite.hpp"

namespace components::graphics
{
    AnimatedSprite::AnimatedSprite(Texture2D tex, Vector2 pos)
        : Sprite(tex, pos)
    {
        tag = "AnimatedSprite";
    }

    void AnimatedSprite::AddAnimation(const std::string &name, const AnimationClip &clip)
    {
        animations[name] = clip;
    }

    void AnimatedSprite::Play(const std::string &name)
    {
        // Don't restart if already playing the requested clip
        if (current_clip == name && is_playing)
            return;

        auto it = animations.find(name);
        if (it != animations.end())
        {
            current_clip = name;
            current_frame_index = 0;
            timer = 0.0f;
            is_playing = true;

            // Snap source_rect to frame 0 immediately
            if (!it->second.frames.empty())
            {
                source_rect = it->second.frames[0];
            }
        }
    }

    void AnimatedSprite::Stop()
    {
        is_playing = false;
    }

    void AnimatedSprite::Update(float delta)
    {
        // Run positional movement from base Sprite first
        Sprite::Update(delta);

        if (!is_playing || current_clip.empty())
            return;

        auto it = animations.find(current_clip);

        if (it == animations.end())
            return;

        const auto &clip = it->second;
        if (clip.frames.empty())
            return;

        timer += delta;
        if (timer >= clip.frame_duration)
        {
            timer -= clip.frame_duration;
            current_frame_index++;

            if (current_frame_index >= clip.frames.size())
            {
                if (clip.loop)
                {
                    current_frame_index = 0; // Wrap around to start of loop
                }
                else
                {
                    current_frame_index = clip.frames.size() - 1; // Freeze on last frame
                    is_playing = false;
                }
            }

            // Update parent's source_rect to current frame slice
            source_rect = clip.frames[current_frame_index];
        }
    }

}