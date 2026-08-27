#include "raylib.h"
#include "core/scene.hpp"
#include "entities/dino.hpp"
#include "entities/ground.hpp"
#include "entities/cactus.hpp"
#include "components/graphics/sprite.hpp"
#include <string>
#include <memory>

int main()
{
    const int screen_width = 1280;
    const int screen_height = 600;

    InitWindow(screen_width, screen_height, "Dino Game");
    SetTargetFPS(60);

    Texture2D sheet = LoadTexture("assets/textures/dino.png");

    float ground_y = 300.0f;
    core::Scene scene{};

    // Player & Ground Setup
    scene.Add(std::make_unique<entities::Dino>(sheet, Vector2{100.0f, 100.0f}));
    scene.Add(std::make_unique<entities::Ground>(sheet, Vector2{0.0f, ground_y}));

    scene.gravity_on = true;
    scene.SetGravity(15);

    int counter = 0;
    float timer = 0.0f;
    float interval = 0.1f;

    float spawn_timer = 0.0f;
    float spawn_interval = 2.0f;

    while (!WindowShouldClose())
    {
        float delta = GetFrameTime();

        scene.Update(delta);

        // Counter accumulator
        timer += delta;
        if (timer >= interval)
        {
            counter += 1;
            timer -= interval;
        }

        // Obstacle Spawner Loop
        spawn_timer += delta;
        if (spawn_timer >= spawn_interval)
        {
            spawn_timer = 0.0f;
            spawn_interval = static_cast<float>(GetRandomValue(15, 30)) / 10.0f;

            scene.Add(std::make_unique<entities::Cactus>(
                sheet,
                Vector2{static_cast<float>(screen_width), ground_y - 94.0f}));
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        scene.Paint();
        DrawText(std::to_string(counter).c_str(), 1100, 30, 30, DARKGRAY);

        EndDrawing();
    }

    UnloadTexture(sheet);
    CloseWindow();

    return 0;
}