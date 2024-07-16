#include "fish.h"
#include "snake.h"
#include "lizard.h"

#include <raylib.h>
#include <raymath.h>

int main(void) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1280, 720, "Procedural animation");

    SetTargetFPS(60);
    
    Fish fish;
    FishInit(&fish, (Vector2[FISH_POINTS_COUNT]){0});
    Snake snake;
    SnakeInit(&snake, (Vector2[SNAKE_POINTS_COUNT]){0});
    Lizard lizard;
    LizardInit(&lizard, (Vector2[LIZARD_SPINE_POINTS_COUNT]){0}, (Vector2[LIZARD_ARMS_COUNT][LIZARD_ARM_POINTS_COUNT]){0});
    
    int exampleId = 0;
    int exampleCount = 3;
    float speed = 500;
    float dt = 0;

    Vector2 mousePos = GetMousePosition();
    Vector2 targetPos = mousePos;
    Vector2 dir = {0};

    while (!WindowShouldClose()) {
        // Update
        dt = GetFrameTime();
        mousePos = GetMousePosition();
        
        dir.x = 0;
        dir.y = 0;

        if (IsKeyPressed(KEY_SPACE)) {
            exampleId = (exampleId + 1)%exampleCount;
        }
        if (IsKeyDown(KEY_LEFT)) {
            dir.x = -1;
        } else if (IsKeyDown(KEY_RIGHT)) {
            dir.x = 1;
        }
        if (IsKeyDown(KEY_UP)) {
            dir.y = -1;
        } else if (IsKeyDown(KEY_DOWN)) {
            dir.y = 1;
        }

        targetPos = Vector2Add(targetPos, Vector2Scale(Vector2Normalize(dir), speed*dt));
        
        if (exampleId == 0) {
            FishResolve(&fish, targetPos);
        } else if (exampleId == 1) {
            SnakeResolve(&snake, targetPos);
        } else {
            LizardResolve(&lizard, targetPos);
        }

        // Draw
        BeginDrawing();
            ClearBackground(BLACK);
            if (exampleId == 0) {
                FishDraw(&fish);
            } else if (exampleId == 1) {
                SnakeDraw(&snake);
            } else {
                LizardDraw(&lizard);
            }
        EndDrawing();
    }
}
