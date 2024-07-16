#include <math.h>

#include "math_utils.h"
#include "raymath.h"

#include <raylib.h>

float Vector2AngleToPoint(Vector2 start, Vector2 end) {
    return atan2f(end.y - start.y, end.x - start.x);
}

Vector2 Vector2PointOnCircle(Vector2 center, float radius, float angle) {
    return Vector2Add(center, Vector2Rotate((Vector2){radius, 0}, angle));
}
