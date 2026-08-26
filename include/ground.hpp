#pragma once
#include "core/scene_object.hpp"

class Ground : public core::SceneObject
{
private:
    Rectangle rectangle;

public:
    Ground();

    void Update(float delta) override;
    void Paint() override;
};