#ifndef SNAKE_H_
#define SNAKE_H_

#include "chain.h"

#include <raylib.h>

#define SNAKE_POINTS_COUNT 30

typedef struct {
    Chain chain;
} Snake;

extern void SnakeInit(Snake *snake, Vector2 points[SNAKE_POINTS_COUNT]);

extern void SnakeResolve(Snake *snake, Vector2 targetPos);
extern void SnakeDraw(Snake *snake);

#endif // SNAKE_H_
