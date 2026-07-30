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

    public:
        Scene() = default;
        ~Scene() = default;

        void Init();
        void Update(float delta);
        void Paint();
        void Clean();

        void Add(std::unique_ptr<SceneObject> obj);
    };
}