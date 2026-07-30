#pragma once

#include <string>
#include "raylib.h"

namespace core
{
    class SceneObject
    {
    protected:
        Vector2 position{0.0f, 0.0f};
        Vector2 velocity{0.0f, 0.0f};
        Vector2 rotation{0.0f, 0.0f};

        std::string tag{"Default"};
        bool pendingDestroy{false};

    public:
        virtual ~SceneObject() = default;

        // frame hook; each scene object needs to implement these
        virtual void Update(float delta) = 0;
        virtual void Paint() = 0;

        // Lifecycle hooks
        virtual void OnSpawn() {}
        virtual void OnDestroy() {}

        // Destruction signaling
        void Destroy() { pendingDestroy = true; }
        bool IsPendingDestroy() const { return pendingDestroy; }

        // Getters & Setters
        Vector2 GetPos() const { return position; }
        void SetPos(Vector2 pos) { position = pos; }

        Vector2 GetVel() const { return velocity; }
        void SetVel(Vector2 vel) { velocity = vel; }

        std::string GetTag() const { return tag; }
        void SetTag(const std::string &newTag) { tag = newTag; }
    };
}