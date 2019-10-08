#include "Vec2D.h"
//#include "VecMath.h"

bool detectCollision(Vec2D A[], Vec2D B[]);

int main() {
    Vec2D a(2,6);
    Vec2D b(3,4);
    printf("a = ");
    a.print();
    printf("b = ");
    b.print();
    printf("Projection of vector a onto vector b = ");
    Vec2D proj = vecProject(a, b);
    proj.print();
    //Start
    Vec2D rectA[4] = { {1,4}, {5,8}, {7,6}, {3,2} };
    Vec2D rectB[4] = { {4,4}, {4.5,5.5}, {7.5,4.5}, {7,3} };
    Vec2D rectC[4] = { {6,10}, {7,10}, {7,7}, {6,7} };
    Vec2D rectD[4] = { {359.0, 25.0}, {374.0, 25.0}, {374.0, 28.000004}, {359.0, 27.999998} };
    Vec2D rectE[4] = { {356.0, 0.0}, {400.0, 0.0}, {400.0, 44.0}, {356.0, 44.0} };

    bool isCollision = detectCollision(rectB, rectA);
    printf("%s\n", isCollision ? "Collision!" : "No Collision...");
    isCollision = detectCollision(rectC, rectA);
    printf("%s\n", isCollision ? "Collision!" : "No Collision...");
    isCollision = detectCollision(rectC, rectB);
    printf("%s\n", isCollision ? "Collision!" : "No Collision...");
    isCollision = detectCollision(rectD, rectE);
    printf("%s\n", isCollision ? "Collision!" : "No Collision...");
    isCollision = isCollision_rotate(rectE, rectD);
    printf("%s\n", isCollision ? "Collision!" : "No Collision...");

}
bool detectCollision(Vec2D A[], Vec2D B[]) {
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

