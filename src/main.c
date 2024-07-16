#include <stdlib.h>

#include "fish.h"
#include "snake.h"

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
    
    size_t exampleId = 0;
    size_t exampleCount = 2;

    Vector2 mousePos = GetMousePosition();
    Vector2 targetPos = mousePos;
    
    while (!WindowShouldClose()) {
        // Update
        mousePos = GetMousePosition();
        
        if (IsKeyPressed(KEY_LEFT)) {
            exampleId = (exampleId - 1) % exampleCount;
        } else if (IsKeyPressed(KEY_RIGHT)) {
            exampleId = (exampleId + 1) % exampleCount;
        }
        
        targetPos = mousePos;

        if (exampleId == 0) {
            FishResolve(&fish, targetPos);
        } else {
            SnakeResolve(&snake, targetPos);
        }

        // Draw
        BeginDrawing();
            ClearBackground(BLACK);
            if (exampleId == 0) {
                FishDraw(&fish);
            } else {
                SnakeDraw(&snake);
            }
        EndDrawing();
    }
}
