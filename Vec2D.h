#ifndef VEC2D_H
#define VEC2D_H

#include <stdio.h>
#include <cmath>

class Vec2D {
    public:
        Vec2D();
        Vec2D(float x, float y);
        Vec2D operator - (Vec2D const& obj); /* addition */
        Vec2D operator + (Vec2D const& obj); /* subtraction */
        float operator * (Vec2D const& obj); /* dot product */
        Vec2D operator * (float const& obj); /* scalar multiplication */
        void print();
        float getLength();
        float x;
        float y;
};

Vec2D vecProject(Vec2D a, Vec2D b);

#endif
