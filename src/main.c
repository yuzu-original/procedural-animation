#include <raylib.h>
#include <raymath.h>

#include "./fish.h"

int main(void) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1280, 720, "Procedural animation");

    SetTargetFPS(60);
    
    Fish fish;
    FishInit(&fish, (Vector2[FISH_POINTS_COUNT]){0});

    Vector2 mousePos = GetMousePosition();
    Vector2 targetPos = mousePos;
    
    while (!WindowShouldClose()) {
        // Update
        mousePos = GetMousePosition();
        
        targetPos = Vector2MoveTowards(targetPos, mousePos, 5);
        FishResolve(&fish, targetPos);

        // Draw
        BeginDrawing();
            ClearBackground(BLACK);
            FishDraw(&fish);
        EndDrawing();
    }
}
