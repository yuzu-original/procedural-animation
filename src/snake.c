#include <stdlib.h>

#include "snake.h"
#include "drawing_utils.h"
#include "math_utils.h"

#include <raylib.h>
#include <raymath.h>

static const float radiuses[SNAKE_POINTS_COUNT] = {
    25, 30, 29, 28, 27, 26, 25, 24, 23, 22,
    21, 20, 19, 18, 17, 16, 15, 14, 13, 12,
    11, 10, 9, 8, 7, 6, 5, 4, 3, 2,
};

void SnakeInit(Snake *snake, Vector2 points[SNAKE_POINTS_COUNT]) {
    snake->chain.points = points;
    snake->chain.pointsCount = SNAKE_POINTS_COUNT;
    snake->chain.spacing = 16;
}

void SnakeResolve(Snake *snake, Vector2 targetPos) {
    ChainResolve(&snake->chain, Vector2Lerp(snake->chain.points[0], targetPos, 0.1));
}

void SnakeDraw(Snake *snake) {
    for (size_t i = 0; i < SNAKE_POINTS_COUNT; ++i) {
        DrawCircleV(snake->chain.points[i], radiuses[i] + 2, WHITE);
    }
    for (size_t i = 1; i < SNAKE_POINTS_COUNT; ++i) {
        DrawPulleyTrapezoid(snake->chain.points[i - 1], radiuses[i - 1] + 2, snake->chain.points[i], radiuses[i] + 2, WHITE);
    }

    for (size_t i = 0; i < SNAKE_POINTS_COUNT; ++i) {
        DrawCircleV(snake->chain.points[i], radiuses[i], ORANGE);
    }
    for (size_t i = 1; i < SNAKE_POINTS_COUNT; ++i) {
        DrawPulleyTrapezoid(snake->chain.points[i - 1], radiuses[i - 1], snake->chain.points[i], radiuses[i], ORANGE);
    }

    size_t ind = 0;
    float angleToNext = Vector2AngleToPoint(snake->chain.points[ind], snake->chain.points[ind + 1]);
    Vector2 v = Vector2PointOnCircle(snake->chain.points[ind], radiuses[ind], angleToNext + PI/3);
    DrawCircleV(v, 4, WHITE);
    v = Vector2PointOnCircle(snake->chain.points[ind], radiuses[ind], angleToNext - PI/3);
    DrawCircleV(v, 4, WHITE);
}
