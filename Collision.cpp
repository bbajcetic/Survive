#include "Collision.h"

bool isCollision_nonRotate(Vec2D centerA, float widthA, float heightA,
        Vec2D centerB, float widthB, float heightB) {
    float minAx, maxAx, minAy, maxAy, minBx, maxBx, minBy, maxBy;
    minAx = centerA.x-widthA/2.0;
    maxAx = centerA.x+widthA/2.0;
    minAy = centerA.y-heightA/2.0;
    maxAy = centerA.y+heightA/2.0;
    minBx = centerB.x-widthB/2.0;
    maxBx = centerB.x+widthB/2.0;
    minBy = centerB.y-heightB/2.0;
    maxBy = centerB.y+heightB/2.0;
    /* x check */
    if (minAx <= maxBx && maxAx >= minBx) {
        /* y check */
        if (minAy <= maxBy && maxAy >= minBy) {
            return true;
        }
    }
    return false;
}
bool isCollision_rotate(Vec2D A[], Vec2D B[]) {
    /* Parameters A and B are Vec2D arrays of size 4, defining a rectangle by
     * its corners, in a clockwise or counter-clockwise manner */

    //get 4 axes
    Vec2D axes[4] = { {A[1]-A[0]}, {A[2]-A[1]}, {B[1]-B[0]}, {B[2]-B[1]} };
    for (int i = 0; i < 4; i++) {
        /* current axis = axes[i] */
        Vec2D projs[8];
        for (int j = 0; j < 4; ++j) {
            projs[j] = vecProject(A[j], axes[i]);
            projs[j+4] = vecProject(B[j], axes[i]);
        }
        //find min and max projected vectors for each rect
        float dots[8];
        for (int j = 0; j < 8; ++j) {
            dots[j] = projs[j] * axes[i];
            //printf("dot %d = %f\n", j, dots[j]);
        }
        float minA, maxA, minB, maxB;
        minA = maxA = dots[0];
        minB = maxB = dots[4];
        for (int j = 0; j < 4; ++j) {
            if (dots[j] < minA) { minA = dots[j]; }
            else if (dots[j] > maxA) { maxA = dots[j]; }
            if (dots[j+4] < minB) { minB = dots[j+4]; }
            else if (dots[j+4] > maxB) { maxB = dots[j+4]; }
        }
        if (minB <= maxA && maxB >= minA) {
            continue;
        }
        else {
            return false;
        }
    }
    return true;
}