#include "core/scene.hpp"
#include <vector>

namespace core
{

    void Scene::Update(float delta)
    {

        // 1. Update active objects
        for (auto &obj : scene_objects)
        {
            if (obj && !obj->IsPendingDestroy())
            {
                Vector2 curr_vel = obj->GetVel();
                curr_vel.y += gravity;

                if (gravity_on && obj->isRigidBody())
                {
                    obj->SetVel(curr_vel);
                }
                obj->Update(delta);
            }
        }

        // collision detection and notification
        for (size_t i = 0; i < scene_objects.size(); ++i)
        {
            for (size_t j = i + 1; j < scene_objects.size(); ++j)
            {
                if (CheckCollision(*scene_objects[i], *scene_objects[j]))
                {
                    // Notify both entities of the collision
                    scene_objects[i]->OnCollision(*scene_objects[j]);
                    scene_objects[j]->OnCollision(*scene_objects[i]);
                }
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

    bool Scene::CheckCollision(const SceneObject &obj1, const SceneObject &obj2)
    {
        // Fetch the bounding rectangles from both abstract objects
        Rectangle bounds1 = obj1.GetBounds();
        Rectangle bounds2 = obj2.GetBounds();

        // Let Raylib perform collision detection
        return CheckCollisionRecs(bounds1, bounds2);
    }
}