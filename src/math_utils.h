#ifndef MATH_UTILS_H_
#define MATH_UTILS_H_

#include <raylib.h>

// Returns the angle between the line connecting the two points and the X axis, in radians.
extern float Vector2AngleToPoint(Vector2 start, Vector2 end);
extern Vector2 Vector2PointOnCircle(Vector2 center, float radius, float angle);

#endif // MATH_UTILS_H_
