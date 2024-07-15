#include <raylib.h>
#include <raymath.h>

#include "./fish.c"

int main(void) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1280, 720, "Procedural animation");

    SetTargetFPS(60);
    
    Fish fish1;
    FishInit(&fish1, (Vector2[FISH_POINTS_COUNT]){0});
    Fish fish2;
    FishInit(&fish2, (Vector2[FISH_POINTS_COUNT]){0});

    Vector2 mousePos = GetMousePosition();
    Vector2 targetPos1 = mousePos;
    Vector2 targetPos2 = mousePos;
    
    while (!WindowShouldClose()) {
        // Update
        mousePos = GetMousePosition();
        
        targetPos1 = Vector2MoveTowards(targetPos1, mousePos, 5);
        FishResolve(&fish1, targetPos1);
        targetPos2 = Vector2MoveTowards(targetPos2, targetPos1, 2.5);
        FishResolve(&fish2, targetPos2);

        // Draw
        BeginDrawing();
            ClearBackground(BLACK);
            FishDraw(&fish1);
            FishDraw(&fish2);
        EndDrawing();
    }
}
