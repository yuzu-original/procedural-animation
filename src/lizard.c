#include <stdlib.h>

#include "lizard.h"
#include "chain.h"
#include "math_utils.h"
#include "drawing_utils.h"

#include <raylib.h>
#include <raymath.h>

static const float radiuses[LIZARD_SPINE_POINTS_COUNT] = {18, 22, 25, 24, 20, 18, 16, 14, 12, 10, 8, 6, 4, 2};
static const float armRadiuses[LIZARD_ARM_POINTS_COUNT] = {4, 6, 4};

void LizardInit(Lizard *lizard, Vector2 spinePoints[LIZARD_SPINE_POINTS_COUNT], Vector2 armsPoints[LIZARD_ARMS_COUNT][LIZARD_ARM_POINTS_COUNT]) {
    lizard->spine.points = spinePoints;
    lizard->spine.pointsCount = LIZARD_SPINE_POINTS_COUNT;
    lizard->spine.spacing = 32;
    for (size_t i = 0; i < 4; ++i) {
        lizard->arms[i].points = armsPoints[i];
        lizard->arms[i].pointsCount = LIZARD_ARM_POINTS_COUNT;
        lizard->arms[i].spacing = (i < 2) ? 40 : 30;
    }
}

void LizardResolve(Lizard *lizard, Vector2 targetPos) {
    ChainResolve(&lizard->spine, Vector2Lerp(lizard->spine.points[0], targetPos, 0.1));

    for (size_t i = 0; i < LIZARD_ARMS_COUNT; ++i) {
        int side = (i % 2 == 0) ? 1 : -1;
        size_t bodyIndex = (i < 2) ? 3 : 7;
        float angle = (i < 2) ? PI/3 : PI/3;
        float bodyAngle = Vector2AngleToPoint(lizard->spine.points[bodyIndex], lizard->spine.points[bodyIndex - 1]);
        
        Vector2 desiredNew = Vector2PointOnCircle(lizard->spine.points[bodyIndex], lizard->arms[i].spacing*1.75, bodyAngle + angle*side);
        
        if (Vector2Distance(lizard->armsDesired[i], desiredNew) > lizard->arms[i].spacing*3 || Vector2Distance(lizard->arms[i].points[LIZARD_ARM_POINTS_COUNT - 1], lizard->armsDesired[i]) > lizard->arms[i].spacing*(lizard->arms[i].pointsCount - 1)) {
            lizard->armsDesired[i] = desiredNew;
        }

        lizard->arms[i].points[LIZARD_ARM_POINTS_COUNT - 1] = Vector2PointOnCircle(lizard->spine.points[bodyIndex], radiuses[bodyIndex] - 20, bodyAngle + PI/2*side);

        ChainResolveFabrik(&lizard->arms[i], Vector2Lerp(lizard->arms[i].points[0], lizard->armsDesired[i], 0.4));
    }
}

void LizardDraw(Lizard *lizard) {
    // Draw arms outline
    float outlineWidth = 2;
    for (size_t i = 0; i < LIZARD_ARMS_COUNT; ++i) {
        for (size_t j = 0; j < LIZARD_ARM_POINTS_COUNT; ++j) {
            DrawCircleV(lizard->arms[i].points[j], armRadiuses[j] + outlineWidth, WHITE);
        }
        for (size_t j = 1; j < LIZARD_ARM_POINTS_COUNT; ++j) {
            DrawPulleyTrapezoid(lizard->arms[i].points[j - 1], armRadiuses[j - 1] + outlineWidth, lizard->arms[i].points[j], armRadiuses[j] + outlineWidth, WHITE);
        }
    }

    // Draw arms
    for (size_t i = 0; i < LIZARD_ARMS_COUNT; ++i) {
        for (size_t j = 0; j < LIZARD_ARM_POINTS_COUNT; ++j) {
            DrawCircleV(lizard->arms[i].points[j], armRadiuses[j], DARKGREEN);
        }
        for (size_t j = 1; j < LIZARD_ARM_POINTS_COUNT; ++j) {
            DrawPulleyTrapezoid(lizard->arms[i].points[j - 1], armRadiuses[j - 1], lizard->arms[i].points[j], armRadiuses[j], DARKGREEN);
        }
    }

    // Draw body outline
    for (size_t i = 0; i < LIZARD_SPINE_POINTS_COUNT; ++i) {
        DrawCircleV(lizard->spine.points[i], radiuses[i] + outlineWidth, WHITE);
    }
    for (size_t i = 1; i < LIZARD_SPINE_POINTS_COUNT; ++i) {
        DrawPulleyTrapezoid(lizard->spine.points[i - 1], radiuses[i - 1] + outlineWidth, lizard->spine.points[i], radiuses[i] + outlineWidth, WHITE);
    }

    // Draw body
    for (size_t i = 0; i < LIZARD_SPINE_POINTS_COUNT; ++i) {
        DrawCircleV(lizard->spine.points[i], radiuses[i], DARKGREEN);
    }
    for (size_t i = 1; i < LIZARD_SPINE_POINTS_COUNT; ++i) {
        DrawPulleyTrapezoid(lizard->spine.points[i - 1], radiuses[i - 1], lizard->spine.points[i], radiuses[i], DARKGREEN);
    }
    
    size_t ind = 0;
    float bodyAngle = Vector2AngleToPoint(lizard->spine.points[ind], lizard->spine.points[ind + 1]);
    Vector2 v = Vector2PointOnCircle(lizard->spine.points[ind], radiuses[ind], bodyAngle + PI/3);
    DrawCircleV(v, 4, WHITE);
    v = Vector2PointOnCircle(lizard->spine.points[ind], radiuses[ind], bodyAngle - PI/3);
    DrawCircleV(v, 4, WHITE);
}
