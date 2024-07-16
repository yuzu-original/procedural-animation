#include "drawing_utils.h"
#include "math_utils.h"

#include <raylib.h>
#include <raymath.h>

// https://en.wikipedia.org/wiki/Belt_problem#Pulley_problem
void DrawPulleyTrapezoid(Vector2 v1, float r1, Vector2 v2, float r2, Color color) {
    float a1 = Vector2AngleToPoint(v1, v2);
    float a2 = acosf((r1 - r2) / Vector2Distance(v1, v2));

    Vector2 v11 = Vector2Add(v1, Vector2Rotate((Vector2){r1, 0}, a1 + a2));
    Vector2 v12 = Vector2Add(v1, Vector2Rotate((Vector2){r1, 0}, a1 - a2));
    Vector2 v21 = Vector2Add(v2, Vector2Rotate((Vector2){r2, 0}, a1 + a2));
    Vector2 v22 = Vector2Add(v2, Vector2Rotate((Vector2){r2, 0}, a1 - a2));

    DrawTriangle(v11, v21, v12, color);
    DrawTriangle(v21, v22, v12, color);
}
