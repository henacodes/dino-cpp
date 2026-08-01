#pragma once
#include <vector>
#include <memory>
#include "scene_object.hpp"

namespace core
{
    class Scene
    {
    private:
        std::vector<std::unique_ptr<SceneObject>> scene_objects;
        std::vector<std::unique_ptr<SceneObject>> pending_additions;
        float gravity = 9.80;

    public:
        bool gravity_on = false;
        Scene() = default;
        ~Scene() = default;

        void Init();
        void Update(float delta);
        void Paint();
        void Clean();

        template <typename T>
        void Add(std::unique_ptr<T> obj)
        {
            static_assert(std::is_base_of_v<SceneObject, T>, "T must derive from core::SceneObject");

            if (obj != nullptr)
            {
                pending_additions.emplace_back(std::move(obj));
            }
        }
        bool CheckCollision(const SceneObject &obj1, const SceneObject &obj2);
        void SetGravity(float val)
        {
            gravity = val;
        }
    };
}