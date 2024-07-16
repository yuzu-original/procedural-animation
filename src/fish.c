#include <stdio.h>

#include "fish.h"
#include "math_utils.h"
#include "drawing_utils.h"

#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>

static const float radiuses[FISH_POINTS_COUNT] = {20, 25, 25, 25, 22, 20, 15, 12, 9, 8}; 

void FishInit(Fish *fish, Vector2 points[FISH_POINTS_COUNT]) {
    fish->chain.points = points;
    for (size_t i = 0; i < FISH_POINTS_COUNT; ++i) {
        points[i].x = i*10;
    }
    fish->chain.pointsCount = FISH_POINTS_COUNT;
    fish->chain.spacing = 20;
}

void FishResolve(Fish *fish, Vector2 targetPos) {
    ChainResolve(&fish->chain, Vector2Lerp(fish->chain.points[0], targetPos, 0.1));
}

void FishDraw(Fish *fish) {
    size_t ind = 2;
    float angleToNext = Vector2AngleToPoint(fish->chain.points[ind], fish->chain.points[ind + 1]);
    Vector2 v = Vector2PointOnCircle(fish->chain.points[ind], radiuses[ind], angleToNext + PI/2);
    rlPushMatrix();
    rlTranslatef(v.x, v.y, 0);
    rlRotatef(RAD2DEG*angleToNext + 60, 0, 0, 1);
    DrawEllipse(0, 0, 18, 10, WHITE);
    DrawEllipse(0, 0, 16, 8, Fade(BLUE, 0.8));
    rlPopMatrix();
    v = Vector2PointOnCircle(fish->chain.points[ind], radiuses[ind], angleToNext - PI/2);
    rlPushMatrix();
    rlTranslatef(v.x, v.y, 0);
    rlRotatef(RAD2DEG*angleToNext - 60, 0, 0, 1);
    DrawEllipse(0, 0, 18, 10, WHITE);
    DrawEllipse(0, 0, 16, 8, Fade(BLUE, 0.8));
    rlPopMatrix();
    
    ind = 8;
    angleToNext = Vector2AngleToPoint(fish->chain.points[ind], fish->chain.points[ind + 1]);
    v = Vector2PointOnCircle(fish->chain.points[ind], radiuses[ind], angleToNext + PI/2);
    rlPushMatrix();
    rlTranslatef(v.x, v.y, 0);
    rlRotatef(RAD2DEG*angleToNext + 60, 0, 0, 1);
    DrawEllipse(0, 0, 18, 10, WHITE);
    DrawEllipse(0, 0, 16, 8, Fade(BLUE, 0.8));
    rlPopMatrix();
    v = Vector2PointOnCircle(fish->chain.points[ind], radiuses[ind], angleToNext - PI/2);
    rlPushMatrix();
    rlTranslatef(v.x, v.y, 0);
    rlRotatef(RAD2DEG*angleToNext - 60,  0, 0, 1);
    DrawEllipse(0, 0, 18, 10, WHITE);
    DrawEllipse(0, 0, 16, 8, Fade(BLUE, 0.8));
    rlPopMatrix();

    for (size_t i = 0; i < FISH_POINTS_COUNT; ++i) {
        DrawCircleV(fish->chain.points[i], radiuses[i] + 2, WHITE);
    }
    for (size_t i = 1; i < FISH_POINTS_COUNT; ++i) {
        DrawPulleyTrapezoid(fish->chain.points[i - 1], radiuses[i - 1] + 2, fish->chain.points[i], radiuses[i] + 2, WHITE);
    }

    for (size_t i = 0; i < FISH_POINTS_COUNT; ++i) {
        DrawCircleV(fish->chain.points[i], radiuses[i], BLUE);
    }
    for (size_t i = 1; i < FISH_POINTS_COUNT; ++i) {
        DrawPulleyTrapezoid(fish->chain.points[i - 1], radiuses[i - 1], fish->chain.points[i], radiuses[i], BLUE);
    }

    ind = 0;
    angleToNext = Vector2AngleToPoint(fish->chain.points[ind], fish->chain.points[ind + 1]);
    v = Vector2PointOnCircle(fish->chain.points[ind], radiuses[ind], angleToNext + PI/3);
    DrawCircleV(v, 4, WHITE);
    v = Vector2PointOnCircle(fish->chain.points[ind], radiuses[ind], angleToNext - PI/3);
    DrawCircleV(v, 4, WHITE);
}

