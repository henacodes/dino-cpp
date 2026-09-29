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
    bool game_over = false;
    const Vector2 dino_start_pos{100.0f, ground_y - 94.0f};

    int counter = 0;
    float timer = 0.0f;
    float interval = 0.1f;

    scene.gravity_on = true;
    scene.SetGravity(15);

    float spawn_timer = 0.0f;
    float spawn_interval = 3.0f;

    auto reset_game = [&]() {
        scene.Clear();
        scene.Add(std::make_unique<entities::Dino>(sheet, dino_start_pos, &game_over));
        scene.Add(std::make_unique<entities::Ground>(sheet, Vector2{0.0f, ground_y}));

        game_over = false;
        counter = 0;
        timer = 0.0f;
        spawn_timer = 0.0f;
        spawn_interval = 3.0f;
    };

    reset_game();

    while (!WindowShouldClose())
    {
        float delta = GetFrameTime();

        if (!game_over)
        {
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
        }
        else if (IsKeyPressed(KEY_R) || IsKeyPressed(KEY_ENTER))
        {
            reset_game();
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        scene.Paint();
        DrawText(std::to_string(counter).c_str(), 1100, 30, 30, DARKGRAY);

        if (game_over)
        {
            DrawRectangle(0, 0, screen_width, screen_height, Fade(BLACK, 0.35f));
            DrawText("GAME OVER", 500, 220, 60, MAROON);
            DrawText("Press R or Enter to restart", 390, 295, 30, DARKGRAY);
        }

        EndDrawing();
    }

    UnloadTexture(sheet);
    CloseWindow();

    return 0;
}