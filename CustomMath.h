#ifndef CUSTOMMATH_H
#define CUSTOMMATH_H

#include <cmath>
#include "Constants.h"

/* uses pythagorus theorem to find hypotenuse*/
float getDist(float x, float y);

/* returns angle in radians between 0 and 2*PI */
float findAngle(float adjacent, float opposite);

#endif
