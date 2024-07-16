#ifndef FISH_H_
#define FISH_H_

#include "chain.h"

#include <raylib.h>

#define FISH_POINTS_COUNT 10

typedef struct {
    Chain chain;
} Fish;

extern void FishInit(Fish *fish, Vector2 points[FISH_POINTS_COUNT]);

extern void FishResolve(Fish *fish, Vector2 targetPos);
extern void FishDraw(Fish *fish);

#endif // FISH_H_
