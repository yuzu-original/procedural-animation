#include "chain.h"

#include <raylib.h>
#include <raymath.h>

void ChainDraw(Chain *chain) {
    for (size_t i = 0; i < chain->pointsCount; ++i) {
        DrawCircleV(chain->points[i], 10, RED);
    }
}

void ChainResolve(Chain *chain, Vector2 targetPos) {
    if (Vector2Equals(chain->points[0], targetPos)) {
        return;
    }
    chain->points[0] = targetPos;
    for (size_t i = 1; i < chain->pointsCount; ++i) {
        chain->points[i] = Vector2Add(chain->points[i - 1], Vector2Scale(Vector2Normalize(Vector2Subtract(chain->points[i], chain->points[i - 1])), chain->spacing));
    }
}
