#include <math.h>
#include <stdlib.h>

#include "./fish.h"

#include <raylib.h>
#include <raymath.h>

static const float radiuses[FISH_POINTS_COUNT] = {20, 25, 25, 25, 22, 20, 15, 10, 9, 8}; 

void FishInit(Fish *fish, Vector2 points[FISH_POINTS_COUNT]) {
    fish->chain.points = points;
    for (size_t i = 0; i < FISH_POINTS_COUNT; ++i) {
        points[i].x = i*10;
    }
    fish->chain.pointsCount = FISH_POINTS_COUNT;
    fish->chain.spacing = 20;
}

void FishResolve(Fish *fish, Vector2 targetPos) {
    ChainResolve(&fish->chain, targetPos);
}

void FishDraw(Fish *fish) {
    for (size_t i = 0; i < FISH_POINTS_COUNT; ++i) {
        DrawCircleV(fish->chain.points[i], radiuses[i], BLUE);
    }

    for (size_t i = 1; i < FISH_POINTS_COUNT; ++i) {
        float a = Vector2Angle((Vector2){1, 0}, Vector2Normalize(Vector2Subtract(fish->chain.points[i], fish->chain.points[i - 1])));
        // https://en.wikipedia.org/wiki/Belt_problem#Pulley_problem
        float angle = acosf((radiuses[i - 1] - radiuses[i]) / Vector2Distance(fish->chain.points[i - 1], fish->chain.points[i]));

        Vector2 v11 = Vector2Add(fish->chain.points[i - 1], Vector2Rotate((Vector2){radiuses[i - 1], 0}, angle + a));
        Vector2 v12 = Vector2Add(fish->chain.points[i - 1], Vector2Rotate((Vector2){radiuses[i - 1], 0}, -angle + a));
        Vector2 v21 = Vector2Add(fish->chain.points[i], Vector2Rotate((Vector2){radiuses[i], 0}, angle + a));
        Vector2 v22 = Vector2Add(fish->chain.points[i], Vector2Rotate((Vector2){radiuses[i], 0}, -angle + a));
        
        DrawTriangle(v11, v21, v12, BLUE);
        DrawTriangle(v21, v22, v12, BLUE);
    }
}
