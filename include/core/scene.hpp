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

        void Add(std::unique_ptr<SceneObject> obj);

        bool CheckCollision(const SceneObject &obj1, const SceneObject &obj2);
    };
}