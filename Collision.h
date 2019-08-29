#ifndef COLLISION_H
#define COLLISION_H

#include <cmath>
#include "Vec2D.h"
#include "Projectile.h"
#include "Zombie.h"
#include "Survivor.h"
#include "CustomMath.h"

bool isCollision(Survivor& s, Zombie& z);
bool isCollision(Projectile& p, Zombie& z);

bool isCollision_nonRotate(Vec2D centerA, float widthA, float heightA,
        Vec2D centerB, float widthB, float heightB);
bool isCollision_rotate(Vec2D A[], Vec2D B[]);

#endif
