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

void ChainResolveFabrik(Chain *chain, Vector2 targetPos) {
    Vector2 anchor = chain->points[chain->pointsCount - 1];
    
    // Forward
    chain->points[0] = targetPos;
    for (size_t i = 1; i < chain->pointsCount; ++i) {
        chain->points[i] = Vector2Add(chain->points[i - 1], Vector2Scale(Vector2Normalize(Vector2Subtract(chain->points[i], chain->points[i - 1])), chain->spacing));
    }
    
    // Backward
    chain->points[chain->pointsCount - 1] = anchor;
    for (int i = chain->pointsCount - 1; i > 0; --i) {
        chain->points[i - 1] = Vector2Add(chain->points[i], Vector2Scale(Vector2Normalize(Vector2Subtract(chain->points[i - 1], chain->points[i])), chain->spacing));
    }
}
