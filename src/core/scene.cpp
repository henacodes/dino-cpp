#include "core/scene.hpp"
#include <vector>

namespace core
{
    void Scene::Add(std::unique_ptr<SceneObject> obj)
    {
        if (obj != nullptr)
        {
            // Stage additions instead of pushing directly to scene_objects
            pending_additions.push_back(std::move(obj));
        }
    }

    void Scene::Update(float delta)
    {
        // 1. Update active objects
        for (auto &obj : scene_objects)
        {
            if (obj && !obj->IsPendingDestroy())
            {
                obj->Update(delta);
            }
        }

        // 2. Flush pending additions safely after iteration finishes
        if (!pending_additions.empty())
        {
            for (auto &obj : pending_additions)
            {
                if (obj)
                {
                    obj->OnSpawn();
                    scene_objects.push_back(std::move(obj));
                }
            }
            pending_additions.clear();
        }
        Clean();
    }

    void Scene::Paint()
    {
        for (auto &obj : scene_objects)
        {
            if (obj && !obj->IsPendingDestroy())
            {
                obj->Paint();
            }
        }
    }

    void Scene::Clean()
    {
        std::erase_if(scene_objects, [](const std::unique_ptr<SceneObject> &obj)
                      {
            if (!obj)
            {
                return true;
            }

            if (obj->IsPendingDestroy())
            {
                obj->OnDestroy();
                return true;
            }

            return false; });
    }
}