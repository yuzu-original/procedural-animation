#ifndef LIZARD_H_
#define LIZARD_H_

#include "chain.h"

#include <raylib.h>

#define LIZARD_SPINE_POINTS_COUNT 14
#define LIZARD_ARMS_COUNT 4
#define LIZARD_ARM_POINTS_COUNT 3

typedef struct {
    Chain spine;
    Chain arms[LIZARD_ARMS_COUNT];
    Vector2 armsDesired[LIZARD_ARMS_COUNT];
} Lizard;

extern void LizardInit(Lizard *lizard, Vector2 spinePoints[LIZARD_SPINE_POINTS_COUNT], Vector2 armsPoints[LIZARD_ARMS_COUNT][LIZARD_ARM_POINTS_COUNT]);

extern void LizardResolve(Lizard *lizard, Vector2 targetPos);
extern void LizardDraw(Lizard *lizard);

#endif // LIZARD_H_
