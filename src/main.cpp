#include "raylib.h"
#include "core/scene.hpp"
#include "components/graphics/animated_sprite.hpp"

int main()
{
    InitWindow(1280, 600, "Dino Game");
    SetTargetFPS(60);

    Texture2D sheet = LoadTexture("assets/textures/dino.png");

    core::Scene scene{};

    // Build the sprite component
    auto dino = std::make_unique<components::graphics::AnimatedSprite>(sheet, Vector2{100.0f, 200.0f});
    dino->toggleRigidBody();
    components::graphics::AnimationClip run_clip{
        .name = "run",
        .frames = {
            Rectangle{1854.0f, 2.0f, 88.0f, 94.0f},
            Rectangle{1942.0f, 2.0f, 88.0f, 94.0f}},
        .frame_duration = 0.1f,
        .loop = true};

    dino->AddAnimation("run", run_clip);
    dino->Play("run");
    dino->SetScale(Vector2{0.5f, 0.5f});

    auto ground = std::make_unique<components::graphics::Sprite>(sheet, Vector2{0.0f, 250.0f});
    ground->SetSourceRect(Rectangle{
        2.0f,
        104.0f,
        (float)sheet.width,
        24.0f});
    // ground->SetSize(64.0f, 64.0f);

    // Add to scene queue
    scene.Add(std::move(dino));
    scene.Add(std::move(ground));

    scene.gravity_on = true;
    while (!WindowShouldClose())
    {
        float delta = GetFrameTime();

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