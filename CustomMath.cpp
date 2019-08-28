#include "CustomMath.h"

/* returns hypotenuse of right triangle with sides of length x and y */
float getDist(float x, float y) {
    return sqrt( pow(x, 2) + pow(y, 2) );
}

/* returns angle in radians */
float findAngle(float adjacent, float opposite) {
    float rad;
    if (adjacent == 0) {
        rad = (opposite >= 0) ? PI/2.0 : 3.0*PI/2.0;
    }
    else {
        rad = atan(opposite/adjacent);
        if (adjacent >= 0 and opposite < 0) {
            rad = rad + 2.0*PI; /* to make angle between 0-360 */
        }
        else if (adjacent < 0) {
            rad = rad + PI;
        }
    }
    return rad;
}
