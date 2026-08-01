#include "raylib.h"
#include "core/scene.hpp"
#include "entities/dino.hpp"
#include "entities/ground.hpp"
#include "components/graphics/sprite.hpp"

int main()
{
    InitWindow(1280, 600, "Dino Game");
    SetTargetFPS(60);

    Texture2D sheet = LoadTexture("assets/textures/dino.png");

    core::Scene scene{};

    scene.Add(std::make_unique<entities::Dino>(sheet, Vector2{100.0f, 100.0f}));
    scene.Add(std::make_unique<entities::Ground>(sheet, Vector2{0.0f, 300.0f}));

    scene.gravity_on = true;
    scene.SetGravity(15);

    while (!WindowShouldClose())
    {
        float delta = GetFrameTime();

        // Dino::Update handles input, physics, and animation automatically
        scene.Update(delta);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        scene.Paint();

        EndDrawing();
    }

    UnloadTexture(sheet);
    CloseWindow();

    return 0;
}