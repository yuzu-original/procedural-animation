#ifndef CHAIN_H_
#define CHAIN_H_

#include <stdlib.h>

#include <raylib.h>

typedef struct {
    Vector2 *points;
    size_t pointsCount;
    float spacing;
} Chain;

extern void ChainDraw(Chain *chain);

extern void ChainResolve(Chain *chain, Vector2 targetPos);
extern void ChainResolveFabrik(Chain *chain, Vector2 targetPos);

#endif // CHAIN_H_
