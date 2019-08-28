#ifndef COLLISION_H
#define COLLISION_H

#include "Vec2D.h"

bool isCollision_nonRotate(Vec2D centerA, float widthA, float heightA,
        Vec2D centerB, float widthB, float heightB);
bool isCollision_rotate(Vec2D A[], Vec2D B[]);

#endif